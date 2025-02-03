#pragma once

#include <iostream>
#include <stack>

template<class Key, class Value, class Comparator = std::less<Key>>
class TreeMap {
private:
	struct Node {
		Node(const std::pair<Key, Value>& data) : data(data) { }
		std::pair<Key, Value> data;
		Node* left = nullptr;
		Node* right = nullptr;
	};

	Node* root = nullptr;
	size_t size = 0;
	Comparator compare;

	Node** findMinElement(Node** head) {
		Node** curr = head;

		while ((*curr)->left) {
			curr = &(*curr)->left;
		}

		return curr;
	}

	void free(Node* head) {
		if (!head) {
			return;
		}

		free(head->left);
		free(head->right);
		delete head;
	}

	Node* copyFrom(Node* head) {
		if (!head) {
			return nullptr;
		}

		Node* curr = new Node(head->data);
		curr->left = copyFrom(head->left);
		curr->right = copyFrom(head->right);

		return curr;
	}
	
	void moveFrom(TreeMap&& other) {
		root = other.root;
		size = other.size;
		compare = other.compare;

		other.root = nullptr;
		other.size = 0;
	}
		 
public:
	TreeMap() = default;
	TreeMap(const Comparator& comparator) : compare(comparator) { }
	TreeMap(const TreeMap& other) {
		root = copyFrom(other.root);
		size = other.size;
		compare = other.compare;
	}
	TreeMap(TreeMap&& other) {
		moveFrom(std::move(other));
	}
	TreeMap& operator=(const TreeMap& other) {
		if (this != &other) {
			free(root);
			root = copyFrom(other.root);
			size = other.size;
			compare = other.compare;
		}

		return *this;
	}
	TreeMap& operator=(TreeMap&& other) {
		if (this != &other) {
			free(root);
			moveFrom(std::move(other));
		}

		return *this;
	}
	~TreeMap() {
		free(root);
		root = nullptr;
		size = 0;
	}

	bool add(const Key& key, const Value& value) {
		Node** curr = &root;

		while (*curr) {
			if (compare((*curr)->data.first, key)) {
				curr = &(*curr)->right;
			}
			else if (compare(key, (*curr)->data.first)) {
				curr = &(*curr)->left;
			}
			else {
				return false;
			}
		}

		*curr = new Node(std::make_pair(key, value));
		size++;
		return true;
	}

	bool remove(const Key& key) {
		Node** curr = &root;

		while (*curr) {
			if (compare((*curr)->data.first, key)) {
				curr = &(*curr)->right;
			}
			else if (compare(key, (*curr)->data.first)) {
				curr = &(*curr)->left;
			}
			else {
				break;
			}
		}

		if (*curr == nullptr) {
			return false;
		}

		Node* toDel = *curr;

		if (!toDel->left && !toDel->right) {
			*curr = nullptr;
		}
		else if (!toDel->left) {
			*curr = (*curr)->right;
		}
		else if (!toDel->right) {
			*curr = (*curr)->left;
		}
		else {
			Node** leaf = findMinElement(&toDel->right);

			*curr = *leaf;
			*leaf = nullptr;
			(*curr)->left = toDel->left;
			(*curr)->right = toDel->right;
		}

		delete toDel;
		size--;
		return true;
	}

	bool find(const Key& key) const {
		Node* curr = root;

		while (curr) {
			if (compare(curr->data.first, key)) {
				curr = curr->right;
			}
			else if (compare(key, curr->data.first)) {
				curr = curr->left;
			}
			else {
				return true;
			}
		}

		return false;
	}

	size_t getSize() const { return size; }
	bool isEmpty() const { return size == 0; }

	class ConstIterator {
	private:
		std::stack<Node*> s;

		void fillStack(Node* head) {
			while (head) {
				s.push(head);
				head = head->left;
			}
		}

	public:
		ConstIterator(Node* head) {
			fillStack(head);
		}

		const std::pair<Key, Value>& operator*() const { return s.top()->data; }
		const std::pair<Key, Value>* operator->() const { return s.top()->data; }

		ConstIterator& operator++() {
			Node* curr = s.top();
			s.pop();
			fillStack(curr->right);
			return *this;
		}
		ConstIterator operator++(int) {
			ConstIterator copy(*this);
			++(*this);
			return copy;
		}

		bool operator==(const ConstIterator& other) { return s == other.s; }
		bool operator!=(const ConstIterator& other) { return s != other.s; }
	};

	ConstIterator cbegin() const { return ConstIterator(root); }
	ConstIterator cend() const { return ConstIterator(nullptr); }
};