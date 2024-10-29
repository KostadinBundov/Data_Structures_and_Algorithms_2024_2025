#pragma once
#include <iostream>
#include "Const_Iterator.hpp"
#include "Iterator.hpp"
#include "Reverse_Iterator.hpp"

static constexpr size_t GROWTH_FACTOR = 2;

template <typename T>
class Vector {
public:
	Vector() = default;
	explicit Vector(size_t size);
	Vector(size_t size, const T& initial);

	Vector(const Vector& other);
	Vector& operator=(const Vector& other);

	Vector(Vector&& other);
	Vector& operator=(Vector&& other);

	~Vector();

	void push_back(const T& element);
	void push_back(T&& element);
	void pop_back();

	void erase(Const_Iterator<T> position);
	void erase(Const_Iterator<T> start, Const_Iterator<T> end);

	void clear();

	template <class... Args>
	void emplace_back(Args&&... args);

	void shrink_to_fit();

	T& operator[](int index);
	const T& operator[](int index) const;

	void reserve(size_t n);
	void resize(size_t n);

	T* data();
	size_t size() const;
	size_t capacity() const;
	bool empty() const;

	Iterator<T> begin();
	Iterator<T> end();

	Const_Iterator<T> c_begin() const;
	Const_Iterator<T> c_end() const;

	Reverse_Iterator<T> r_begin();
	Reverse_Iterator<T> r_end();

	T& back();
	const T& back() const;

	T& front();
	const T& front() const;

private:
	T* _data = nullptr;
	size_t _size = 0;
	size_t _capacity = 0;

	void free();
	void copyFrom(const Vector& other);
	void moveFrom(Vector&& other);

	size_t calculate_capacity() const;
};

template <typename T>
Vector<T>::Vector(size_t size) {
	_data = static_cast<T*>(operator new(size * sizeof(T)));
	_size = size;
	_capacity = size;
}

template <typename T>
Vector<T>::Vector(size_t size, const T& initial) : Vector(size) {
	for (int i = 0; i < size; i++) {
		new (&_data[i]) T(initial);
	}
}

template <typename T>
Vector<T>::Vector(const Vector& other) {
	copyFrom(other);
}

template <typename T>
Vector<T>& Vector<T>::operator=(const Vector& other) {
	if (this != &other) {
		free();
		copyFrom(other);
	}
	return *this;
}

template <typename T>
Vector<T>::Vector(Vector&& other) {
	moveFrom(std::move(other));
}

template <typename T>
Vector<T>& Vector<T>::operator=(Vector&& other) {
	if (this != &other) {
		free();
		moveFrom(std::move(other));
	}
	return *this;
}

template <typename T>
Vector<T>::~Vector() {
	free();
}

template <typename T>
void Vector<T>::free() {
	for (size_t i = 0; i < _size; i++) {
		_data[i].~T();
	}

	operator delete (_data, _capacity * sizeof(T));

	_data = nullptr;
	_size = 0;
	_capacity = 0;
}

template <typename T>
void Vector<T>::copyFrom(const Vector& other) {
	_data = static_cast<T*>(operator new(sizeof(T) * other._capacity));

	for (int i = 0; i < other._size; i++) {
		new (&_data[i]) T(other[i]);
	}

	_size = other._size;
	_capacity = other._capacity;
}

template <typename T>
void Vector<T>::moveFrom(Vector&& other) {
	_size = other._size;
	_capacity = other._capacity;
	_data = other._data;

	other._size = 0;
	other._capacity = 0;
	other._data = nullptr;
}

template <typename T>
T& Vector<T>::operator[](int index) {
	return _data[index];
}

template <typename T>
const T& Vector<T>::operator[](int index) const {
	return _data[index];
}

template <typename T>
void Vector<T>::reserve(size_t capacity) {
	if (capacity <= _capacity) {
		return;
	}

	T* new_data = static_cast<T*>(operator new(capacity * sizeof(T)));

	for (size_t i = 0; i < _size; i++) {
		new (&new_data[i]) T(std::move(_data[i]));
		_data[i].~T();
	}

	operator delete(_data, _capacity * sizeof(T));

	_data = new_data;
	_capacity = capacity;
}

