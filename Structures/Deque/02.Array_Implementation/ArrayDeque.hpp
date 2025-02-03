#pragma once

#include <iostream>

template<class T, class Allocator = std::allocator<T>>
class ArrayDeque {
public:
	ArrayDeque();
	ArrayDeque(const ArrayDeque& other);
	ArrayDeque(ArrayDeque&& other);
	ArrayDeque<T>& operator=(const ArrayDeque<T>& other);
	ArrayDeque<T>& operator=(ArrayDeque<T>&& other);
	~ArrayDeque();

	void push_back(const T& element);
	void push_back(T&& element);

	void push_front(const T& element);
	void push_front(T&& element);

	template<class... Args>
	void emplace_front(Args&&... args);

	template<class... Args>
	void emplace_back(Args&&... args);

	void pop_back();
	void pop_front();

	const T& front() const { return data[frontIndex]; }
	const T& back() const { return backIndex == 0 ? data[capacity - 1] : data[backIndex - 1]; }

	T& front() { return data[frontIndex]; }
	T& back() { return backIndex == 0 ? data[capacity - 1] : data[backIndex - 1]; }

	size_t getSize() const { return size; }
	bool isEmpty() const { return size == 0; }

	const T& operator[](size_t index) const { return data[(frontIndex + index) % capacity]; }
	T& operator[](size_t index) { return data[(frontIndex + index) % capacity]; }

	class Iterator {
	public:
		Iterator(size_t index, const ArrayDeque<T, Allocator>& context) : index(index), context(context) {}
		const T& operator*() const { return context[index]; }
		const T* operator->() const { return &context[index]; }

		Iterator& operator++() {
			index++;
			return *this;
		}
		Iterator operator++(int) {
			Iterator copy(*this);
			++(*this);
			return copy;
		}

		Iterator& operator--() {
			index--;
			return *this;
		}
		Iterator operator--(int) {
			Iterator copy(*this);
			--(*this);
			return copy;
		}

		Iterator operator+(size_t size) const {
			return Iterator(index + size, context);
		}
		Iterator operator-(size_t size) const {
			return Iterator(index - size, context);
		}

		bool operator==(const Iterator& other) const { return index == other.index; }
		bool operator!=(const Iterator& other) const { return index != other.index; }
	private:
		size_t index;
		const ArrayDeque<T, Allocator>& context;
	};
	class ConstIterator {
	public:
		ConstIterator(size_t index, const ArrayDeque<T, Allocator>& context) : index (index), context(context) {}
		const T& operator*() const { return context[index]; }
		const T* operator->() const { return &context[index]; }

		ConstIterator& operator++() {
			index++;
			return *this;
		}
		ConstIterator operator++(int) {
			ConstIterator copy(*this);
			++(*this);
			return copy;
		}

		ConstIterator& operator--() {
			index--;
			return *this;
		}
		ConstIterator operator--(int) {
			ConstIterator copy(*this);
			--(*this);
			return copy;
		}

		ConstIterator operator+(size_t size) const {
			return ConstIterator(index + size, context);
		}
		ConstIterator operator-(size_t size) const {
			return ConstIterator(index - size, context);
		}

		bool operator==(const ConstIterator& other) const { return index == other.index; }
		bool operator!=(const ConstIterator& other) const { return index != other.index; }
	private:
		size_t index;
		const ArrayDeque<T, Allocator>& context;
	};

	Iterator begin() { return Iterator(0, *this); }
	Iterator end() { return Iterator(size, *this); }
	ConstIterator cbegin() const { return ConstIterator(0, *this); }
	ConstIterator cend() const { return ConstIterator(size, *this); }

private:
	T* data = nullptr;
	size_t size = 0;
	size_t capacity;

	size_t frontIndex = 0;
	size_t backIndex = 0;

	Allocator allocator;

	void free();
	void copyFrom(const ArrayDeque<T>& other);
	void moveFrom(ArrayDeque<T>&& other);

	void resize(size_t newSize);

	size_t calculateCapacity() const;

	void moveForward(size_t& index) { index = (index + 1) % capacity; }
	void moveBackward(size_t& index) { index = index == 0 ? (capacity - 1) : (index - 1); }
};

template<class T, class Allocator>
ArrayDeque<T, Allocator>::ArrayDeque() {
	capacity = 8;
	data = allocator.allocate(capacity);
}

template<class T, class Allocator>
ArrayDeque<T, Allocator>::ArrayDeque(const ArrayDeque& other) {
	copyFrom(other);
}

template<class T, class Allocator>
ArrayDeque<T, Allocator>::ArrayDeque(ArrayDeque&& other) {
	moveFrom(std::move(other));
}

template<class T, class Allocator>
ArrayDeque<T>& ArrayDeque<T, Allocator>::operator=(const ArrayDeque<T>& other) {
	if (this != &other) {
		free();
		copyFrom(other);
	}

	return *this;
}

