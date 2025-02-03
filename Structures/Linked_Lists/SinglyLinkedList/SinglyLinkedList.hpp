#pragma once
#include <iostream>

template<class T> 
class SinglyLinkedList {
private:
	class Node {
	public:
		Node* next = nullptr;
		T data;

		Node(const T& data) {
			this->data = data;
		}
	};

	Node* head = nullptr;
	Node* tail = nullptr;
	size_t size = 0;
public:
	SinglyLinkedList() = default;
	SinglyLinkedList(const SinglyLinkedList<T>& other);
	SinglyLinkedList(SinglyLinkedList<T>&& other);
	SinglyLinkedList<T>& operator=(const SinglyLinkedList<T>& other);
	SinglyLinkedList<T>& operator=(SinglyLinkedList<T>&& other);
	~SinglyLinkedList();
	
	void push_back(const T& element);
	void push_front(const T& element);
	void pop_front();

	size_t getSize() const;
	bool isEmpty() const {
		return size == 0;
	}

	template <typename U>
	friend SinglyLinkedList<U> concat(SinglyLinkedList<U>& lhs, SinglyLinkedList<U>& rhs);

	const T& front() const;
	const T& back() const;
	T& front();
	T& back();

	class SllIterator {
		friend class SinglyLinkedList;

	public:
		SllIterator(Node* element) {
			this->element = element;
		}

		T& operator*() {
			return element->data;
		}

		T* operator->() {
			return &element->data;
		}

		SllIterator& operator++() {
			if (element != nullptr) {
				element = element->next;
			}

			return *this;
		}

		SllIterator operator++(int) {
			SllIterator toReturn(*this); // a copy of SllIterator with ccopy constructor
			++(*this);
			return toReturn;
		}

		SllIterator& operator+=(size_t size) {
			while (size != 0) {
				++(*this);
				size--;
			}

			return *this;
		}

		SllIterator operator+(size_t size) {
			SllIterator toReturn(*this);
			toReturn += size;
			return toReturn;
		}

		bool operator==(const SllIterator& rhs) const {
			return element == rhs.element;
		}

		bool operator!=(const SllIterator& rhs) const {
			return element != rhs.element;
		}
	private:
		Node* element = nullptr;
	};

	class ConstSllIterator {
		friend class SinglyLinkedList;

	public:
		ConstSllIterator(Node* element) {
			this->element = element;
		}

		ConstSllIterator(const SllIterator& nonConstIter) : element(nonConstIter.element) {}

		const T* operator->() const {
			return &element->data;
		}

		const T& operator*() const {
			return element->data;
		}

		ConstSllIterator& operator++() {
			if (element != nullptr) {
				element = element->next;
			}

			return *this;
		}

		ConstSllIterator& operator++(int) {
			ConstSllIterator toReturn(*this);
			++(*this);
			return toReturn;
		}

		ConstSllIterator& operator+=(size_t size) {
			while (size != 0) {
				++(*this);
				size--;
			}

			return *this;
		}

		ConstSllIterator operator+(size_t size) {
			ConstSllIterator toReturn(*this);
			toReturn += size;
			return toReturn;
		}

		bool operator==(const ConstSllIterator& rhs) const {
			return element == rhs.element;
		}

		bool operator!=(const ConstSllIterator& rhs) const {
			return element != rhs.element;
		}

	private:
		Node* element = nullptr;
	};

	ConstSllIterator begin() { return SllIterator(head); }
	SllIterator end() { return SllIterator(nullptr); }
	ConstSllIterator cbegin() const { return ConstSllIterator(head); }
	ConstSllIterator cend() const { return ConstSllIterator(nullptr); }

	SllIterator insertAfter(const T& element, const ConstSllIterator& it);
	SllIterator removeAfter(const ConstSllIterator& it);

private:
	void free();
	void copyFrom(const SinglyLinkedList<T>& other);
	void moveFrom(SinglyLinkedList<T>&& other);
};

template<class T>
SinglyLinkedList<T>::SinglyLinkedList(const SinglyLinkedList<T>& other) {
	copyFrom(other);
}

template<class T>
SinglyLinkedList<T>::SinglyLinkedList(SinglyLinkedList<T>&& other) {
	moveFrom(std::move(other));
}

template<class T>
SinglyLinkedList<T>& SinglyLinkedList<T>::operator=(const SinglyLinkedList<T>& other) {
	if (this != &other) {
		free();
		copyFrom(other);
	}

	return *this;
}

