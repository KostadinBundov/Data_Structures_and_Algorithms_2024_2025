# include <iostream>
#include <vector>

template <class T>
class KArryPriorityQueue {
public:
	KArryPriorityQueue(int k);
	KArryPriorityQueue(const std::vector<T>& input, int k);
	void push(const T& element);
	void pop();
	const T& peek() const;

	size_t size() const;
	bool isEmpty() const;

private:
	size_t k;

	void heapify(size_t index);
	std::vector<T> data;

	size_t getParentIndex(size_t index) const;
	std::vector<size_t> getChildrenIndecies(size_t parentIndex) const;
};

template<class T>
void KArryPriorityQueue<T>::heapify(size_t index) {
	size_t currIndex = index;

	while (true) {
		std::vector<size_t> children = getChildrenIndecies(currIndex);
		int currValue = data[currIndex];
		int maxChildIndex = -1;

		for (auto childIndex : children) {
			if (currValue <= data[childIndex]) {
				currValue = data[childIndex];
				maxChildIndex = childIndex;
			}
		}

		if (maxChildIndex == -1) {
			break;
		}

		std::swap(data[currIndex], data[maxChildIndex]);
		currIndex = maxChildIndex;
	}
}

template<class T>
size_t KArryPriorityQueue<T>::getParentIndex(size_t index) const {
	return index == 0 ? 0 : (index - 1) / k;
}

template<class T>
std::vector<size_t> KArryPriorityQueue<T>::getChildrenIndecies(size_t parentIndex) const {
	std::vector<size_t> children;

	for (int i = 1; i <= k; i++) {
		size_t currChildIndex = k * parentIndex + i;

		if (currChildIndex >= data.size()) {
			break;
		}

		children.push_back(currChildIndex);
	}

	return children;
}

template<class T>
KArryPriorityQueue<T>::KArryPriorityQueue(int k) {
	if (k < 1) {
		throw std::invalid_argument("K must be greater than 0!");
	}
	this->k = k;
}

template<class T>
KArryPriorityQueue<T>::KArryPriorityQueue(const std::vector<T>& input, int k) : KArryPriorityQueue(k) {
	data = input;

	for (int i = (input.size() - 1) / k; i >= 0; i--) {
		heapify(i);
	}
}

template<class T>
void KArryPriorityQueue<T>::push(const T& element) {
	data.push_back(element);

	size_t currElementIndex = data.size() - 1;
	size_t parentIndex = getParentIndex(currElementIndex);

	while (data[parentIndex] < data[currElementIndex]) {
		std::swap(data[parentIndex], data[currElementIndex]);

		currElementIndex = parentIndex;
		parentIndex = getParentIndex(currElementIndex);
	}
}

template<class T>
void KArryPriorityQueue<T>::pop() {
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
const T& KArryPriorityQueue<T>::peek() const {
	if (isEmpty()) {
		throw std::out_of_range("There are no elements in the queue!");
	}

	return data[0];
}

template<class T>
size_t KArryPriorityQueue<T>::size() const {
	return data.size();
}

template<class T>
bool KArryPriorityQueue<T>::isEmpty() const {
	return data.size() == 0;
}