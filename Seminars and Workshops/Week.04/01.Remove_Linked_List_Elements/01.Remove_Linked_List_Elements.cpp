#include <iostream>

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

	if (head == nullptr) {
		return head;
	}

	ListNode* previous = head;
	ListNode* current = head->next;

	while (current) {
		if (current->val == val) {
			previous->next = current->next;
			current = previous->next;
		}
		else {
			previous = previous->next;
			current = current->next;
		}
	}
	
	return head;
}

int main()
{
	
}