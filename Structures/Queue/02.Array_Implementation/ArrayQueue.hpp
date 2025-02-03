#pragma once

#include <iostream>

template<class T>
class ArrayQueue {
public:
	ArrayQueue() {
		size = 0;
		capacity = 4;
		data = new T[capacity];
	}

	ArrayQueue(const ArrayQueue& other);
	ArrayQueue(ArrayQueue&& other);
	ArrayQueue& operator=(const ArrayQueue& other);
	ArrayQueue& operator=(ArrayQueue&& other);
	~ArrayQueue();

	void push(const T& element);
	void pop();
	const T& front() const;

	size_t getSize() const;
	bool isEmpty() const;

private:
	T* data;
	size_t size;
	size_t capacity;

	size_t first = 0;
	size_t last = 0;

	void resize(size_t newSize);
	void free();
	void copyFrom(const ArrayQueue& other);
	void moveFrom(ArrayQueue&& other);
};

template<class T>
ArrayQueue<T>::ArrayQueue(const ArrayQueue& other) {
	copyFrom(other);
}

template<class T>
ArrayQueue<T>::ArrayQueue(ArrayQueue&& other) {
	moveFrom(std::move(other));
}

template<class T>
ArrayQueue<T>& ArrayQueue<T>::operator=(const ArrayQueue& other) {
	if (this != &other) {
		free();
		copyFrom(other);
	}

	return *this;
}

template<class T>
ArrayQueue<T>& ArrayQueue<T>::operator=(ArrayQueue&& other) {
	if (this != &other) {
		free();
		moveFrom(std::move(other));
	}

	return *this;
}

template<class T>
ArrayQueue<T>::~ArrayQueue() {
	free();
}

template<class T>
void ArrayQueue<T>::push(const T& element) {
	if (size == capacity) {
		resize(2 * capacity);
	}

	data[last++] = element;
	last %= capacity;
	size++;
}

template<class T>
void ArrayQueue<T>::pop() {
	if (isEmpty()) {
		throw std::runtime_error("The queue is empty!");
	}

	first = (first + 1) % capacity;
	size--;
}

template<class T>
const T& ArrayQueue<T>::front() const {
	if (isEmpty()) {
		throw std::runtime_error("The queue is empty!");
	}

	return data[first];
}

template<class T>
size_t ArrayQueue<T>::getSize() const {
	return size;
}

template<class T>
bool ArrayQueue<T>::isEmpty() const {
	return size == 0;
}

template<class T>
void ArrayQueue<T>::resize(size_t newSize) {
	T* temp = data;
	data = new T[newSize];

	for (int i = 0; i < size; i++) {
		data[i] = temp[first++];
		first %= capacity;
	}

	first = 0;
	last = size;
	capacity = newSize;
	delete[] temp;
}

template<class T>
void ArrayQueue<T>::free() {
	delete[] data;
	data = nullptr;
	size = capacity = 0;
}

template<class T>
void ArrayQueue<T>::copyFrom(const ArrayQueue& other) {
	data = new T[other.capacity];

	size_t iter = other.first;

	for (int i = 0; i < other.size; i++) {
		data[i] = other.data[iter];
		iter %= other.capacity;
	}

	first = 0;
	last = other.size;

	size = other.size;
	capacity = other.capacity;
}

template<class T>
void ArrayQueue<T>::moveFrom(ArrayQueue&& other) {
	data = other.data;
	size = other.size;
	capacity = other.capacity;
	first = other.first;
	last = other.last;

	other.data = nullptr;
	other.size = other.capacity = 0;
}
