#pragma once

#include <iostream> 
#include <vector>

template<class Key, class Hash = std::hash<Key>>
class HashSet {
public:
	HashSet() {
		data.resize(100);
		jumpValue = 3;
	}

	class ConstIterator {
	public:
		ConstIterator(size_t index, const HashSet<Key, Hash>& context) : index(index), context(context) { }

		const Key& operator*() const { return context.data[index].key; }
		const Key* operator->() const { return &context.data[index].key; }

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
			size_t oldIndex = index;

			do
			{
				index++;
			} while (index < context.data.size() && (context.data[index].isTaken == false || context.data[index].isDeleted == true));

			if (index >= data.size()) {
				index = -1;
			}

			return ConstIterator(oldIndex);
		}

		bool operator==(const ConstIterator& other) const { return index == other.index; }
		bool operator!=(const ConstIterator& other) const { return index != other.index; }
	private:
		int index;
		const HashSet<Key, Hash>& context;
	};

	size_t getSize() const { return size; }
	bool isEmpty() const { return size == 0; }

	ConstIterator cbegin() const {
		if (size == 0) {
			return cend();
		}

		for (int i = 0; i < data.size(); i++)
		{
			if (data[i].isTaken && data[i].isDeleted == false) {
				return ConstIterator(i, *this);
			}
		}

		return cend();
	}

	ConstIterator cend() const { return ConstIterator(-1, *this); }

	void add(const Key& key) {
		if (getLoadFactor() >= maxLoadFactor) {
			resize();
		}

		size_t hashCode = getHashCode(key);
		size_t index = hashCode;

		do
		{
			if (data[index].isTaken == false || data[index].isDeleted) {
				data[index] = Node(key, true, false);
				size++;
				return;
			}
			else if (data[index].key == key) {
				return;
			}

			index = (index + jumpValue) % data.size();

		} while (index != hashCode);
	}

	bool remove(const Key& key) {
		size_t hashCode = getHashCode(key);
		size_t index = hashCode;

		do
		{
			if (data[index].isTaken == false) {
				return false;
			}
			else if (data[index].isDeleted == false && data[index].key == key) {
				data[index].isDeleted = true;
				size--;
				return true;
			}

			index = (index + jumpValue) % data.size();

		} while (index != hashCode);

		return false;
	}

	ConstIterator find(const Key& key) {
		size_t hashCode = getHashCode(key);
		size_t index = hashCode;

		do
		{
			if (data[index].isTaken == false) {
				return cend();
			}
			else if (data[index].isDeleted == false && data[index].key == key) {
				return ConstIterator(index, *this);
			}

			index = (index + jumpValue) % data.size();

		} while (index != hashCode);
	}
private:
	struct Node {
		Node() = default;
		Node(const Key& key, bool isTaken, bool isDeleted) : key(key), isTaken(isTaken), isDeleted(isDeleted) { }

		Key key;
		bool isTaken = false;
		bool isDeleted = false;
	};

	std::vector<Node> data;
	size_t jumpValue;
	size_t size = 0;

	Hash getHash;
	double maxLoadFactor = 0.75;

	size_t getHashCode(const Key& key) const { return getHash(key) % data.size(); }
	double getLoadFactor() const { return static_cast<double>(size) / data.size(); }

	void resize() {
		std::vector<Node> newData(data.size() * 2);

		for (auto it = data.begin(); it != data.end(); ++it) {
			if (it->isTaken && it->isDeleted == false) {
				size_t hashCode = getHash(it->key) % newData.size();
				size_t index = hashCode;

				do
				{
					if (newData[index].isTaken == false) {
						newData[index] = Node(std::move(it->key), true, false);
						break;
					}

					index = (index + jumpValue) % newData.size();
				} while (index != hashCode);
			}
		}

		data = std::move(newData);
	}
};