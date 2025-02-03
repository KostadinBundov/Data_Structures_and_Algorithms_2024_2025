#pragma once

#include <iostream>

template<class T>
class LinkedStack {
private:
	struct Node {
		Node(const T& data) : data(data) { }
		T data;
		Node* next = nullptr;
	};

	size_t size = 0;
	Node* head = nullptr;
public:
	LinkedStack() = default;
	LinkedStack(const LinkedStack<T>& other);
	LinkedStack(LinkedStack<T>&& other);
	LinkedStack& operator=(const LinkedStack<T>& other);
	LinkedStack& operator=(LinkedStack<T>&& other);
	~LinkedStack();

	void pop();
	void push(const T& element);
	const T& top() const;

	bool isEmpty() const;
	size_t getSize() const;

private:
	void free();
	void copyFrom(const LinkedStack<T>& other);
	void moveFrom(LinkedStack<T>&& other);
};

template<class T>
void LinkedStack<T>::pop() {
	if (isEmpty()) {
		throw std::runtime_error("The stack is emoty!");
	}

	if (size == 1) {
		delete head;
		head = nullptr;
	}
	else {
		Node* toDel = head;
		head = head->next;
		delete toDel;
	}

	size--;
}

template<class T>
void LinkedStack<T>::push(const T& element) {
	Node* newNode = new Node(element);

	if (isEmpty()) {
		head = newNode;
	}
	else {
		newNode->next = head;
		head = newNode;
	}

	size++;
}

template<class T>
const T& LinkedStack<T>::top() const {
	if (isEmpty()) {
		throw std::runtime_error("The stack is emoty!");
	}

	return head->data;
}

template<class T>
bool LinkedStack<T>::isEmpty() const {
	return size == 0;
}

template<class T>
size_t LinkedStack<T>::getSize() const {
	return size;
}

template<class T>
void LinkedStack<T>::free() {
	Node* curr = head;

	while (curr) {
		Node* toDel = curr;
		curr = curr->next;
		delete toDel;
	}

	head = nullptr;
	size = 0;
}

template<class T>
void LinkedStack<T>::copyFrom(const LinkedStack<T>& other) {
	if (other.isEmpty()) {
		head = nullptr;
		return;
	}

	head = new Node(other.head->data);
	Node* iter = head;
	Node* otherIter = other.head->next;

	while (otherIter)
	{
		iter->next = new Node(otherIter->data);
		iter = iter->next;
		otherIter = otherIter->next;
	}

	size = other.size;
}

template<class T>
void LinkedStack<T>::moveFrom(LinkedStack<T>&& other) {
	head = other.head;
	size = other.size;

	other.head = nullptr;
	other.size = 0;
}

template<class T>
LinkedStack<T>::LinkedStack(const LinkedStack<T>& other) {
	copyFrom(other);
}

template<class T>
LinkedStack<T>::LinkedStack(LinkedStack<T>&& other) {
	moveFrom(std::move(other));
}

template<class T>
LinkedStack<T>& LinkedStack<T>::operator=(const LinkedStack<T>& other) {
	if (this != &other) {
		free();
		copyFrom(other);
	}

	return *this;
}

template<class T>
LinkedStack<T>& LinkedStack<T>::operator=(LinkedStack<T>&& other) {
	if (this != &other) {
		free();
		moveFrom(std::move(other));
	}

	return *this;
}

template<class T>
LinkedStack<T>::~LinkedStack() {
	free();
}
