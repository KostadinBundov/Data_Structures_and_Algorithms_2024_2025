#pragma once

#include <iostream>

#include <forward_list>
#include <list>
#include <vector>

template <class T, class Hash = std::hash<T>>
class UnorderedSet {
public:
    using HashTableType = std::vector<std::forward_list<typename std::list<T>::iterator>>;

    class ConstIterator
    {
    public:
        const T& operator*() const;
        const T* operator->() const;

        ConstIterator& operator++();
        ConstIterator operator++(int);

        ConstIterator& operator--();
        ConstIterator operator--(int);

        bool operator==(const ConstIterator& other) const;
        bool operator!=(const ConstIterator& other) const;

    private:
        typename std::list<T>::const_iterator element;
        ConstIterator(typename std::list<T>::const_iterator it);
        friend class UnorderedSet;
    };

    UnorderedSet();

    void insert(const T& element);

    void remove(const T& element);
    ConstIterator remove(ConstIterator it);

    ConstIterator find(const T& element);

    void clear();
    bool empty() const;

    template <class Predicate>
    void erase_if(Predicate predicate);

    double loadFactor() const;

    ConstIterator cbegin() const;
    ConstIterator cend() const;

private:
    std::list<T> data;
    HashTableType hashTable;

    double maxLoadFactor = 0.75;
    Hash getHash;

    std::forward_list<typename std::list<T>::iterator>& getHashTableSlot(const T& element);

    void resize();
    size_t getHashCode(const T& element) const;
};

template<class T, class Hash>
const T& UnorderedSet<T, Hash>::ConstIterator::operator*() const {
    return *element;
}

template<class T, class Hash>
typename UnorderedSet<T, Hash>::ConstIterator&
UnorderedSet<T, Hash>::ConstIterator::operator++() {
    ++element;
    return *this;
}

template<class T, class Hash>
typename UnorderedSet<T, Hash>::ConstIterator
UnorderedSet<T, Hash>::ConstIterator::operator++(int) {
    typename UnorderedSet<T, Hash>::ConstIterator temp = *this;
    ++(*this);
    return temp;
}

template<class T, class Hash>
typename UnorderedSet<T, Hash>::ConstIterator&
UnorderedSet<T, Hash>::ConstIterator::operator--() {
    --element;
    return *this;
}

template<class T, class Hash>
typename UnorderedSet<T, Hash>::ConstIterator
UnorderedSet<T, Hash>::ConstIterator::operator--(int) {
    typename UnorderedSet<T, Hash>::ConstIterator temp = *this;
    --(*this);
    return temp;
}

template<class T, class Hash>
const T* UnorderedSet<T, Hash>::ConstIterator::operator->() const {
    return &(*element);
}

template<class T, class Hash>
bool UnorderedSet<T, Hash>::ConstIterator::operator==(const typename UnorderedSet<T, Hash>::ConstIterator& other) const {
    return element == other.element;
}

template<class T, class Hash>
bool UnorderedSet<T, Hash>::ConstIterator::operator!=(const typename UnorderedSet<T, Hash>::ConstIterator& other) const {
    return element != other.element;
}

template<class T, class Hash>
UnorderedSet<T, Hash>::ConstIterator::ConstIterator(typename std::list<T>::const_iterator it) {
    element = it;
}

template<class T, class Hash>
UnorderedSet<T, Hash>::UnorderedSet() {
    hashTable.resize(8);
}

template<class T, class Hash>
void UnorderedSet<T, Hash>::insert(const T& element) {
    if (loadFactor() >= maxLoadFactor) {
        resize();
    }

    auto& slot = getHashTableSlot(element);

    auto iter = std::find_if(slot.begin(), slot.end(), [&element](const auto& it) { return *it == element; });

    if (iter != slot.end()) {
        return;
    }

    auto lastElementIterator = data.end();

    if (!slot.empty()) {
        lastElementIterator = slot.front();
        ++lastElementIterator;
    }

    auto insertedElementIterator = data.insert(lastElementIterator, element);

    slot.push_front(insertedElementIterator);
}

template<class T, class Hash>
void UnorderedSet<T, Hash>::remove(const T& element) {
    auto& slot = getHashTableSlot(element);

    slot.remove_if([this, &element](const auto& it) {
        if (*it == element) {
            data.erase(it);
            return true;
        }

        return false;
        });
}

template<class T, class Hash>
typename UnorderedSet<T, Hash>::ConstIterator
UnorderedSet<T, Hash>::remove(ConstIterator it) {
    auto& slot = getHashTableSlot(*it);

    auto nextIt = it.element;
    ++nextIt;

    slot.remove_if([&it](const auto& currIterator) {
        return currIterator == it.element;
        });

    data.erase(it.element);

    return ConstIterator(nextIt);
}

template<class T, class Hash>
typename UnorderedSet<T, Hash>::ConstIterator
UnorderedSet<T, Hash>::find(const T& element) {
    auto& slot = getHashTableSlot(element);

    auto it = std::find_if(slot.begin(), slot.end(), [&element](const auto& it) { return *it == element; });

    if (it == slot.end()) {
        return cend();
    }

    return ConstIterator(*it);
}

template<class T, class Hash>
void UnorderedSet<T, Hash>::clear() {
    data.clear();
    hashTable.clear();
    hashTable.resize(8);
}

template<class T, class Hash>
bool UnorderedSet<T, Hash>::empty() const {
    return data.empty();
}

template<class T, class Hash>
template<class Predicate>
void UnorderedSet<T, Hash>::erase_if(Predicate predicate) {
    auto it = data.begin();

    while (it != data.end()) {
        if (predicate(*it)) {
            auto& slot = getHashTableSlot(*it);

            slot.remove(it);

            it = data.erase(it);
        }
        else {
            ++it;
        }
    }
}

template<class T, class Hash>
std::forward_list<typename std::list<T>::iterator>& UnorderedSet<T, Hash>::getHashTableSlot(const T& element) {
    size_t hashCode = getHashCode(element);
    return hashTable[hashCode];
}

template<class T, class Hash>
void UnorderedSet<T, Hash>::resize() {
    size_t newSize = hashTable.size() * 2;
    hashTable.clear();
    hashTable.resize(newSize);

    for (auto it = data.begin(); it != data.end(); ++it) {
        size_t newHashCode = getHashCode(*it);
        hashTable[newHashCode].push_front(it);
    }
}

template<class T, class Hash>
size_t UnorderedSet<T, Hash>::getHashCode(const T& element) const {
    return getHash(element) % hashTable.size();
}

template<class T, class Hash>
double UnorderedSet<T, Hash>::loadFactor() const {
    return static_cast<double>(data.size() / hashTable.size());
}

template<class T, class Hash>
typename UnorderedSet<T, Hash>::ConstIterator
UnorderedSet<T, Hash>::cbegin() const {
    return ConstIterator(data.cbegin());
}

template<class T, class Hash>
typename UnorderedSet<T, Hash>::ConstIterator
UnorderedSet<T, Hash>::cend() const {
    return ConstIterator(data.cend());
}