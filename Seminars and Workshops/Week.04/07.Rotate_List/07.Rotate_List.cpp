#include <iostream>
#include <vector>

struct ListNode {
	int val;
	ListNode* next;
	ListNode() : val(0), next(nullptr) {}
	ListNode(int x) : val(x), next(nullptr) {}
	ListNode(int x, ListNode* next) : val(x), next(next) {}

};

ListNode* rotateRight(ListNode* head, int k) {
	if (!head || k == 0) {
		return head;
	}

	ListNode* curr = head;
	size_t size = 1;

	while (curr->next) {
		curr = curr->next;
		size++;
	}

	curr->next = head;
	int shiftsCount = size - (k % size);

	for (int i = 0; i < shiftsCount; i++) {
		curr = curr->next;
	}

	head = curr->next;
	curr->next = nullptr;

	return head;
}

ListNode* createLinkedList(const std::vector<int>& values) {
	if (values.empty()) {
		return nullptr;
	}

	ListNode* head = new ListNode(values[0]);
	ListNode* current = head;

	for (size_t i = 1; i < values.size(); ++i) {
		current->next = new ListNode(values[i]);
		current = current->next;
	}

	return head;
}

void printLinkedList(ListNode* head) {
	ListNode* current = head;

	while (current) {
		std::cout << current->val;

		if (current->next) {
			std::cout << " -> ";
		}

		current = current->next;
	}

	std::cout << std::endl;
}

int main() {
	std::vector<int> arr = { 1, 2, 3, 4, 5 };
	int k = 1;

	ListNode* head = createLinkedList(arr);
	head = rotateRight(head, k);

	printLinkedList(head);
}