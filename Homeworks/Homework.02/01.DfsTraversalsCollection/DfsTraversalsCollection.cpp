#include "DfsTraversalsCollection.h"

void DfsTraversalsCollection::getArrayPermutations(std::vector<int>& arr, std::vector<std::vector<int>>& permutations, size_t index) const {
	if (index == arr.size()) {
		permutations.push_back(arr);
		return;
	}

	for (int i = index; i < arr.size(); i++) {
		std::swap(arr[index], arr[i]);
		getArrayPermutations(arr, permutations, index + 1);
		std::swap(arr[index], arr[i]);
	}
}

void DfsTraversalsCollection::getAllGraphTraversals(std::vector<std::vector<int>>& adjacencyList, size_t vertexIndex, size_t startIndex) {
	if (vertexIndex == adjacencyList.size()) {
		traversals.insert(Traversal(adjacencyList, startIndex));
		return;
	}

	std::vector<std::vector<int>> neighboursPermutations;
	getArrayPermutations(adjacencyList[vertexIndex], neighboursPermutations, 0);

	for (auto permutation : neighboursPermutations) {
		adjacencyList[vertexIndex] = permutation;
		getAllGraphTraversals(adjacencyList, vertexIndex + 1, startIndex);
	}
}

DfsTraversalsCollection::DfsTraversalsCollection(std::vector<std::vector<int>> graph, size_t startIndex) {
	getAllGraphTraversals(graph, 0, startIndex);
}

DfsTraversalsCollection::ConstIterator::ConstIterator(std::set<Traversal>::iterator it) : it(it) { }

const Traversal& DfsTraversalsCollection::ConstIterator::operator*() const {
	return *it;
}

const Traversal* DfsTraversalsCollection::ConstIterator::operator->() const {
	return &(*it);
}

DfsTraversalsCollection::ConstIterator& DfsTraversalsCollection::ConstIterator::operator++() {
	++it;
	return *this;
}

DfsTraversalsCollection::ConstIterator DfsTraversalsCollection::ConstIterator::operator++(int) {
	ConstIterator temp = *this;
	++it;
	return temp;
}

DfsTraversalsCollection::ConstIterator& DfsTraversalsCollection::ConstIterator::operator--() {
	--it;
	return *this;
}

DfsTraversalsCollection::ConstIterator DfsTraversalsCollection::ConstIterator::operator--(int) {
	ConstIterator temp = *this;
	--it;
	return temp;
}

bool DfsTraversalsCollection::ConstIterator::operator==(const ConstIterator& other) const {
	return it == other.it;
}

bool DfsTraversalsCollection::ConstIterator::operator!=(const ConstIterator& other) const {
	return it != other.it;
}