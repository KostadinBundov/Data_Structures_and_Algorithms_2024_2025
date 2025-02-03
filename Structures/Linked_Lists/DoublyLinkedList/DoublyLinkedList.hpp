#pragma once

#include <iostream>

template<class T>
class DoublyLinkedList {
private:
	struct Node {
		Node(const T& data) : data(data) { }
		T data;
		Node* prev = nullptr;
		Node* next = nullptr;
	};

	Node* head = nullptr;
	Node* tail = nullptr;
	size_t size = 0;

public:
	DoublyLinkedList() = default;
	DoublyLinkedList(const DoublyLinkedList& other);
	DoublyLinkedList(DoublyLinkedList&& other);
	DoublyLinkedList& operator=(const DoublyLinkedList& other);
	DoublyLinkedList& operator=(DoublyLinkedList&& other);
	~DoublyLinkedList();

	void push_front(const T& element);
	void push_back(const T& element);

	void push_front(T&& element);
	void push_back(T&& element);

	void pop_front();
	void pop_back();

	void clear();

	bool isEmpty() const;
	size_t getSize() const;

	T& front();
	T& back();
	const T& front() const;
	const T& back() const;

	class DllIterator {
		friend class DoublyLinkedList;

	public:
		DllIterator(Node* element) : element(element) { }

		T& operator*() { return element->data; }
		T* operator->() { return &element->data; }

		DllIterator& operator++() {
			if (element) {
				element = element->next;
			}

			return *this;
		}

		DllIterator operator++(int) {
			DllIterator toReturn(*this);
			++(*this);
			return toReturn;
		}

		DllIterator& operator--() {
			if (element) {
				element = element->prev;
			}

			return *this;
		}

		DllIterator operator--(int) {
			DllIterator toReturn(*this);
			--(*this);
			return toReturn;
		}

		DllIterator& operator+=(size_t size) {
			while (size) {
				++(*this);
				size--;
			}

			return *this;
		}

		DllIterator& operator-=(size_t size) {
			while (size) {
				--(*this);
				size--;
			}

			return *this;
		}

		DllIterator operator+(size_t size) {
			DllIterator toReturn(*this);
			return toReturn += size;
		}

		DllIterator operator-(size_t size) {
			DllIterator toReturn(*this);
			return toReturn -= size;
		}

		bool operator==(const DllIterator& other) const { return element == other.element; }
		bool operator!=(const DllIterator& other) const { return element != other.element; }

	private:
		Node* element;
	};

	class ConstDllIterator {
		friend class DoublyLinkedList;

	public:
		ConstDllIterator(const DllIterator& it) : element(it.element) { }
		ConstDllIterator(Node* element) : element(element) { }

		const T& operator*() const { return element->data; }
		const T* operator->() const { return &element->data; }

		ConstDllIterator& operator++() {
			if (element) {
				element = element->next;
			}

			return *this;
		}

		ConstDllIterator operator++(int) {
			ConstDllIterator toReturn(*this);
			++(*this);
			return toReturn;
		}

		ConstDllIterator& operator--() {
			if (element) {
				element = element->prev;
			}

			return *this;
		}

		ConstDllIterator operator--(int) {
			ConstDllIterator toReturn(*this);
			--(*this);
			return toReturn;
		}

		ConstDllIterator& operator+=(size_t size) {
			while (size) {
				++(*this);
				size--;
			}

			return *this;
		}

		ConstDllIterator& operator-=(size_t size) {
			while (size) {
				--(*this);
				size--;
			}

			return *this;
		}

		ConstDllIterator operator+(size_t size) {
			ConstDllIterator toReturn(*this);
			return toReturn += size;
		}

		ConstDllIterator operator-(size_t size) {
			ConstDllIterator toReturn(*this);
			return toReturn -= size;
		}

		bool operator==(const ConstDllIterator& other) const { return element == other.element; }
		bool operator!=(const ConstDllIterator& other) const { return element != other.element; }
	private:
		Node* element;
	};

	DllIterator begin() { return DllIterator(head); };
	DllIterator end() { return DllIterator(nullptr); };
	ConstDllIterator cbegin() const { return ConstDllIterator(head); };
	ConstDllIterator cend() const { return ConstDllIterator(nullptr); };

	DllIterator insert(const ConstDllIterator& it, const T& element);
	DllIterator remove(const ConstDllIterator& it);

	template<class U>
	friend DoublyLinkedList<U> concat(DoublyLinkedList<U> lhs, DoublyLinkedList<U> rhs);

	void print() const;
private:
	void free();
	void copyFrom(const DoublyLinkedList& other);
	void moveFrom(DoublyLinkedList&& other);
};

template<class T>
void DoublyLinkedList<T>::push_front(const T& element) {
	Node* toAdd = new Node(element);

	if (isEmpty()) {
		head = tail = toAdd;
	}
	else {
		head->prev = toAdd;
		toAdd->next = head;
		head = toAdd;
	}

	size++;
}

template<class T>
void DoublyLinkedList<T>::push_back(const T& element) {
	Node* toAdd = new Node(element);
	if (isEmpty()) {
		head = tail = toAdd;
	}
	else {
		tail->next = toAdd;
		toAdd->prev = tail;
		tail = toAdd;
	}

	size++;
}

template<class T>
void DoublyLinkedList<T>::push_front(T&& element) {
	Node* toAdd = new Node(std::move(element));

	if (isEmpty()) {
		head = tail = toAdd;
	}
	else {
		head->prev = toAdd;
		toAdd->next = head;
		head = toAdd;
	}

	size++;
}

