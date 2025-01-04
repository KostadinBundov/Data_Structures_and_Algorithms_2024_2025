#pragma once
#include <iostream>
#include <memory>

namespace Constants {
    constexpr unsigned BUCKET_SIZE = 8;
    constexpr unsigned GROWTH_FACTOR = 1;
}

template <class Allocator = std::allocator<uint8_t>>
class Vector {
private:
    class Iterator;
    class ConstIterator;

    Allocator _allocator;

    uint8_t* data = nullptr;
    size_t _size = 0;
    size_t _capacity = 0;

    void copyFrom(const Vector& other);
    void moveFrom(Vector&& other);
    void free();

    void resize(size_t size);
    size_t calculateCapacity() const;
public:
    class BitReference {
    private:
        friend class Iterator;
        friend class Vector;

        uint8_t* bucket;
        int bitIndex;

    public:
        BitReference(uint8_t* bucket, int bitIndex) : bucket(bucket), bitIndex(bitIndex) { }

        BitReference& operator=(bool value);
        operator bool() const;
    };

    class Iterator {
    private:
        friend class Vector;
        BitReference reference;

    public:
        Iterator(BitReference reference) : reference(reference) { }

        operator ConstIterator() const {
            return ConstIterator(reference);
        }

        BitReference operator*();
        BitReference* operator->();

        Iterator& operator++();
        Iterator operator++(int);

        Iterator& operator--();
        Iterator operator--(int);

        Iterator operator+(int n) const;
        Iterator operator-(int n) const;

        bool operator==(const Iterator& other) const;
        bool operator!=(const Iterator& other) const;
    };

    class ConstIterator {
    private:
        friend class Vector;
        BitReference reference;

    public:
        ConstIterator(BitReference reference) : reference(reference) { }

        const BitReference operator*() const;
        const BitReference* operator->() const;

        ConstIterator operator+(int n) const;
        ConstIterator operator-(int n) const;

        bool operator==(const ConstIterator& other) const;
        bool operator!=(const ConstIterator& other) const;
    };

    class ReverseIterator {
    private:
        friend class Vector;
        BitReference reference;

    public:
        ReverseIterator(BitReference reference) : reference(reference) { }

        BitReference operator*();
        BitReference* operator->();

        ReverseIterator& operator++();
        ReverseIterator operator++(int);

        ReverseIterator& operator--();
        ReverseIterator operator--(int);

        ReverseIterator operator+(int n) const;
        ReverseIterator operator-(int n) const;

        bool operator==(const ReverseIterator& other) const;
        bool operator!=(const ReverseIterator& other) const;
    };

    Vector() = default;
    explicit Vector(size_t size);
    Vector(size_t size, uint8_t initial);

    Vector(const Vector& other);
    Vector(Vector&& other) noexcept;

    Vector& operator=(const Vector& other);
    Vector& operator=(Vector&& other) noexcept;

    ~Vector();

    size_t size() const;
    size_t capacity() const;
    bool isEmpty() const;

    void push_back(bool value);

    void pop_back();
    void pop_front();

    void insert(ConstIterator it, bool value);
    void remove(Iterator it);

    BitReference operator[](int index);
    const BitReference operator[](int index) const;

    Iterator begin();
    Iterator end();

    ConstIterator cbegin() const;
    ConstIterator cend() const;

    ReverseIterator rbegin();
    ReverseIterator rend();
};