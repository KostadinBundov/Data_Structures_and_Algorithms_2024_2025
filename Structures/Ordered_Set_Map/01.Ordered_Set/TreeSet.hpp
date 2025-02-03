#pragma once

#include <iostream>
#include <stack>

template<class T, class Comparator = std::less<T>>
class TreeSet {
private:
	struct Node {
		Node(const T& data) : data(data) { }
		T data;
		Node* left = nullptr;
		Node* right = nullptr;
	};

	size_t size = 0;
	Node* root = nullptr;
	Comparator compare;

public:
	TreeSet() = default;
	TreeSet(const Comparator& comparator) : compare(comparator) { }
	TreeSet(const TreeSet<T, Comparator>& other);
	TreeSet(TreeSet<T, Comparator>&& other);
	TreeSet<T, Comparator>& operator=(const TreeSet<T, Comparator>& other);
	TreeSet<T, Comparator>& operator=(TreeSet<T, Comparator>&& other);
	~TreeSet();

	size_t getSize() const { return size; }
	bool isEmpty() const { return size == 0; }

	bool add(const T& element);
	bool remove(const T& element);
	bool find(const T& element) const;

	class ConstIterator {
	private:
		std::stack<Node*> stack;

		void pushLeft(Node* head) {
			while (head) {
				stack.push(head);
				head = head->left;
			}
		}

	public:
		ConstIterator(Node* head = nullptr) {
			pushLeft(head);
		}

		const T& operator*() const { return stack.top()->data; }
		const T* operator->() const { return &stack.top()->data; }

		ConstIterator& operator++() {
			Node* curr = stack.top();
			stack.pop();
			pushLeft(curr->right);

			return *this;
		}
		ConstIterator operator++(int) {
			ConstIterator copy(*this);
			++(*this);
			return copy;
		}

		bool operator==(const ConstIterator& other) const { return stack == other.stack; }
		bool operator!=(const ConstIterator& other) const { return stack != other.stack; }
	};

	ConstIterator cbegin() const { return ConstIterator(root); }
	ConstIterator cend() const { return ConstIterator(nullptr); }

private:
	void free(Node* head);
	Node* copyFrom(Node* other);
	void moveFrom(TreeSet<T, Comparator>&& other);

	Node** findMaxElement(Node** root) {
		Node** curr = root;

		while ((*curr)->right) {
			curr = &(*curr)->right;
		}

		return curr;
	}
};

template<class T, class Comparator>
TreeSet<T, Comparator>::TreeSet(const TreeSet<T, Comparator>& other) {
	root = copyFrom(other.root);
	size = other.size;
	compare = other.compare;
}

template<class T, class Comparator>
TreeSet<T, Comparator>::TreeSet(TreeSet<T, Comparator>&& other) {
	moveFrom(std::move(other));
}

template<class T, class Comparator>
TreeSet<T, Comparator>& TreeSet<T, Comparator>::operator=(const TreeSet<T, Comparator>& other) {
	if (this != &other) {
		free(root);
		root = copyFrom(other.root);
		size = other.size;
		compare = other.compare;
	}

	return *this;
}

template<class T, class Comparator>
TreeSet<T, Comparator>& TreeSet<T, Comparator>::operator=(TreeSet<T, Comparator>&& other) {
	if (this != &other) {
		free(root);
		moveFrom(std::move(other));
	}
}

template<class T, class Comparator>
TreeSet<T, Comparator>::~TreeSet() {
	free(root);
}

template<class T, class Comparator>
bool TreeSet<T, Comparator>::add(const T& element) {
	Node** curr = &root;

	while (*curr) {
		if (compare((*curr)->data, element)) {
			curr = &(*curr)->right;
		}
		else if (compare(element, (*curr)->data)) {
			curr = &(*curr)->left;
		}
		else {
			return false;
		}
	}

	*curr = new Node(element);
	size++;
	return true;
}

template<class T, class Comparator>
bool TreeSet<T, Comparator>::remove(const T& element) {
	Node** curr = &root;

	while (*curr) {
		if (compare((*curr)->data, element)) {
			curr = &(*curr)->right;
		}
		else if (compare(element, (*curr)->data)) {
			curr = &(*curr)->left;
		}
		else {
			break;
		}
	}

	if ((*curr) == nullptr) {
		return false;
	}
	Node* toDel = *curr;

	if (!(*curr)->left && !(*curr)->right) {
		*curr = nullptr;
	}
	else if (!(*curr)->left) {
		*curr = toDel->right;
	}
	else if (!(*curr)->right) {
		*curr = toDel->left;
	}
	else {
		Node** leafNode = findMaxElement(&toDel->left);

		*curr = *leafNode;
		*leafNode = (*leafNode)->left;

		(*curr)->left = toDel->left;
		(*curr)->right = toDel->right;
	}

	delete toDel;
	size--;
	return true;
}

template<class T, class Comparator>
bool TreeSet<T, Comparator>::find(const T& element) const {
	Node* curr = root;

	while (curr)
	{
		if (compare(curr->data, element)) {
			curr = curr->right;
		}
		else if (compare(element, curr->data)) {
			curr = curr->left;
		}
		else {
			return true;
		}
	}

	return false;
}

template<class T, class Comparator>
void TreeSet<T, Comparator>::free(Node* head) {
	if (!head) {
		return;
	}

	free(head->left);
	free(head->right);
	delete head;
}

template<class T, class Comparator>
typename TreeSet<T, Comparator>::Node* TreeSet<T, Comparator>::copyFrom(Node* other) {
	if (!other) {
		return nullptr;
	}

	Node* res = new Node(other->data);

	res->left = copyFrom(other->left);
	res->right = copyFrom(other->right);
	return res;
}

template<class T, class Comparator>
void TreeSet<T, Comparator>::moveFrom(TreeSet<T, Comparator>&& other) {
	root = other.root;
	size = other.size;

	other.root = nullptr;
	other.size = 0;
}