template<class T>
SinglyLinkedList<T>& SinglyLinkedList<T>::operator=(SinglyLinkedList<T>&& other) {
	if (this != &other) {
		free();
		mobveFrom(std::move(other));
	}

	return *this;
}

template<class T>
SinglyLinkedList<T>::~SinglyLinkedList() {
	free();
}

template<class T>
void SinglyLinkedList<T>::push_front(const T& element) {
	Node* newHead = new Node(element);

	if (head == nullptr) {
		head = tail = newHead;
	}
	else {
		newHead->next = head;
		head = newHead;
	}

	size++;
}

template<class T>
void SinglyLinkedList<T>::pop_front() {
	if (head == nullptr) {
		throw std::out_of_range("The list is empty!");
	}

	if (head == tail) {
		delete head;
		head = tail = nullptr;
	}
	else {
		Node* toRemove = head;
		head = head->next;
		delete toRemove;
	}

	size--;
}

template<class T>
void SinglyLinkedList<T>::push_back(const T& element) {
	Node* newTail = new Node(element);

	if (head == nullptr) {
		head = tail = newTail;
	}
	else {
		tail->next = newTail;
		tail = newTail;
	}

	size++;
}

template<class T>
size_t SinglyLinkedList<T>::getSize() const {
	return size;
}

template<class T>
const T& SinglyLinkedList<T>::front() const {
	if (!head) {
		throw std::logic_error("Empty list!");
	}

	return head->data;
}

template<class T>
const T& SinglyLinkedList<T>::back() const {
	if (!head) {
		throw std::logic_error("Empty list!");
	}

	return tail->data;
}

template<class T>
T& SinglyLinkedList<T>::front() {
	if (!head) {
		throw std::logic_error("Empty list!");
	}

	return head->data;
}

template<class T>
T& SinglyLinkedList<T>::back() {
	if (!head) {
		throw std::logic_error("Empty list!");
	}

	return tail->data;
}

template <typename T>
typename SinglyLinkedList<T>::SllIterator SinglyLinkedList<T>::insertAfter(const T& element, const SinglyLinkedList<T>::ConstSllIterator& it) {
	if (it == cend()) {
		return end();
	}

	if (it.element == tail) {
		push_back(element);
		return SllIterator(tail);
	}

	Node* curr = it.element;
	Node* toInsert = new Node(element);

	toInsert->next = curr->next;
	curr->next = toInsert;

	size++;

	return SinglyLinkedList<T>::SllIterator(toInsert);
}

template <typename T>
typename SinglyLinkedList<T>::SllIterator SinglyLinkedList<T>::removeAfter(const typename SinglyLinkedList<T>::ConstSllIterator& it) {
	if (it == cend() || size == 1) {
		return end();
	}

	Node* curr = it.element;
	Node* toDel = curr->next;

	curr->next = toDel->next;

	if (toDel == tail) {
		tail = curr;
	}

	delete toDel;

	size--;

	return SinglyLinkedList<T>::SllIterator(curr->next);
}

template<class T>
void SinglyLinkedList<T>::free() {
	while (head != nullptr) {
		Node* toDel = head;
		head = head->next;
		delete toDel;
	}

	head = tail = nullptr;
	size = 0;
}

template<class T>
void SinglyLinkedList<T>::copyFrom(const SinglyLinkedList<T>& other) {
	Node* curr = other.head;

	while (curr != nullptr) {
		push_back(curr->data);
		curr = curr->next;
	}
}

template<class T>
void SinglyLinkedList<T>::moveFrom(SinglyLinkedList<T>&& other) {
	head = other.head;
	tail = other.tail;
	size = other.size;

	other.head = other.tail = nullptr;
	other.size = 0;
}

template <typename T>
SinglyLinkedList<T> concat(SinglyLinkedList<T>&& lhs, SinglyLinkedList<T>&& rhs)
{
	SinglyLinkedList<T> result;

	if (!lhs.head)
	{
		result.head = rhs.head;
		result.tail = rhs.tail;
	}
	else if (!rhs.head)
	{
		result.head = lhs.head;
		result.tail = lhs.tail;
	}
	else
	{
		lhs.tail->next = rhs.head;
		result.head = lhs.head;
		result.tail = rhs.tail;
	}

	result.size = rhs.size + lhs.size;
	rhs.size = lhs.size = 0;
	rhs.head = rhs.tail = lhs.head = lhs.tail = nullptr;

	return result;
}