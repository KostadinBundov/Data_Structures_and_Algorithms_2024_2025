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
		end = curr;
	}
}


void processNode(ListNode*& node, int& additiveNumber, ListNode*& resultBegin, ListNode*& resultEnd) {
	int newValue = node->val + additiveNumber;

	if (newValue > 9) {
		additiveNumber = newValue / 10;
		newValue %= 10;
	}
	else {
		additiveNumber = 0;
	}

	node->val = newValue;
	pushBack(resultBegin, resultEnd, node);
}

ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
	ListNode* resultBegin = nullptr;
	ListNode* resultEnd = nullptr;
	int additiveNumber = 0;

	while (l1 && l2) {
		l1->val += l2->val;
		processNode(l1, additiveNumber, resultBegin, resultEnd);

		l1 = l1->next;
		l2 = l2->next;
	}

	while (l1) {
		processNode(l1, additiveNumber, resultBegin, resultEnd);
		l1 = l1->next;
	}

	while (l2) {
		processNode(l2, additiveNumber, resultBegin, resultEnd);
		l2 = l2->next;
	}

	if (additiveNumber != 0) {
		resultEnd->next = new ListNode(additiveNumber);
		resultEnd = resultEnd->next;
	}

	return resultBegin;
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
	ListNode* f1 = createLinkedList({ 9,9,9,9,9,9,9 });
	ListNode* f2 = createLinkedList({ 9,9,9,9 });
	ListNode* head = addTwoNumbers(f1, f2);

	printLinkedList(head);
	free(f1);
	free(f2);
	free(head);
}