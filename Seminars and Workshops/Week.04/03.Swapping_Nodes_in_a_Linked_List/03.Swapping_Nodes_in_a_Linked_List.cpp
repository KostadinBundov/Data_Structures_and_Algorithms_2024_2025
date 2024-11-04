#include <iostream>
#include <vector>

struct ListNode {
	int val;
	ListNode* next;
	ListNode() : val(0), next(nullptr) {}
	ListNode(int x) : val(x), next(nullptr) {}
	ListNode(int x, ListNode* next) : val(x), next(next) {}

};

ListNode* swapNodes(ListNode* head, int k) {
	ListNode* firstNode = head;

	for (int i = 1; i < k; i++) {
		firstNode = firstNode->next;
	}

	ListNode* secondNode = head;
	ListNode* buffer = head;

	while (buffer->next) {
		buffer = buffer->next;

		if (k > 1) {
			k--;
		}
		else {
			secondNode = secondNode->next;
		}
	}

	int temp = firstNode->val;
	firstNode->val = secondNode->val;
	secondNode->val = temp;

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
	std::vector<int> arr = { 7,9,6,6,7,8,3,0,9,5 };

	ListNode* head = createLinkedList(arr);
	head = swapNodes(head, 5);
	printLinkedList(head);
}