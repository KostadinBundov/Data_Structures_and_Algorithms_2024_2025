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

ListNode* oddEvenList(ListNode* head) {
	ListNode* oddHead = nullptr;
	ListNode* oddTail = nullptr;
	ListNode* evenHead = nullptr;
	ListNode* evenTail = nullptr;
	ListNode* curr = head;

	int index = 1;

	while (curr) {
		if (index & 1) {
			pushBack(oddHead, oddTail, curr);
		}
		else {
			pushBack(evenHead, evenTail, curr);
		}

		curr = curr->next;
		index++;
	}

	if (oddHead) {
		oddTail->next = evenHead;
	}
	else {
		oddHead = evenHead;
	}

	if (evenTail) { 
		evenTail->next = nullptr;
	}

	return oddHead;
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
	ListNode* f1 = createLinkedList({ 2,1,3,5,6,4,7 });
	ListNode* head = oddEvenList(f1);
	printLinkedList(head);
	free(head);
}