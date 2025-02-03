#pragma once

#include<iostream>
#include<forward_list>
#include<list>
#include<vector>
#include<algorithm>

template<class Value, class Hash = std::hash<Value>>
class HashSet {
public:
	using HashtableType = std::vector<std::pair<typename std::list<Value>::iterator, size_t>>;

	HashSet() { hashTable.resize(8, std::make_pair(data.end(), 0)); }

	class ConstIterator {
	public:
		ConstIterator(typename std::list<Value>::const_iterator iter) : iter(iter) { };

		const Value& operator*() const { return *iter; }
		const Value* operator->() const { return &(*iter); };

		ConstIterator& operator++() {
			iter++;
			return *this;
		}
		ConstIterator operator++(int) {
			ConstIterator copy(*this);
			++(*this);
			return copy;
		}

		ConstIterator& operator--() {
			iter--;
			return *this;
		}
		ConstIterator operator--(int) {
			ConstIterator copy(*this);
			--(*this);
			return copy;
		}

		bool operator==(const ConstIterator& other) const { return iter == other.iter; }
		bool operator!=(const ConstIterator& other) const { return iter != other.iter; }
	private:
		typename std::list<Value>::const_iterator iter;
	};

	ConstIterator cbegin() const { return ConstIterator(data.cbegin()); }
	ConstIterator cend() const { return ConstIterator(data.cend()); }


	size_t getSize() const { return data.size(); }
	bool isEmpty() const { return data.size() == 0; }

	void clear() {
		hashTable.clear();
		data.clear();
	}

	ConstIterator find(const Value& value) {
		if (hashTable.empty()) {
			return cend();
		}

		typename std::list<Value>::iterator iter = findElement(value);

		if (iter == data.end()) {
			return cend();
		}

		return ConstIterator(iter);
	}

	bool remove(const Value& value) {
		if (hashTable.empty()) {
			return false;
		}

		typename std::list<Value>::iterator iter = findElement(value);

		if (iter == data.end()) {
			return false;
		}

		auto& bucketInfo = getBucketInfo(value);

		if (iter == bucketInfo.first) {
			auto nextIter = iter;
			++nextIter;
			bucketInfo.first = nextIter;
		}

		data.erase(iter);
		bucketInfo.second -= 1;

		return true;
	}

	bool remove(const ConstIterator& it) {
		if (it == cend() || hashTable.empty()) {
			return false;
		}

		const Value& val = *it;

		return remove(val);
	}

	std::pair<bool, ConstIterator> add(const Value& value) {
		if (hashTable.empty()) {
			hashTable.resize(8, std::make_pair(data.end(), 0));
		}

		typename std::list<Value>::iterator iter = findElement(value);

		if (iter != data.end()) {
			return std::make_pair(false, ConstIterator(iter));
		}

		auto& bucketInfo = getBucketInfo(value);

		if (bucketInfo.second == 0) {
			data.push_front(value);
			bucketInfo.first = data.begin();
		}
		else {
			auto insertedPosition = data.insert(bucketInfo.first, value);
			bucketInfo.first = insertedPosition;
		}

		bucketInfo.second++;

		if (getLoadFactor() >= maxLoadFactor) {
			resize();

			typename std::list<Value>::iterator iter = findElement(value);

			return std::make_pair(true, ConstIterator(iter));
		}

		return std::make_pair(true, ConstIterator(bucketInfo.first));
	}

private:
	double maxLoadFactor = 0.75;
	Hash getHash;

	std::list<Value> data;
	HashtableType hashTable;

	void resize() {
		size_t newSize = hashTable.size() * 2;

		std::vector<Value> oldElements(data.size());

		for (auto it = data.begin(); it != data.end(); ++it) {
			oldElements.push_back(*it);
		}

		data.clear();
		hashTable.clear();
		hashTable.resize(newSize, std::make_pair(data.end(), 0));

		for (int i = 0; i < oldElements.size(); i++) {
			add(oldElements[i]);
		}
	}

	double getLoadFactor() const {
		return static_cast<double>(data.size()) / hashTable.size();
	}

	size_t getHashCode(const Value& value) const { return getHash(value) % hashTable.size(); }

	std::pair<typename std::list<Value>::iterator, size_t>& getBucketInfo(const Value& value) {
		size_t hashCode = getHashCode(value);
		return hashTable[hashCode];
	}

	typename std::list<Value>::const_iterator findElement(const Value& value) const {
		size_t hashCode = getHashCode(value);
		auto iter = hashTable[hashCode].first;

		for (int i = 0; i < hashTable[hashCode].second; i++) {
			if (*iter == value) {
				return iter;
			}

			++iter;
		}

		return data.cend();
	}

	typename std::list<Value>::iterator findElement(const Value& value) {
		auto& bucketInfo = getBucketInfo(value);

		auto iter = bucketInfo.first;

		for (int i = 0; i < bucketInfo.second; i++) {
			if (*iter == value) {
				return iter;
			}

			++iter;
		}

		return data.end();
	}
};