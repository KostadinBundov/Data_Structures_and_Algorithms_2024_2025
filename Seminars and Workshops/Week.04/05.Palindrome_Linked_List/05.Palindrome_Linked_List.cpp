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

bool isPalindrome(ListNode* head) {
	ListNode* slow = head;
	ListNode* fast = head;

	while (fast && fast->next) {
		slow = slow->next;
		fast = fast->next->next;
	}

	ListNode* secondHalfHead = reverse(slow);

	ListNode* firstHalfHead = head;

	while (secondHalfHead) {
		if (firstHalfHead->val != secondHalfHead->val) {
			return false;
		}

		firstHalfHead = firstHalfHead->next;
		secondHalfHead = secondHalfHead->next;
	}

	return true;
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

void free(ListNode* list) {
	while (list) {
		ListNode* toDel = list;
		list = list->next;
		delete toDel;
	}
}

int main() {
	std::vector<int> arr = { 1,1,2,1, 1 };

	ListNode* head = createLinkedList(arr);
	std::cout << isPalindrome(head);
	free(head);
}