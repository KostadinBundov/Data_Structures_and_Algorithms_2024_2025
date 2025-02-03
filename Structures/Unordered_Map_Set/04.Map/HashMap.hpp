#pragma once

#include<iostream>
#include<forward_list>
#include<list>
#include<vector>
#include<algorithm>

template<class Key, class Value, class Hash = std::hash<Key>>
class HashMap {
public:
	HashMap() {
		hashTable.resize(8, std::make_pair(data.end(), 0));
	}

	using Pair = std::pair<Key, Value>;
	using BucketType = std::pair<typename std::list<Pair>::iterator, size_t>;
	using HashTableType = std::vector<BucketType>;

	class ConstIterator {
	public:
		ConstIterator(typename std::list<Pair>::const_iterator iter) : iter(iter) { }

		const Pair& operator*() const { return *iter; }
		const Pair* operator->() const { return &(*iter); }

		ConstIterator& operator++() {
			iter++;
			return *this;
		}
		ConstIterator& operator++(int) {
			ConstIterator copy(*this);
			++(*this);
			return copy;
		}

		ConstIterator& operator--() {
			iter--;
			return *this;
		}
		ConstIterator& operator--(int) {
			ConstIterator copy(*this);
			--(*this);
			return copy;
		}

		bool operator==(const ConstIterator& other) const { return iter == other.iter; }
		bool operator!=(const ConstIterator& other) const { return iter != other.iter; }
	private:
		typename std::list<Pair>::const_iterator iter;
	};

	ConstIterator cbegin() const { return ConstIterator(data.cbegin()); }
	ConstIterator cend() const { return ConstIterator(data.cend()); }

	std::pair<bool, ConstIterator> add(const Key& key, const Value& value) {
		if (hashTable.empty()) {
			hashTable.resize(8, std::make_pair(data.end(), 0));
		}

		typename std::list<Pair>::iterator elementIter = findElement(key);

		if (elementIter != data.end()) {
			return std::make_pair(false, ConstIterator(elementIter));
		}

		BucketType& bucket = getBucketInfo(key);

		if (bucket.second == 0) {
			data.emplace_front(key, value);
			bucket.first = data.begin();
		}
		else {
			auto iter = data.insert(bucket.first, std::make_pair(key, value));
			bucket.first = iter;
		}

		bucket.second++;

		if (getLoadFactor() >= maxLoadFactor) {
			resize();
			typename std::list<Pair>::iterator iter = findElement(key);
			return std::make_pair(true, ConstIterator(iter));
		}

		return std::make_pair(true, ConstIterator(bucket.first));
	}

	bool remove(const Key& key) {
		if (hashTable.empty()) {
			return false;
		}

		typename std::list<Pair>::iterator elementIter = findElement(key);

		if (elementIter == data.end()) {
			return false;
		}

		BucketType& bucket = getBucketInfo(key);

		if (bucket.first == elementIter) {
			auto tempIter = elementIter;
			++tempIter;

			bucket.first = tempIter;
		}

		data.erase(elementIter);
		bucket.second--;

		return true;
	}

	bool remove(const ConstIterator& iter) {
		if (iter == cend() || hashTable.empty()) {
			return false;
		}

		const Key& key = iter->first;
		return remove(key);
	}

	ConstIterator find(const Key& key) const {
		if (hashTable.empty()) {
			return cend();
		}

		typename std::list<Pair>::const_iterator elementIter = findElement(key);

		if (elementIter == data.cend()) {
			return cend();
		}

		return ConstIterator(elementIter);
	}

	size_t getSize() const { return data.size(); }
	bool isEmpty() const { return data.size() == 0; }

	void clear() {
		data.clear();
		hashTable.clear();
	}
private:
	std::list<Pair> data;
	HashTableType hashTable;

	double maxLoadFactor = 0.75;
	Hash getHash;

	void resize() {
		std::vector<Pair> oldData(data.size());

		for (auto it = data.begin(); it != data.end(); ++it) {
			oldData.push_back(*it);
		}

		size_t newSize = hashTable.size() * 2;
		data.clear();
		hashTable.clear();
		hashTable.resize(newSize, std::make_pair(data.end(), 0));

		for (int i = 0; i < oldData.size(); i++) {
			add(oldData[i].first, oldData[i].second);
		}
	}

	size_t getLoadFactor() const { return static_cast<double>(data.size()) / hashTable.size(); }
	size_t getHashCode(const Key& key) const { return getHash(key) % hashTable.size(); }

	typename std::list<Pair>::const_iterator findElement(const Key& key) const {
		const BucketType& bucket = getBucketInfo(key);

		auto iter = bucket.first;
		for (int i = 0; i < bucket.second; i++) {
			if (iter->first == key) {
				return iter;
			}

			++iter;
		}

		return data.cend();
	}

	typename std::list<Pair>::iterator findElement(const Key& key) {
		BucketType& bucket = getBucketInfo(key);

		auto iter = bucket.first;
		for (int i = 0; i < bucket.second; i++) {
			if (iter->first == key) {
				return iter;
			}

			++iter;
		}

		return data.end();
	}

	const BucketType& getBucketInfo(const Key& key) const {
		size_t hashCode = getHashCode(key);
		return hashTable[hashCode];
	}

	BucketType& getBucketInfo(const Key& key) {
		size_t hashCode = getHashCode(key);
		return hashTable[hashCode];
	}
};