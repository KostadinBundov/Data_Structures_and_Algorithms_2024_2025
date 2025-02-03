#pragma once

#include <iostream>
#include <forward_list>
#include <list>
#include <vector>
#include <algorithm>

template<class Value, class Hash = std::hash<Value>>
class HashSet {
public:
    using HashTableType = std::vector<std::forward_list<typename std::list<Value>::iterator>>;

    class ConstIterator {
    public:
        ConstIterator(typename std::list<Value>::const_iterator iter);

        const Value& operator*() const;
        const Value* operator->() const;

        ConstIterator& operator++();
        ConstIterator operator++(int);

        ConstIterator& operator--();
        ConstIterator operator--(int);

        bool operator==(const ConstIterator& other) const;
        bool operator!=(const ConstIterator& other) const;

    private:
        typename std::list<Value>::const_iterator iter;
    };

    HashSet();

    void add(const Value& value);
    void remove(const Value& value);

    ConstIterator find(const Value& value) const;

    ConstIterator cbegin() const;
    ConstIterator cend() const;

    size_t getSize() const;
    bool isEmpty() const;

private:
    std::list<Value> data;
    HashTableType hashTable;

    double maxLoadFactor = 0.75;
    Hash getHash;

    double getLoadFactor() const;
    size_t getHashCode(const Value& value) const;
    void resize();

    std::forward_list<typename std::list<Value>::iterator>& getBucket(const Value& value);
};

template<class Value, class Hash>
HashSet<Value, Hash>::ConstIterator::ConstIterator(typename std::list<Value>::const_iterator iter)
    : iter(iter) { }

template<class Value, class Hash>
const Value& HashSet<Value, Hash>::ConstIterator::operator*() const {
    return *iter;
}

template<class Value, class Hash>
const Value* HashSet<Value, Hash>::ConstIterator::operator->() const {
    return &(*iter);
}

template<class Value, class Hash>
typename HashSet<Value, Hash>::ConstIterator& HashSet<Value, Hash>::ConstIterator::operator++() {
    iter++;
    return *this;
}

template<class Value, class Hash>
typename HashSet<Value, Hash>::ConstIterator HashSet<Value, Hash>::ConstIterator::operator++(int) {
    ConstIterator copy(*this);
    ++(*this);
    return copy;
}

template<class Value, class Hash>
typename HashSet<Value, Hash>::ConstIterator& HashSet<Value, Hash>::ConstIterator::operator--() {
    iter--;
    return *this;
}

template<class Value, class Hash>
typename HashSet<Value, Hash>::ConstIterator HashSet<Value, Hash>::ConstIterator::operator--(int) {
    ConstIterator copy(*this);
    --(*this);
    return copy;
}

template<class Value, class Hash>
bool HashSet<Value, Hash>::ConstIterator::operator==(const ConstIterator& other) const {
    return iter == other.iter;
}

template<class Value, class Hash>
bool HashSet<Value, Hash>::ConstIterator::operator!=(const ConstIterator& other) const {
    return iter != other.iter;
}

template<class Value, class Hash>
HashSet<Value, Hash>::HashSet() {
    hashTable.resize(8);
}

template<class Value, class Hash>
void HashSet<Value, Hash>::add(const Value& value) {
    if (find(value) != cend()) {
        return;
    }

    auto& bucket = getBucket(value);
    data.emplace_back(value);
    bucket.push_front(--data.end());
}

template<class Value, class Hash>
void HashSet<Value, Hash>::remove(const Value& value) {
    auto& bucket = getBucket(value);

    bucket.remove_if([this, &value](const auto& it) {
        if (*it == value) {
            data.erase(it);
            return true;
        }
        return false;
        });
}

template<class Value, class Hash>
typename HashSet<Value, Hash>::ConstIterator HashSet<Value, Hash>::find(const Value& value) const {
    auto& bucket = getBucket(value);

    auto iter = std::find_if(bucket.begin(), bucket.end(), [&value](const auto& it) {
        return *it == value;
        });

    if (iter == bucket.end()) {
        return cend();
    }

    return ConstIterator(*iter);
}

template<class Value, class Hash>
typename HashSet<Value, Hash>::ConstIterator HashSet<Value, Hash>::cbegin() const {
    return ConstIterator(data.cbegin());
}

template<class Value, class Hash>
typename HashSet<Value, Hash>::ConstIterator HashSet<Value, Hash>::cend() const {
    return ConstIterator(data.cend());
}

template<class Value, class Hash>
size_t HashSet<Value, Hash>::getSize() const {
    return data.size();
}

template<class Value, class Hash>
bool HashSet<Value, Hash>::isEmpty() const {
    return data.size() == 0;
}

template<class Value, class Hash>
double HashSet<Value, Hash>::getLoadFactor() const {
    return static_cast<double>(data.size()) / hashTable.size();
}

template<class Value, class Hash>
size_t HashSet<Value, Hash>::getHashCode(const Value& value) const {
    return getHash(value) % hashTable.size();
}

template<class Value, class Hash>
void HashSet<Value, Hash>::resize() {
    size_t newSize = hashTable.size() * 2;
    HashTableType newHashTable(newSize);

    for (auto it = data.begin(); it != data.end(); it++) {
        size_t newHashCode = getHash(*it) % newSize;
        newHashTable[newHashCode].push_front(it);
    }

    hashTable = std::move(newHashTable);
}

template<class Value, class Hash>
std::forward_list<typename std::list<Value>::iterator>& HashSet<Value, Hash>::getBucket(const Value& value) {
    size_t hashCode = getHashCode(value);
    return hashTable[hashCode];
}