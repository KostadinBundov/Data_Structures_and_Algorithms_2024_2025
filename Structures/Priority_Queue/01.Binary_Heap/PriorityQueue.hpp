#pragma once

#include <vector>
#include <iostream>

template<class T, class Comparator = std::less<T>>
class PriorityQueue {
private:
	std::vector<T> data;
	Comparator compare;

	size_t getLeftChildIndex(size_t parentIndex) const { return 2 * parentIndex + 1; }
	size_t getRightChildIndex(size_t parentIndex) const { return 2 * parentIndex + 2; }
	size_t getParentIndex(size_t childIndex) const { return (childIndex - 1) / 2; }

	void heapify(size_t index);
public:
	PriorityQueue() = default;
	PriorityQueue(const std::vector<T>& input);

	void push(const T& element);
	void pop();

	const T& top() const;

	bool isEmpty() const { return data.size() == 0; }
	size_t getSize() const { return data.size(); }
};

template<class T, class Comparator>
void PriorityQueue<T, Comparator>::heapify(size_t index) {
	while (true) {
		size_t leftChildIndex = getLeftChildIndex(index);
		size_t rightChildIndex = getRightChildIndex(index);
		
		bool shouldGoLeft = leftChildIndex < data.size() && compare(data[index], data[leftChildIndex]);
		bool shouldGoRight = rightChildIndex < data.size() && compare(data[index], data[rightChildIndex]);

		if (shouldGoLeft && shouldGoRight) {
			if (compare(data[rightChildIndex], data[leftChildIndex])) {
				std::swap(data[index], data[leftChildIndex]);
				index = leftChildIndex;
			}
			else {
				std::swap(data[index], data[rightChildIndex]);
				index = rightChildIndex;
			}
		}
		else if (shouldGoLeft) {
			std::swap(data[index], data[leftChildIndex]);
			index = leftChildIndex;
		}
		else if (shouldGoRight) {
			std::swap(data[index], data[rightChildIndex]);
			index = rightChildIndex;
		}
		else {
			break;
		}
	}
}

template<class T, class Comparator>
PriorityQueue<T, Comparator>::PriorityQueue(const std::vector<T>& input) {
	data = input;

	for (int i = data.size() / 2 - 1; i >= 0; i--) {
		heapify(i);
	}
}

template<class T, class Comparator>
void PriorityQueue<T, Comparator>::push(const T& element) {
	data.push_back(element);

	size_t childIndex = data.size() - 1;
	size_t parentIndex = getParentIndex(childIndex);

	while (childIndex > 0 && compare(data[parentIndex], data[childIndex])) {
		std::swap(data[childIndex], data[parentIndex]);
		childIndex = parentIndex;
		parentIndex = getParentIndex(parentIndex);
	}
}

template<class T, class Comparator>
void PriorityQueue<T, Comparator>::pop() {
	if (data.empty()) {
		throw std::runtime_error("The queue is empty!");
	}

	std::swap(data[0], data[data.size() - 1]);
	data.pop_back();

	if (!data.empty()) {
		heapify(0);
	}
}

template<class T, class Comparator>
const T& PriorityQueue<T, Comparator>::top() const {
	if (data.empty()) {
		throw std::runtime_error("The queue is empty!");
	}

	return data[0];
}
