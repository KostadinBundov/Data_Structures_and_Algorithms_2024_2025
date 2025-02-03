#pragma once

#include <iostream>
#include <list>
#include <forward_list>
#include <vector>
#include <algorithm>

template<class Key, class Value, class Hash = std::hash<Key>>
class HashMap {
public:
    using Pair = std::pair<Key, Value>;
    using hashMapType = std::vector<std::forward_list<typename std::list<Pair>::iterator>>;

    class ConstIterator {
    public:
        ConstIterator(typename std::list<Pair>::const_iterator iter);
        const Pair& operator*() const;
        const Pair* operator->() const;

        ConstIterator& operator++();
        ConstIterator operator++(int);

        bool operator==(const ConstIterator& other) const;
        bool operator!=(const ConstIterator& other) const;

    private:
        typename std::list<Pair>::const_iterator iter;
    };

    HashMap();

    void add(const Key& key, const Value& value);
    void remove(const Key& key);
    typename HashMap<Key, Value, Hash>::ConstIterator find(const Key& key) const;

    size_t getSize() const;
    bool isEmpty() const;

    typename HashMap<Key, Value, Hash>::ConstIterator cbegin() const;
    typename HashMap<Key, Value, Hash>::ConstIterator cend() const;

private:
    std::list<Pair> data;
    hashMapType hashMap;

    void resize();
    size_t getHashCode(const Key& key) const;
    double getLoadFactor() const;

    Hash getHash;
    double maxLoadFactor = 0.75;
};


template<class Key, class Value, class Hash>
HashMap<Key, Value, Hash>::ConstIterator::ConstIterator(typename std::list<Pair>::const_iterator iter) : iter(iter) { }

template<class Key, class Value, class Hash>
const typename HashMap<Key, Value, Hash>::Pair& HashMap<Key, Value, Hash>::ConstIterator::operator*() const {
    return *iter;
}

template<class Key, class Value, class Hash>
const typename HashMap<Key, Value, Hash>::Pair* HashMap<Key, Value, Hash>::ConstIterator::operator->() const {
    return &(*iter);
}

template<class Key, class Value, class Hash>
typename HashMap<Key, Value, Hash>::ConstIterator& HashMap<Key, Value, Hash>::ConstIterator::operator++() {
    ++iter;
    return *this;
}

template<class Key, class Value, class Hash>
typename HashMap<Key, Value, Hash>::ConstIterator HashMap<Key, Value, Hash>::ConstIterator::operator++(int) {
    ConstIterator copy(*this);
    ++(*this);
    return copy;
}

template<class Key, class Value, class Hash>
bool HashMap<Key, Value, Hash>::ConstIterator::operator==(const ConstIterator& other) const {
    return iter == other.iter;
}

template<class Key, class Value, class Hash>
bool HashMap<Key, Value, Hash>::ConstIterator::operator!=(const ConstIterator& other) const {
    return iter != other.iter;
}

template<class Key, class Value, class Hash>
HashMap<Key, Value, Hash>::HashMap() {
    hashMap.resize(8);
}

template<class Key, class Value, class Hash>
void HashMap<Key, Value, Hash>::add(const Key& key, const Value& value) {
    if (getLoadFactor() >= maxLoadFactor) {
        resize();
    }

    auto iter = find(key);
    if (iter != cend()) {
        return;
    }

    size_t hashCode = getHashCode(key);
    auto& bucket = hashMap[hashCode];

    data.emplace_back(key, value);
    bucket.push_front(--data.end());
}

template<class Key, class Value, class Hash>
void HashMap<Key, Value, Hash>::remove(const Key& key) {
    size_t hashCode = getHashCode(key);
    auto& bucket = hashMap[hashCode];

    bucket.remove_if([this, &key](const auto& it) {
        if (it->first == key) {
            data.erase(it);
            return true;
        }
        return false;
        });
}

template<class Key, class Value, class Hash>
typename HashMap<Key, Value, Hash>::ConstIterator HashMap<Key, Value, Hash>::find(const Key& key) const {
    size_t hashCode = getHashCode(key);
    auto& bucket = hashMap[hashCode];

    auto iter = std::find_if(bucket.begin(), bucket.end(), [&key](const auto& it) {
        return it->first == key;
        });

    if (iter == bucket.end()) {
        return cend();
    }

    return ConstIterator(*iter);
}

template<class Key, class Value, class Hash>
size_t HashMap<Key, Value, Hash>::getSize() const {
    return data.size();
}

template<class Key, class Value, class Hash>
bool HashMap<Key, Value, Hash>::isEmpty() const {
    return data.empty();
}

template<class Key, class Value, class Hash>
typename HashMap<Key, Value, Hash>::ConstIterator HashMap<Key, Value, Hash>::cbegin() const {
    return ConstIterator(data.cbegin());
}

template<class Key, class Value, class Hash>
typename HashMap<Key, Value, Hash>::ConstIterator HashMap<Key, Value, Hash>::cend() const {
    return ConstIterator(data.cend());
}

template<class Key, class Value, class Hash>
void HashMap<Key, Value, Hash>::resize() {
    size_t newSize = hashMap.size() * 2;
    hashMapType newHashMap(newSize);

    for (auto it = data.begin(); it != data.end(); it++) {
        size_t newHashCode = getHash(it->first) % newSize;
        newHashMap[newHashCode].push_front(it);
    }

    hashMap = std::move(newHashMap);
}

template<class Key, class Value, class Hash>
size_t HashMap<Key, Value, Hash>::getHashCode(const Key& key) const {
    return getHash(key) % hashMap.size();
}

template<class Key, class Value, class Hash>
double HashMap<Key, Value, Hash>::getLoadFactor() const {
    return static_cast<double>(data.size()) / hashMap.size();
}