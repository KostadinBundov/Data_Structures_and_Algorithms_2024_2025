#pragma once

#include <iostream>
#include <vector>

template<class Key, class Value, class Hash = std::hash<Key>>
class HashMap {
public:
	HashMap() {
		size = 0;
		step = 3;
		data.resize(100);
	}

	class ConstIterator {
	public:
		ConstIterator(size_t index, const HashMap<Key, Value, Hash>& context) : index(index), context(context) { }
		const std::pair<Key, Value>& operator*() const { return context.data[index].element; }
		const std::pair<Key, Value>* operator->() const { return &context.data[index].element; }

		ConstIterator& operator++() {
			do
			{
				index++;
			} while (index < context.data.size() && (context.data[index].isTaken == false || context.data[index].isDeleted == true));

			if (index >= context.data.size()) {
				index = -1;
			}

			return *this;
		}
		ConstIterator operator++(int) {
			size_t copy = index;

			do
			{
				index++;
			} while (index < context.data.size() && (context.data[index].isTaken == false || context.data[index].isDeleted == true));

			if (index >= context.data.size()) {
				index = -1;
			}

			return ConstIterator(copy, context);
		}

		bool operator==(const ConstIterator& other) const { return index == other.index; }
		bool operator!=(const ConstIterator& other) const { return index != other.index; }
	private:
		size_t index;
		const HashMap<Key, Value, Hash>& context;
	};

	void add(const Key& key, const Value& value) {
		if (getLoadFactor() >= maxLoadFactor) {
			resize();
		}

		size_t elementIndex = getHashCode(key);
		size_t currIndex = elementIndex;

		do
		{
			if (data[currIndex].isTaken == false || data[currIndex].isDeleted == true) {
				data[currIndex] = Node(key, value, true, false);
				size++;
				return;
			}

			if (data[currIndex].element.first == key) {
				return;
			}

			currIndex = (currIndex + step) % data.size();
		} while (currIndex != elementIndex);
	}

	bool remove(const Key& key) {
		size_t elementIndex = getHashCode(key);
		size_t currIndex = elementIndex;

		do
		{
			if (data[currIndex].isTaken == false) {
				break;
			}

			if (data[currIndex].isDeleted == false && data[currIndex].element.first == key) {
				data[currIndex].isDeleted = true;
				size--;
				return true;
			}

			currIndex = (currIndex + step) % data.size();
		} while (currIndex != elementIndex);

		return false;
	}

	ConstIterator find(const Key& key) const {
		size_t elementIndex = getHashCode(key);
		size_t currIndex = elementIndex;

		do
		{
			if (data[currIndex].isTaken == false) {
				break;
			}

			if (data[currIndex].isDeleted == false && data[currIndex].element.first == key) {
				return ConstIterator(currIndex, *this);
			}

			currIndex = (currIndex + step) % data.size();
		} while (currIndex != elementIndex);

		return cend();
	}

	ConstIterator cbegin() const {
		if (size == 0) {
			return cend();
		}

		for (int i = 0; i < data.size(); i++) {
			if (data[i].isTaken && data[i].isDeleted == false) {
				return ConstIterator(i, *this);
			}
		}

		return cend();
	}
	ConstIterator cend() const { return ConstIterator(-1, *this); }

	size_t getSize() const { return size; }
	bool isEmpty() const { return size == 0; }

private:
	struct Node {
		Node() = default;
		Node(const Key& key, const Value& value, bool isTaken, bool isDeleted) : isTaken(isTaken), isDeleted(isDeleted) {
			element = std::make_pair(key, value);
		}

		std::pair<Key, Value> element;
		bool isTaken = false;
		bool isDeleted = false;
	};

	std::vector<Node> data;

	size_t size;
	Hash getHash;
	double maxLoadFactor = 0.75;

	size_t step;

	double getLoadFactor() const { return static_cast<double>(size) / data.size(); }
	size_t getHashCode(const Key& key) const { return getHash(key) % data.size(); }

	void resize() {
		std::vector<Node> newData(data.size() * 2);

		for (int i = 0; i < data.size(); i++) {
			if (data[i].isTaken && data[i].isDeleted == false) {
				size_t elementIndex = getHash(data[i].element.first) % newData.size();
				size_t currIndex = elementIndex;

				do
				{
					if (newData[currIndex].isTaken == false) {
						newData[currIndex] = Node(std::move(data[i].element.first), std::move(data[i].element.second), true, false);
						break;
					}

					currIndex = (currIndex + step) % newData.size();
				} while (currIndex != elementIndex);
			}
		}

		data = std::move(newData);
	}
};