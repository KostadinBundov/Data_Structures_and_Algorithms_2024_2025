#include <iostream>
#include <vector>

struct ListNode {
	int val;
	ListNode* next;
	ListNode() : val(0), next(nullptr) {}
	ListNode(int x) : val(x), next(nullptr) {}
	ListNode(int x, ListNode* next) : val(x), next(next) {}

};

ListNode* mergeNodes(ListNode* head) {
	if (!head) {
		return nullptr;
	}

	if (!head->next) {
		return head;
	}

	ListNode* curr = head;
	ListNode* it = curr->next;

	while (it) {
		if (!it->next) {
			break;
		}

		if (it->val != 0) {
			curr->val += it->val;
		}
		else {
			curr->next = it;
			curr = curr->next;
		}

		it = it->next;
	}

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
	std::vector<int> arr = { 0,1,0,3,0,2,2,0 };

	ListNode* head = createLinkedList(arr);
	head = mergeNodes(head);

	printLinkedList(head);
}