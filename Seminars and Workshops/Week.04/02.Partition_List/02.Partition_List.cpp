#include <iostream>

struct ListNode {
	int val;
	ListNode* next;
	ListNode() : val(0), next(nullptr) {}
	ListNode(int x) : val(x), next(nullptr) {}
	ListNode(int x, ListNode* next) : val(x), next(next) {}
};

ListNode* swapNodes(ListNode* head, int k) {
    ListNode* first = head;
    ListNode* second = head;
    ListNode* current = head;

    for (int i = 1; i < k; i++) {
        first = first->next;
    }

    ListNode* kthFromBeginning = first;

    while (current->next) {
        current = current->next;
        if (k > 1) {
            k--;
        }
        else {
            second = second->next;
        }
    }

    int temp = kthFromBeginning->val;
    kthFromBeginning->val = second->val;
    second->val = temp;

    return head;
}

int main()
{

}