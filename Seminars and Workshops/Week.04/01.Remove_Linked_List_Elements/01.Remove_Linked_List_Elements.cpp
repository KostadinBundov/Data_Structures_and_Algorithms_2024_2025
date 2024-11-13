#include <iostream>
#include <vector>

struct ListNode {
	int val;
	ListNode* next;
	ListNode() : val(0), next(nullptr) {}
	ListNode(int x) : val(x), next(nullptr) {}
	ListNode(int x, ListNode* next) : val(x), next(next) {}
	
};

ListNode* removeElements(ListNode* head, int val) {
	while (head && head->val == val) {
		head = head->next;
	}

	if (!head) {
		return nullptr;
	}

	ListNode* newHead = head;
	ListNode* current = head->next;
	ListNode* prev = head;
	
	while (current) {
		if (current->val == val) {
			current = current->next;
			prev->next = current;
		}
		else {
			prev = current;
			current = current->next;
		}
	}

	return newHead;
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
	std::vector<int> arr = {  };
	int val = 6;

	ListNode* head = createLinkedList(arr);
	head = removeElements(head, val);

	printLinkedList(head);
	free(head);
}