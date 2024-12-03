# include <iostream>
#include <vector>

template <class T>
class PriorityQueue {
private:
	void heapify(size_t index);
	std::vector<T> data;

	static size_t getParentIndex(size_t index);
	static size_t getLeftChildIndex(size_t index);
	static size_t getRightChildIndex(size_t index);

public :
	void push(const T& element);
	void pop();
	const T& peek() const;

	size_t size() const;
	bool isEmpty() const;
};

template<class T>
void PriorityQueue<T>::heapify(size_t index) {
	size_t currIndex = index;

	while (true) {
		size_t leftChildIndex = getLeftChildIndex(currIndex);
		size_t rightChildIndex = getRightChildIndex(currIndex);

		bool shouldGoLeft = leftChildIndex < data.size() && data[currIndex] <= data[leftChildIndex];
		bool shouldGoRight = rightChildIndex < data.size() && data[currIndex] <= data[rightChildIndex];

		if (shouldGoLeft && shouldGoRight) {
			if (data[leftChildIndex] >= data[rightChildIndex]) {
				std::swap(data[leftChildIndex], data[currIndex]);
				currIndex = leftChildIndex;
			}
			else {
				std::swap(data[rightChildIndex], data[currIndex]);
				currIndex = rightChildIndex;
			}
		}
		else if (shouldGoLeft) {
			std::swap(data[currIndex], data[leftChildIndex]);
			currIndex = leftChildIndex;
		}
		else if (shouldGoRight) {
			std::swap(data[currIndex], data[rightChildIndex]);
			currIndex = rightChildIndex;
		}
		else {
			break;
		}
	}
}

template<class T>
size_t PriorityQueue<T>::getParentIndex(size_t index) {
	return index == 0 ? 0 : (index - 1) / 2;
}

template<class T>
size_t PriorityQueue<T>::getLeftChildIndex(size_t index) {
	return 2 * index + 1;
}

template<class T>
size_t PriorityQueue<T>::getRightChildIndex(size_t index) {
	return 2 * index + 2;
}

template<class T>
void PriorityQueue<T>::push(const T& element) {
	data.push_back(element);

	size_t currElementIndex = data.size() - 1;
	size_t parentIndex = getParentIndex(currElementIndex);

	while (data[parentIndex] < data[currElementIndex]) {
		std::swap(data[parentIndex], data[currElementIndex]);

		currElementIndex = parentIndex;
		size_t parentIndex = getParentIndex(currElementIndex);
	}
}

template<class T>
void PriorityQueue<T>::pop() {
	if (isEmpty()) {
		throw std::out_of_range("There are no elements in the queue!");
	}

	data[0] = data[data.size() - 1];
	data.pop_back();

	if (data.size() != 0) {
		heapify(0);
	}
}

template<class T>
const T& PriorityQueue<T>::peek() const {
	if (isEmpty()) {
		throw std::out_of_range("There are no elements in the queue!");
	}

	return data[0];
}

template<class T> 
size_t PriorityQueue<T>::size() const {
	return data.size();
}

template<class T>
bool PriorityQueue<T>::isEmpty() const {
	return data.size() == 0;
}