template<class T>
void DoublyLinkedList<T>::push_back(T&& element) {
	Node* toAdd = new Node(std::move(element));
	if (isEmpty()) {
		head = tail = toAdd;
	}
	else {
		tail->next = toAdd;
		toAdd->prev = tail;
		tail = toAdd;
	}

	size++;
}

template<class T>
void DoublyLinkedList<T>::pop_front() {
	if (isEmpty()) {
		throw std::logic_error("The list is empty!");
	}

	if (head == tail) {
		delete head;
		head = tail = nullptr;
	}
	else {
		Node* toDel = head;
		head = head->next;
		head->prev = nullptr;
		delete toDel;
	}

	size--;
}

template<class T>
void DoublyLinkedList<T>::pop_back() {
	if (isEmpty()) {
		throw std::logic_error("The list is empty!");
	}

	if (head == tail) {
		delete head;
		head = tail = nullptr;
	}
	else {
		Node* toDel = tail;
		tail = tail->prev;
		tail->next = nullptr;
		delete toDel;
	}

	size--;
}

template<class T>
void DoublyLinkedList<T>::clear() {
	free();
}

template<class T>
bool DoublyLinkedList<T>::isEmpty() const {
	return size == 0;
}

template<class T>
size_t DoublyLinkedList<T>::getSize() const {
	return size;
}

template<class T>
T& DoublyLinkedList<T>::front() {
	if (isEmpty()) {
		throw std::logic_error("The list is empty!");
	}

	return head->data;
}

template<class T>
T& DoublyLinkedList<T>::back() {
	if (isEmpty()) {
		throw std::logic_error("The list is empty!");
	}

	return tail->data;
}

template<class T>
const T& DoublyLinkedList<T>::front() const {
	if (isEmpty()) {
		throw std::logic_error("The list is empty!");
	}

	return head->data;
}

template<class T>
const T& DoublyLinkedList<T>::back() const {
	if (isEmpty()) {
		throw std::logic_error("The list is empty!");
	}

	return tail->data;
}

template<class T>
typename DoublyLinkedList<T>::DllIterator DoublyLinkedList<T>::insert(const ConstDllIterator& it, const T& element) {
	if (it == cbegin()) {
		push_front(element);
		return begin();
	}
	else if (it == cend()) {
		push_back(element);
		return DoublyLinkedList::DllIterator(tail);
	}
	else {
		Node* curr = it.element;
		Node* newNode = new Node(element);

		newNode->next = curr;
		curr->prev->next = newNode;
		newNode->prev = curr->prev;
		curr->prev = newNode;
		size++;

		return DllIterator(newNode);
	}
}

template<class T>
typename DoublyLinkedList<T>::DllIterator DoublyLinkedList<T>::remove(const ConstDllIterator& it) {
	Node* curr = it.element;

	if (!curr) {
		throw std::runtime_error("Trying to remove end iterator");
	}
	else if (curr == head) {
		pop_front();
		return begin();
	}
	else if (curr == tail) {
		pop_back();
		return end();
	}
	else {
		curr->prev->next = curr->next;
		curr->next->prev = curr->prev;

		Node* next = curr->next;

		delete curr;
		size--;

		return DllIterator(next);
	}
}

template<class T>
void DoublyLinkedList<T>::print() const {
	Node* it = head;

	while (it) {
		std::cout << it->data << " ";
		it = it->next;
	}

	std::cout << std::endl;
}

template<class T>
void DoublyLinkedList<T>::free() {
	Node* it = head;

	while (it) {
		Node* toDel = it;
		it = it->next;
		delete toDel;
	}

	head = tail = nullptr;
	size = 0;
}

template<class T>
void DoublyLinkedList<T>::copyFrom(const DoublyLinkedList& other) {
	Node* iter = other.head;

	while (iter) {
		push_back(iter->data);
		iter = iter->next;
	}
}

template<class T>
void DoublyLinkedList<T>::moveFrom(DoublyLinkedList&& other) {
	head = other.head;
	tail = other.tail;
	size = other.size;

	other.head = other.tail = nullptr;
	other.size = 0;
}

template<class T>
DoublyLinkedList<T>::DoublyLinkedList(const DoublyLinkedList& other) {
	copyFrom(other);
}

template<class T>
DoublyLinkedList<T>::DoublyLinkedList(DoublyLinkedList&& other) {
	moveFrom(std::move(other));
}

template<class T>
DoublyLinkedList<T>& DoublyLinkedList<T>::operator=(const DoublyLinkedList& other) {
	if (this != &other) {
		free();
		copyFrom(other);
	}

	return *this;
}

template<class T>
DoublyLinkedList<T>& DoublyLinkedList<T>::operator=(DoublyLinkedList&& other) {
	if (this != &other) {
		free();
		moveFrom(std::move(other));
	}

	return *this;
}

template<class T>
DoublyLinkedList<T>::~DoublyLinkedList() {
	free();
}

template<class T>
DoublyLinkedList<T> concat(DoublyLinkedList<T> lhs, DoublyLinkedList<T> rhs) {
	DoublyLinkedList<T> result;

	if (lhs.isEmpty()) {
		result.head = rhs.head;
		result.tail = rhs.tail;
	}
	else if (rhs.isEmpty()) {
		result.head = lhs.head;
		result.tail = lhs.tail;
	}
	else {
		result.head = lhs.head;
		lhs.tail->next = rhs.head;
		rhs.head->prev = lhs.tail;
		result.tail = rhs.tail;
	}

	result.size = lhs.size + rhs.size;

	lhs.head = lhs.tail = rhs.head = rhs.tail = nullptr;
	rhs.size = lhs.size = 0;

	return result;
}