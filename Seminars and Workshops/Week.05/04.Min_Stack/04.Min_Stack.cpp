#include <iostream>

class MinStack {
private:
	struct Node {
		Node(int data) : data(data) { }
		int data;
		Node* next = nullptr;
		Node* prev = nullptr;
		int min;
	};

	Node* head = nullptr;
	Node* tail = nullptr;
	size_t size = 0;


public:
	MinStack() {

	}

	void push(int val) {
		if (!head) {
			head = tail = new Node(val);
			head->min = val;
		}
		else {
			tail->next = new Node(val);
			tail->next->prev = tail;
			tail = tail->next;
			tail->min = val < tail->prev->min ? val : tail->prev->min;
		}

		size++;
	}

	void pop() {
		Node* toDel = tail;

		if (!head->next) {
			delete head;
			head = tail = nullptr;
		}
		else {
			Node* prev = tail->prev;
			delete tail;
			tail = prev;
			tail->next = nullptr;
		}
	}

	int top() {
		if (head) {
			return tail->data;
		}
	}

	int getMin() {
		if (head) {
			return tail->min;
		}
	}
};

int main() {
	MinStack minStack;
	minStack.push(-2);
	minStack.push(0);
	minStack.push(-3);
	std:: cout << minStack.getMin() << std::endl; // return -3
	minStack.pop();
	std::cout << minStack.top() << std::endl;    // return 0
	std::cout << minStack.getMin() << std::endl; // return -2
}