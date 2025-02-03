#pragma once

#include <iostream>

template<class T>
class ArrayStack {
public:
	ArrayStack();
	ArrayStack(const ArrayStack& other);
	ArrayStack(ArrayStack&& other);
	ArrayStack& operator=(const ArrayStack& other);
	ArrayStack& operator=(ArrayStack&& other);

	void pop();
	void push(const T& element);
	const T& top() const;

	size_t getSize() const;
	bool isEmpty() const;

private:
	T* data;
	size_t size;
	size_t capacity;

	void free();
	void copyFrom(const ArrayStack& other);
	void moveFrom(ArrayStack&& other);

	void resize(size_t size);
};

template<class T>
ArrayStack<T>::ArrayStack() {
	size = 0;
	capacity = 4;
	data = new T[capacity];
}

template<class T>
ArrayStack<T>::ArrayStack(const ArrayStack& other) {
	copyFrom(other);
}

template<class T>
ArrayStack<T>::ArrayStack(ArrayStack&& other) {
	moveFrom(std::move(other));
}

template<class T>
ArrayStack<T>& ArrayStack<T>::operator=(const ArrayStack<T>& other) {
	if (this != &other) {
		free();
		copyFrom(other);
	}

	return *this;
}

template<class T>
ArrayStack<T>& ArrayStack<T>::operator=(ArrayStack<T>&& other) {
	if (this != &other) {
		free();
		moveFrom(std::move(other));
	}

	return *this;
}

template<class T>
void ArrayStack<T>::pop() {
	if (isEmpty()) {
		throw std::runtime_error("The stack is empty!");
	}

	size--;

	if (size * 2 <= capacity && capacity > 1) {
		resize(capacity / 2);
	}
}

template<class T>
void ArrayStack<T>::push(const T& element) {
	if (size == capacity) {
		resize(2 * capacity);
	}

	data[size] = element;
	size++;
}

template<class T>
const T& ArrayStack<T>::top() const {
	if (isEmpty()) {
		throw std::runtime_error("The stack is empty!");
	}

	return data[size - 1];
}

template<class T>
void ArrayStack<T>::free() {
	delete[] data;
	size = 0;
	capacity = 4;
}

template<class T>
void ArrayStack<T>::copyFrom(const ArrayStack& other) {
	data = new T[other.capacity];

	for (int i = 0; i < other.size; i++) {
		data[i] = other.data[i];
	}

	size = other.size;
	capacity = other.capacity;
}

template<class T>
void ArrayStack<T>::moveFrom(ArrayStack&& other) {
	data = other.data;
	size = other.size;
	capacity = other.capacity;

	other.data = nullptr;
	other.size = other.capacity = 0;
}

template<class T>
void ArrayStack<T>::resize(size_t newSize) {
	T* temp = data;
	data = new T[newSize];

	for (int i = 0; i < size; i++) {
		data[i] = temp[i];
	}

	capacity = newSize;
	delete[] temp;
}

template<class T>
size_t ArrayStack<T>::getSize() const {
	return size;
}

template<class T>
bool ArrayStack<T>::isEmpty() const {
	return size == 0;
}