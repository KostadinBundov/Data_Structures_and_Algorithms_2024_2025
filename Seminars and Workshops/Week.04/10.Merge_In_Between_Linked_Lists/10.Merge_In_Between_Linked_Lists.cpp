#include <iostream>
#include <vector>

struct ListNode {
	int val;
	ListNode* next;
	ListNode() : val(0), next(nullptr) {}
	ListNode(int x) : val(x), next(nullptr) {}
	ListNode(int x, ListNode* next) : val(x), next(next) {}

};

ListNode* findNodeByIndex(ListNode* list, int index) {
	for (int i = 0; i < index; i++) {
		list = list->next;
	}

	return list;
}

void free(ListNode* list) {
	while (list) {
		ListNode* toDel = list;
		list = list->next;
		delete toDel;
	}
}

ListNode* mergeInBetween(ListNode* list1, int a, int b, ListNode* list2) {

	ListNode* leftTail = findNodeByIndex(list1, a - 1);
	ListNode* toDeleteHead = findNodeByIndex(list1, a);
	leftTail->next = list2;

	ListNode* toDeleteTail = findNodeByIndex(toDeleteHead, b - a);

	ListNode* rightHead = list2;

	while (rightHead->next) {
		rightHead = rightHead->next;
	}

	rightHead->next = toDeleteTail->next;
	toDeleteTail->next = nullptr;

	free(toDeleteHead);

	return list1;
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
	ListNode* l1 = createLinkedList({ 10,1,13,6,9,5 });
	ListNode* l2 = createLinkedList({ 1000000,1000001,1000002 });
	ListNode* head = mergeInBetween(l1, 3, 4, l2);
	printLinkedList(head);
	free(head);
}