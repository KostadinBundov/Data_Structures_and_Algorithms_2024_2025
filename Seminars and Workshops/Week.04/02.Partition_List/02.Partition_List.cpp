#include <iostream>
#include <vector>

struct ListNode {
	int val;
	ListNode* next;
	ListNode() : val(0), next(nullptr) {}
	ListNode(int x) : val(x), next(nullptr) {}
	ListNode(int x, ListNode* next) : val(x), next(next) {}
};

ListNode* partition(ListNode* head, int x) {
    ListNode* leftHead = nullptr;
    ListNode* rightHead = nullptr;
    ListNode* currentLeft = nullptr;
    ListNode* currentRight = nullptr;

    while (head) {
        if (head->val < x) {
            if (!leftHead) {
                leftHead = head;
                currentLeft = leftHead;
            }
            else {
                currentLeft->next = head;
                currentLeft = currentLeft->next;
            }
        }
        else {
            if (!rightHead) {
                rightHead = head;
                currentRight = rightHead;
            }
            else {
                currentRight->next = head;
                currentRight = currentRight->next;
            }
        }

        head = head->next;
    }

    if (currentLeft) {
        currentLeft->next = rightHead;
    }
    if (currentRight) {
        currentRight->next = nullptr;
    }

    return leftHead ? leftHead : rightHead;
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
    std::vector<int> arr = { 1,4,3,2,5,2 };

    ListNode* head = createLinkedList(arr);
    head = partition(head, 3);
    printLinkedList(head);
    free(head);
}