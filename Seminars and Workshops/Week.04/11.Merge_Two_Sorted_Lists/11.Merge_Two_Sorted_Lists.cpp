#include <iostream>
#include <vector>

struct ListNode {
	int val;
	ListNode* next;
	ListNode() : val(0), next(nullptr) {}
	ListNode(int x) : val(x), next(nullptr) {}
	ListNode(int x, ListNode* next) : val(x), next(next) {}

};

void pushBack(ListNode*& begin, ListNode*& end, ListNode* curr) {
	if (!begin) {
		begin = end = curr;
	}
	else {
		end->next = curr;
		end = end->next;
	}
}

ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
	ListNode* resultBegin = nullptr;
	ListNode* resultEnd = nullptr;

	while (list1 && list2) {
		if (list1->val < list2->val) {
			pushBack(resultBegin, resultEnd, list1);
			list1 = list1->next;
		}
		else {
			pushBack(resultBegin, resultEnd, list2);
			list2 = list2->next;
		}
	}

	

	if (list1) {
		pushBack(resultBegin, resultEnd, list1);
	}
	
	if (list2) {
		pushBack(resultBegin, resultEnd, list2);
	}

	return resultBegin;
}

void free(ListNode* list) {
	while (list) {
		ListNode* toDel = list;
		list = list->next;
		delete toDel;
	}
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
	ListNode* l1 = createLinkedList({ });
	ListNode* l2 = createLinkedList({ 0 });
	ListNode* head = mergeTwoLists(l1, l2);
	printLinkedList(head);
	free(head);
}