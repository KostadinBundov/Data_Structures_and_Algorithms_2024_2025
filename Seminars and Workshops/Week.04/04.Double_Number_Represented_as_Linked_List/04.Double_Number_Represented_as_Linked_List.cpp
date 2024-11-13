#include <iostream>
#include <vector>

struct ListNode {
	int val;
	ListNode* next;
	ListNode() : val(0), next(nullptr) {}
	ListNode(int x) : val(x), next(nullptr) {}
	ListNode(int x, ListNode* next) : val(x), next(next) {}

};

ListNode* reverse(ListNode* head) {
	ListNode* prev = nullptr;
	ListNode* curr = head;
	ListNode* next = nullptr;

	while (curr) {
		next = curr->next;
		curr->next = prev;
		prev = curr;
		curr = next;
	}

	return prev;
}

ListNode* doubleIt(ListNode* head) {
	head = reverse(head);

	ListNode* curr = head;
	ListNode* prev = nullptr;

	int additional = 0;

	while (curr) {
		curr->val = curr->val * 2 + additional;

		if (curr->val > 9) {
			additional = curr->val / 10;
			curr->val %= 10;
		}
		else {
			additional = 0;
		}

		prev = curr;
		curr = curr->next;
	}

	if (additional > 0) {
		prev->next = new ListNode(additional);
	}

	return reverse(head);
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

void free(ListNode* list) {
	while (list) {
		ListNode* toDel = list;
		list = list->next;
		delete toDel;
	}
}

int main() {
	std::vector<int> arr = { 9, 9, 9 };

	ListNode* head = createLinkedList(arr);
	head = doubleIt(head);
	printLinkedList(head);
	free(head);
}