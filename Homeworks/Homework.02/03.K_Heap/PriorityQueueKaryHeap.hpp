# include <iostream>
#include <vector>

//https://w3.cs.jmu.edu/spragunr/CS228_S14/lectures/trees/trees.pdf - Slide 13
//from here I take the idea of what is the count of non-leaf vertecies in the tree
//so the creation of a heap from a random vector to be possible

template <class T>
class PriorityQueueKaryHeap {
public:
	PriorityQueueKaryHeap(int k);
	PriorityQueueKaryHeap(const std::vector<T>& input, int k);
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
void PriorityQueueKaryHeap<T>::heapify(size_t index) {
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
size_t PriorityQueueKaryHeap<T>::getParentIndex(size_t index) const {
	return index == 0 ? 0 : (index - 1) / k;
}

template<class T>
std::vector<size_t> PriorityQueueKaryHeap<T>::getChildrenIndecies(size_t parentIndex) const{
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
PriorityQueueKaryHeap<T>::PriorityQueueKaryHeap(int k) {
	if (k < 1) {
		throw std::invalid_argument("K must be greater than 0!");
	}
	this->k = k;
}

template<class T>
PriorityQueueKaryHeap<T>::PriorityQueueKaryHeap(const std::vector<T>& input, int k) : PriorityQueueKaryHeap(k) {
	data = input;

	for (int i = (input.size() - 1) / k; i >= 0; i--) {
		heapify(i);
	}
}

template<class T>
void PriorityQueueKaryHeap<T>::push(const T& element) {
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
void PriorityQueueKaryHeap<T>::pop() {
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
const T& PriorityQueueKaryHeap<T>::peek() const {
	if (isEmpty()) {
		throw std::out_of_range("There are no elements in the queue!");
	}

	return data[0];
}

template<class T>
size_t PriorityQueueKaryHeap<T>::size() const {
	return data.size();
}

template<class T>
bool PriorityQueueKaryHeap<T>::isEmpty() const {
	return data.size() == 0;
}