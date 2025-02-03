#pragma once

#include <iostream>
#include <memory>

namespace Constraints {
	constexpr size_t GROWTH_FACTOR = 2;
}

template<class T, class Allocator = std::allocator<T>>
class Vector {
public:
	Vector() = default;
	Vector(size_t size);
	Vector(size_t size, const T& initial);
	Vector(const Vector<T>& other);
	Vector(Vector<T>&& other);
	Vector<T>& operator=(const Vector<T>& other);
	Vector<T>& operator=(Vector<T>&& other);
	~Vector();

	void push_back(const T& other);
	void push_back(T&& other);

	template<class... Args>
	void emplace_back(Args&&... args);

	void pop_back();

	size_t getSize() const { return size; }
	size_t getCapacity() const { return capacity; }
	bool isEmpty() const { return size == 0; }

	T* getData() { return data; }

	const T& front() const { return data[0]; }
	T& front() { return data[0]; }

	const T& back() const { return data[size - 1]; }
	T& back() { return data[size - 1]; }

	void resize(size_t newSize);
	void shrink_to_fit();
	void reserve(size_t newSize);

	class ConstIterator {
	public:
		ConstIterator(T* pointer) : pointer(pointer) { }
		const T& operator*() const { return *pointer; }
		const T* operator->() const { return pointer; }

		ConstIterator& operator++() {
			pointer++;
			return *this;
		}
		ConstIterator operator++(int) const {
			ConstIterator copy(*this);
			++(*this);
			return copy;
		}

		ConstIterator& operator--() {
			pointer--;
			return *this;
		}
		ConstIterator operator--(int) const {
			ConstIterator copy(*this);
			--(*this);
			return copy;
		}

		ConstIterator operator+(size_t size) const {
			return ConstIterator(pointer + size);
		}
		ConstIterator operator-(size_t size) const {
			return ConstIterator(pointer - size);
		}

		int operator-(const ConstIterator& other) const {
			return pointer - other.pointer;
		}


		bool operator==(const ConstIterator& other) const { return pointer == other.pointer; }
		bool operator!=(const ConstIterator& other) const { return pointer != other.pointer; }
	private:
		T* pointer;
	};

	class Iterator {
	public:
		Iterator(T* pointer) : pointer(pointer) { }
		T& operator*() { return *pointer; }
		T* operator->() { return pointer; }

		Iterator& operator++() {
			pointer++;
			return *this;
		}
		Iterator operator++(int) const {
			Iterator copy(*this);
			++(*this);
			return copy;
		}

		Iterator& operator--() {
			pointer--;
			return *this;
		}
		Iterator operator--(int) const {
			Iterator copy(*this);
			--(*this);
			return copy;
		}

		Iterator operator+(size_t size) const {
			return Iterator(pointer + size);
		}
		Iterator operator-(size_t size) const {
			return Iterator(pointer - size);
		}

		operator ConstIterator() const {
			return ConstIterator(pointer);
		}

		bool operator==(const Iterator& other) const { return pointer == other.pointer; }
		bool operator!=(const Iterator& other) const { return pointer != other.pointer; }
	private:
		T* pointer;
	};

	class ReversedIterator {
	public:
		ReversedIterator(T* pointer) : pointer(pointer) { }
		T& operator*() { return *pointer; }
		T* operator->() { return pointer; }

		ReversedIterator& operator++() {
			pointer--;
			return *this;
		}
		ReversedIterator operator++(int) const {
			ReversedIterator copy(*this);
			--(*this);
			return copy;
		}

		ReversedIterator& operator--() {
			pointer++;
			return *this;
		}
		ReversedIterator operator--(int) const {
			ReversedIterator copy(*this);
			++(*this);
			return copy;
		}

		ReversedIterator operator+(size_t size) const {
			return ReversedIterator(pointer - size);
		}
		ReversedIterator operator-(size_t size) const {
			return ReversedIterator(pointer + size);
		}

		bool operator==(const ReversedIterator& other) const { return pointer == other.pointer; }
		bool operator!=(const ReversedIterator& other) const { return pointer != other.pointer; }
	private:
		T* pointer;
	};

	Iterator begin() { return Iterator(data); }
	Iterator end() { return Iterator(&data[size]); }
	
	ConstIterator cbegin() const { return ConstIterator(data); }
	ConstIterator cend() const { return ConstIterator(&data[size]); }

	ReversedIterator rbegin() { return size > 0 ? ReversedIterator(&data[size - 1]) : ReversedIterator(nullptr); }
	ReversedIterator rend() { return size > 0 ? ReversedIterator(data - 1) : ReversedIterator(nullptr); }

	void erase(const ConstIterator& iter);
	void erase(const ConstIterator& begin, const ConstIterator& end);

	void emplace(const ConstIterator& iter, const T& element) {
		size_t index = iter - begin();
		
		if (size == capacity) {
			reserve(calculateCapacity());
		}

		for (int i = size; i >  index; i--) {
			data[i] = std::move(data[i - 1]);
		}

		allocator.construct(&data[index], element);

		size++;
	}

	const T& operator[](size_t index) const { return data[index]; }
	T& operator[](size_t index) { return data[index]; }

	void clear();

private:
	T* data = nullptr;
	size_t size = 0;
	size_t capacity = 0;

	Allocator allocator;

	void free();
	void copyFrom(const Vector<T>& other);
	void moveFrom(Vector<T>&& other);

	size_t calculateCapacity() const;
};

template<class T, class Allocator>
Vector<T, Allocator>::Vector(size_t size) : size(size), capacity(size) {
	data = allocator.allocate(size);

	for (int i = 0; i < size; i++) {
		allocator.construct(&data[i]);
	}
}

