﻿#include <iostream>
#include <vector>

struct ListNode {
	int val;
	ListNode* next;
	ListNode() : val(0), next(nullptr) {}
	ListNode(int x) : val(x), next(nullptr) {}
	ListNode(int x, ListNode* next) : val(x), next(next) {}

};

ListNode* swapNodes(ListNode* head, int k) {
	int index = k - 1;
	ListNode** firstPtr = &head;

	for (int i = 0; i < index; i++) {
		firstPtr = &((*firstPtr)->next);
	}

	ListNode** secondPtr = &head;
	ListNode* buffer = head;

	while (buffer->next) {
		buffer = buffer->next;

		if (k > 1) {
			k--;
		}
		else {
			secondPtr = &((*secondPtr)->next);
		}
	}

	ListNode* temp = *firstPtr;
	*firstPtr = *secondPtr;
	*secondPtr = temp;

	temp = (*firstPtr)->next;
	(*firstPtr)->next = (*secondPtr)->next;
	(*secondPtr)->next = temp;

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

void free(ListNode* list) {
	while (list) {
		ListNode* toDel = list;
		list = list->next;
		delete toDel;
	}
}

int main() {
	std::vector<int> arr = { 1, 2, 3, 4, 5, 6  };

	ListNode* head = createLinkedList(arr);
	head = swapNodes(head, 1);
	printLinkedList(head);
	free(head);
}