template <class T>
void Vector<T>::resize(size_t n)
{
	if (n < size()) {
		for (size_t i = n; i < size(); i++) {
			(_data + i)->~T();
		}

		_size = n;
	}
	else if (n > size()) {
		if (n <= capacity()) {
			for (size_t i = size(); i < n; i++) {
				new (&_data[i]) T();
			}

			_size = n;
		}
		else {
			T* new_data = static_cast<T*>(operator new(n * sizeof(T)));

			for (size_t i = 0; i < size(); i++) {
				new (&new_data[i]) T(std::move(_data[i]));
			}

			for (size_t i = size(); i < n; i++) {
				new (&new_data[i]) T();
			}

			operator delete(_data, capacity() * sizeof(T));

			_data = new_data;
			_capacity = n;
			_size = n;
		}
	}
}

template <typename T>
T* Vector<T>::data() {
	return _data;
}

template <typename T>
size_t Vector<T>::size() const {
	return _size;
}

template <typename T>
size_t Vector<T>::capacity() const {
	return _capacity;
}

template <typename T>
bool Vector<T>::empty() const {
	return _size == 0;
}

template <typename T>
void Vector<T>::push_back(const T& element) {
	if (_size >= _capacity) {
		reserve(calculate_capacity());
	}

	new (&_data[_size++]) T(element);
}

template <typename T>
void Vector<T>::push_back(T&& element) {
	if (_size >= _capacity) {
		reserve(calculate_capacity());
	}

	new (&_data[_size++]) T(std::move(element));
}

template <typename T>
void Vector<T>::pop_back() {
	if (!empty()) {
		_data[--_size].~T();
	}
}

template <typename T>
void Vector<T>::erase(Const_Iterator<T> position) {
	erase(position, position + 1);
}

template <typename T>
void Vector<T>::erase(Const_Iterator<T> start, Const_Iterator<T> end) {
	int deletedCount = end - start;

	if (deletedCount <= 0) {
		return;
	}

	int startIndex = start - c_begin();
	int endIndex = end - c_begin();

	if (end != c_end()) {
		for (int i = endIndex; i < _size; i++) {
			new (&_data[startIndex++]) T(std::move(_data[i]));
		}
	}

	for (int i = startIndex; i < _size; i++) {
		_data[i].~T();
	}

	_size -= deletedCount;
}

template <typename T>
void Vector<T>::clear() {
	for (size_t i = 0; i < _size; i++) {
		_data[i].~T();
	}

	_size = 0;
}

template <typename T>
size_t Vector<T>::calculate_capacity() const {
	return _capacity == 0 ? 1 : _capacity * GROWTH_FACTOR;
}

template <typename T>
Iterator<T> Vector<T>::begin() {
	return Iterator<T>(_data);
}

template <typename T>
Iterator<T> Vector<T>::end() {
	return Iterator<T>(_data + _size);
}

template <typename T>
Const_Iterator<T> Vector<T>::c_begin() const {
	return Const_Iterator<T>(_data);
}

template <typename T>
Const_Iterator<T> Vector<T>::c_end() const {
	return Const_Iterator<T>(_data + _size);
}

template <typename T>
Reverse_Iterator<T> Vector<T>::r_begin() {
	return _size > 0 ? Reverse_Iterator<T>(_data + _size - 1) : Reverse_Iterator<T>(nullptr);
}

template <typename T>
Reverse_Iterator<T> Vector<T>::r_end() {
	return _size > 0 ? Reverse_Iterator<T>(_data - 1) : Reverse_Iterator<T>(nullptr);
}

template <typename T>
T& Vector<T>::back() {
	return _data[_size - 1];
}

template <typename T>
const T& Vector<T>::back() const {
	return _data[_size - 1];
}

template <typename T>
T& Vector<T>::front() {
	return _data[0];
}

template <typename T>
const T& Vector<T>::front() const {
	return _data[0];
}

template<typename T>
template<class ...Args>
inline void Vector<T>::emplace_back(Args && ...args)
{
	if (size() == capacity()) {
		reserve(calculate_capacity());
	}

	new (&_data[_size++]) T(std::forward<Args>(args)...);
}

template <class T>
void Vector<T>::shrink_to_fit()
{
	if (capacity() == size())
		return;

	T* new_data = static_cast<T*>(operator new(size() * sizeof(T)));

	for (size_t i = 0; i < size(); i++)
	{
		new (&new_data[i]) T(std::move(_data[i]));
		_data[i].~T();
	}
	operator delete(_data, capacity() * sizeof(T));

	_capacity = _size;
	_data = new_data;
}