template<class T, class Allocator>
Vector<T, Allocator>::Vector(size_t size, const T& initial) : capacity(size), size(size) {
	data = allocator.allocate(size);

	for (int i = 0; i < size; i++) {
		allocator.construct(&data[i], initial);
	}
}

template<class T, class Allocator>
Vector<T, Allocator>::Vector(const Vector<T>& other) {
	copyFrom(other);
}

template<class T, class Allocator>
Vector<T, Allocator>::Vector(Vector<T>&& other) {
	moveFrom(std::move(other));
}

template<class T, class Allocator>
Vector<T>& Vector<T, Allocator>::operator=(const Vector<T>& other) {
	if (this != &other) {
		free();
		copyFrom(other);
	}

	return *this;
}

template<class T, class Allocator>
Vector<T>& Vector<T, Allocator>::operator=(Vector<T>&& other) {
	if (this != &other) {
		free();
		moveFrom(std::move(other));
	}

	return *this;
}

template<class T, class Allocator>
Vector<T, Allocator>::~Vector() {
	free();
}

template<class T, class Allocator>
void Vector<T, Allocator>::push_back(const T& other) {
	if (size >= capacity) {
		reserve(calculateCapacity());
	}

	allocator.construct(&data[size], other);
	size++;
}

template<class T, class Allocator>
void Vector<T, Allocator>::push_back(T&& other) {
	if (size >= capacity) {
		reserve(calculateCapacity());
	}

	allocator.construct(&data[size], std::move(other));
	size++;
}

template<class T, class Allocator>
void Vector<T, Allocator>::pop_back() {
	if (size == 0) {
		throw std::runtime_error("The vector is empty!");
	}

	allocator.destroy(&data[size - 1]);
	size--;
}

template<class T, class Allocator>
void Vector<T, Allocator>::erase(const ConstIterator& iter) {
	erase(iter, iter + 1);
}

template<class T, class Allocator>
void Vector<T, Allocator>::erase(const ConstIterator& begin, const ConstIterator& end) {
	int elementsToDelete = end - begin;

	if (elementsToDelete <= 0) {
		return;
	}

	size_t startIndex = begin - cbegin();
	size_t endIndex = end - cbegin();

	if (end != cend()) {
		size_t indexToAttach = startIndex;

		for (int i = endIndex; i < size; i++) {
			data[indexToAttach++] = std::move(data[i]);
		}
	}

	for (int i = size - elementsToDelete; i < size; i++) {
		allocator.destroy(&data[i]);
	}

	size -= elementsToDelete;
}

template<class T, class Allocator>
void Vector<T, Allocator>::resize(size_t newSize) {
	if (size < newSize) {
		if (newSize <= capacity) {
			for (int i = size; i < newSize; i++) {
				allocator.construct(&data[i], std::move(data[i]));
			}
			size = newSize;
		}
		else {
			T* newData = allocator.allocate(newSize);

			for (int i = 0; i < size; i++) {
				allocator.construct(&newData[i], std::move(data[i]));
			}

			for (int i = size; i < newSize; i++) {
				allocator.construct(&newData[i]);
			}

			allocator.deallocate(data, capacity);

			data = newData;
			size = capacity = newSize;
		}
	}
	else if (size > newSize) {
		for (int i = newSize; i > size; i++) {
			allocator.destroy(&data[i]);
		}

		size = newSize;
	}
}

template<class T, class Allocator>
void Vector<T, Allocator>::shrink_to_fit() {
	if (size == capacity) {
		return;
	}

	T* newData = allocator.allocate(size);

	for (int i = 0; i < size; i++) {
		allocator.construct(&newData[i], std::move(data[i]));
	}

	allocator.deallocate(data, capacity);

	data = newData;
	capacity = size;
}

template<class T, class Allocator>
void Vector<T, Allocator>::clear() {
	for (int i = 0; i < size; i++) {
		allocator.destroy(&data[i]);
	}

	size = 0;
}

template<class T, class Allocator>
void Vector<T, Allocator>::free() {
	for (int i = 0; i < size; i++) {
		allocator.destroy(&data[i]);
	}

	allocator.deallocate(data, capacity);

	size = capacity = 0;
	data = nullptr;
}

template<class T, class Allocator>
void Vector<T, Allocator>::copyFrom(const Vector<T>& other) {
	data = allocator.allocate(other.capacity);

	for (int i = 0; i < other.size; i++) {
		allocator.construct(&data[i], other.data[i]);
	}

	size = other.size;
	capacity = other.capacity;
}

template<class T, class Allocator>
void Vector<T, Allocator>::moveFrom(Vector<T>&& other) {
	data = other.data;
	size = other.size;
	capacity = other.capacity;

	other.data = nullptr;
	other.size = other.capacity = 0;
}

template<class T, class Allocator>
size_t Vector<T, Allocator>::calculateCapacity() const {
	if (capacity == 0) {
		return 1;
	}

	return capacity * Constraints::GROWTH_FACTOR;
}

template<class T, class Allocator>
void Vector<T, Allocator>::reserve(size_t newSize) {
	T* newData = allocator.allocate(newSize);

	for (int i = 0; i < size; i++) {
		allocator.construct(&newData[i], std::move(data[i]));
	}

	allocator.deallocate(data, capacity);

	data = newData;
	capacity = newSize;
}

template<class T, class Allocator>
template<class ...Args>
void Vector<T, Allocator>::emplace_back(Args && ...args) {
	if (size == capacity) {
		reserve(calculateCapacity());
	}

	allocator.construct(&data[size++], std::forward<Args>(args)...);
}