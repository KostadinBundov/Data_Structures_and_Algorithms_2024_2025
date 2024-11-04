#include <iostream>
#include <vector>

struct ListNode {
	int val;
	ListNode* next;
	ListNode() : val(0), next(nullptr) {}
	ListNode(int x) : val(x), next(nullptr) {}
	ListNode(int x, ListNode* next) : val(x), next(next) {}

};

ListNode* reverseBetween(ListNode* head, int left, int right) {
	if (!head->next || left == right) {
		return head;
	}

	ListNode* prev = nullptr;
	ListNode* curr = head;

	for (int i = 1; i < left; i++) {
		prev = curr;
		curr = curr->next;
	}

	ListNode* next = nullptr;
	ListNode* leftTail = prev;
	ListNode* reverseTail = curr;

	while (left <= right) {
		next = curr->next;
		curr->next = prev;
		prev = curr;
		curr = next;

		left++;
	}

	if (leftTail) {
		leftTail->next = prev;
	}
	else {
		head = prev;
	}

	reverseTail->next = curr;

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
	std::vector<int> arr = { 3, 5 };
	int left = 1;
	int right = 2;

	ListNode* head = createLinkedList(arr);
	head = reverseBetween(head, left, right);

	printLinkedList(head);
}