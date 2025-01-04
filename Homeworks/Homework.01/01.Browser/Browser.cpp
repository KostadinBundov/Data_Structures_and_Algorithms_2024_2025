#include "Browser.h"

void Browser::copyFrom(const Browser& other) {
	head = new Node(other.head->data);

	if (other.head == other.tail) {
		tail = current = head;
		return;
	}

	Node* iter = head;
	Node* otherIter = other.head->next;

	while (otherIter) {
		iter->next = new Node(otherIter->data);
		iter->next->prev = iter;

		iter = iter->next;

		if (otherIter == other.current) {
			current = iter;
		}

		otherIter = otherIter->next;
	}

	tail = iter;
}

void Browser::moveFrom(Browser&& other) {
	head = other.head;
	other.head = nullptr;

	tail = other.tail;
	other.tail = nullptr;

	current = other.current;
	other.current = nullptr;
}

void Browser::free() {
	Node* iter = head;

	while (iter) {
		Node* toDelete = iter;
		iter = iter->next;
		delete toDelete;
	}

	head = current = tail = nullptr;
}

bool Browser::sortByURLComparator(Node* first, Node* second) {
	if (first->data.getURL().compare(second->data.getURL()) < 0) {
		return true;
	}
	else if (first->data.getURL().compare(second->data.getURL()) > 0) {
		return false;
	}
	else {
		return first->data.getTimestamp() <= second->data.getTimestamp();
	}
}

bool Browser::sortByTimeStampComparator(Node* first, Node* second) {
	if (first->data.getTimestamp() < second->data.getTimestamp()) {
		return true;
	}
	else if (first->data.getTimestamp() > second->data.getTimestamp()) {
		return false;
	}
	else {
		return first->data.getURL().compare(second->data.getURL()) <= 0;
	}
}

void Browser::pushBack(Node*& resultBegin, Node*& resultEnd, Node* curr) {
	if (!resultBegin) {
		resultBegin = resultEnd = curr;
		curr->prev = nullptr;
	}
	else {
		resultEnd->next = curr;
		curr->prev = resultEnd;
		resultEnd = curr;
	}
}

Browser::Node* Browser::findMiddle(Node* list) const {
	Node* slow = list;
	Node* fast = list->next;

	while (fast && fast->next) {
		slow = slow->next;
		fast = fast->next->next;
	}

	return slow;
}

Browser::Node* Browser::merge(Node* left, Node* right, bool(*pred)(Node*, Node*)) {
	Node* resultBegin = nullptr;
	Node* resultEnd = nullptr;

	while (left && right) {
		if (pred(left, right)) {
			pushBack(resultBegin, resultEnd, left);
			left = left->next;
		}
		else {
			pushBack(resultBegin, resultEnd, right);
			right = right->next;
		}
	}

	if (left) {
		resultEnd->next = left;
		left->prev = resultEnd;
	}
	else {
		resultEnd->next = right;
		right->prev = resultEnd;
	}

	return resultBegin;
}

Browser::Node* Browser::mergeSort(Node* list, bool(*pred)(Node*, Node*)) {
	if (!list || !list->next) {
		return list;
	}

	Node* middle = findMiddle(list);
	Node* left = list;
	Node* right = middle->next;
	middle->next = nullptr;

	left = mergeSort(left, pred);
	right = mergeSort(right, pred);
	return merge(left, right, pred);
}

Browser::Browser() {
	head = tail = current = new Node({ Constants::defaultMessage });
}

Browser::Browser(const Browser& other) {
	copyFrom(other);
}

Browser::Browser(Browser&& other) noexcept {
	moveFrom(std::move(other));
}

Browser& Browser::operator=(const Browser& other) {
	if (this != &other) {
		free();
		copyFrom(other);
	}

	return *this;
}

Browser& Browser::operator=(Browser&& other) noexcept {
	if (this != &other) {
		free();
		moveFrom(std::move(other));
	}

	return *this;
}

Browser::~Browser() {
	free();
}

void Browser::go(std::string url) {
	current->data.setURL(url);
}

void Browser::back() {
	if (current != head) {
		current = current->prev;
	}
}

void Browser::forward() {
	if (current != tail) {
		current = current->next;
	}
}

void Browser::insert(std::string url) {
	Node* newNode = new Node({ url });

	if (current->next) {
		current->next->prev = newNode;
	}
	else {
		tail = newNode;
	}

	newNode->next = current->next;
	newNode->prev = current;

	current->next = newNode;
	current = newNode;
}

void Browser::remove() {
	if (head == tail) {
		current->data.setURL(Constants::defaultMessage);
		return;
	}

	Node* toRemove = current;

	if (current == tail) {
		current->prev->next = nullptr;
		current = current->prev;
		tail = current;
	}
	else if (current == head) {
		current->next->prev = nullptr;
		current = current->next;
		head = current;
	}
	else {
		current->prev->next = current->next;
		current->next->prev = current->prev;
		current = current->next;
	}

	delete toRemove;
}

void Browser::print() const {
	Node* iter = head;

	while (iter) {
		if (iter == current) {
			std::cout << ">";
		}

		std::cout << iter->data.getURL() << " " << iter->data.getTimestamp() << std::endl;

		iter = iter->next;
	}
}

void Browser::sort(const SortCriteria& criteria) {
	if (criteria == SortCriteria::TIME) {
		head = mergeSort(head, &sortByTimeStampComparator);
	}
	else if (criteria == SortCriteria::URL) {
		head = mergeSort(head, &sortByURLComparator);
	}
}

Browser::Node::Node(const Tab& data) : data(data) { }