template<class T, class Allocator>
ArrayDeque<T>& ArrayDeque<T, Allocator>::operator=(ArrayDeque<T>&& other) {
	if (this != &other) {
		free();
		moveFrom(std::move(other));
	}

	return *this;
}

template<class T, class Allocator>
ArrayDeque<T, Allocator>::~ArrayDeque() {
	free();
}

template<class T, class Allocator>
void ArrayDeque<T, Allocator>::push_back(const T& element) {
	if (size >= capacity) {
		resize(calculateCapacity());
	}

	allocator.construct(&data[backIndex], element);
	moveForward(backIndex);
	size++;
}

template<class T, class Allocator>
void ArrayDeque<T, Allocator>::push_back(T&& element) {
	if (size >= capacity) {
		resize(calculateCapacity());
	}

	allocator.construct(&data[backIndex], std::move(element));
	moveForward(backIndex);
	size++;
}

template<class T, class Allocator>
void ArrayDeque<T, Allocator>::push_front(const T& element) {
	if (size >= capacity) {
		resize(calculateCapacity());
	}

	moveBackward(frontIndex);
	allocator.construct(&data[frontIndex], element);
	size++;
}

template<class T, class Allocator>
void ArrayDeque<T, Allocator>::push_front(T&& element) {
	if (size >= capacity) {
		resize(calculateCapacity());
	}

	moveBackward(frontIndex);
	allocator.construct(&data[frontIndex], std::move(element));
	size++;
}

template<class T, class Allocator>
void ArrayDeque<T, Allocator>::pop_back() {
	if (isEmpty()) {
		throw std::runtime_error("The deque is empty!");
	}

	moveBackward(backIndex);
	allocator.destroy(&data[backIndex]);
	size--;
}

template<class T, class Allocator>
void ArrayDeque<T, Allocator>::pop_front() {
	if (isEmpty()) {
		throw std::runtime_error("The deque is empty!");
	}

	allocator.destroy(&data[frontIndex]);
	moveForward(frontIndex);
	size--;
}

template<class T, class Allocator>
void ArrayDeque<T, Allocator>::free() {
	if (frontIndex == backIndex && size>= 1) {
		allocator.destroy(&data[frontIndex]);
		moveForward(frontIndex);
	}

	while (frontIndex != backIndex) {
		allocator.destroy(&data[frontIndex]);
		moveForward(frontIndex);
	}

	allocator.deallocate(data, capacity);
	data = nullptr;
	size = capacity = frontIndex = backIndex = 0;
}

template<class T, class Allocator>
void ArrayDeque<T, Allocator>::copyFrom(const ArrayDeque<T>& other) {
	capacity = other.capacity;
	data = allocator.allocate(other.capacity);

	for (int i = 0; i < other.size; i++) {
		push_back(other[i]);
	}
}

template<class T, class Allocator>
void ArrayDeque<T, Allocator>::moveFrom(ArrayDeque<T>&& other) {
	data = other.data;
	size = other.size;
	capacity = other.capacity;
	frontIndex = other.frontIndex;
	backIndex = other.backIndex;

	other.data = nullptr;
	other.size = other.capacity = other.frontIndex = other.backIndex = 0;
}

template<class T, class Allocator>
void ArrayDeque<T, Allocator>::resize(size_t newSize) {
	if (newSize == 0) {
		return;
	}

	T* newData = allocator.allocate(newSize);

	int includedElements = std::min(size, newSize);

	for (int i = 0; i < includedElements; i++) {
		allocator.construct(&newData[i], std::move(operator[](i)));
		allocator.destroy(&data[(frontIndex + i) % capacity]);
	}

	if (newSize < size)
	{
		for (int i = newSize; i < size; i++) {
			allocator.destroy(data + ((frontIndex + i) % capacity));
		}
	}

	allocator.deallocate(data, capacity);

	frontIndex = 0;
	backIndex = includedElements;
	capacity = newSize;
	data = newData;
}

template<class T, class Allocator>
size_t ArrayDeque<T, Allocator>::calculateCapacity() const {
	if (capacity == 0) {
		return 1;
	}

	return 2 * capacity;
}

template<class T, class Allocator>
template<class ...Args>
void ArrayDeque<T, Allocator>::emplace_front(Args && ...args) {
	if (size >= capacity) {
		resize(calculateCapacity());
	}

	moveBackward(frontIndex);
	allocator.construct(&data[frontIndex], std::forward<Args>(args)...);
	size++;
}

template<class T, class Allocator>
template<class ...Args>
void ArrayDeque<T, Allocator>::emplace_back(Args && ...args) {
	if (size >= capacity) {
		resize(calculateCapacity());
	}

	allocator.construct(&data[backIndex], std::forward<Args>(args)...);
	moveForward(backIndex);
	size++;
}