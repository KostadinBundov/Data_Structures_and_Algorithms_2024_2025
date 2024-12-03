#include <iostream>
#include <vector>
#include <queue>

struct ListNode {
   int val;
   ListNode* next;
   ListNode() : val(0), next(nullptr) {}
   ListNode(int x) : val(x), next(nullptr) {}
   ListNode(int x, ListNode* next) : val(x), next(next) {}
};

//ListNode* mergeKLists(std::vector<ListNode*>& lists) {
//	ListNode* head = nullptr;
//	ListNode* curr = nullptr;
//	bool isHeadSet = false;
//
//	while (true) {
//		int minIndex = -1;
//		int minElement = INT32_MAX;
//
//		for (int i = 0; i < lists.size(); i++) {
//			if (lists[i] != nullptr && lists[i]->val < minElement) {
//				minIndex = i;
//				minElement = lists[i]->val;
//			}
//		}
//
//		if (minIndex == -1) {
//			break;
//		}
//
//		if (isHeadSet) {
//			ListNode* temp = lists[minIndex];
//			lists[minIndex] = lists[minIndex]->next;
//			curr->next = temp;
//			curr = curr->next;
//		}
//		else {
//			head = curr = lists[minIndex];
//			lists[minIndex] = lists[minIndex]->next;
//			isHeadSet = true;
//		}
//	}
//
//	return head;
//}

ListNode* mergeKLists(std::vector<ListNode*>& lists) {
    auto comparator = [](ListNode* a, ListNode* b) { return a->val > b->val; };
    std::priority_queue<ListNode*, std::vector<ListNode*>, decltype(comparator)> pq(comparator);

    for (int i = 0; i < lists.size(); i++) {
        if (lists[i] != nullptr) {
            pq.push(lists[i]);
        }
    }


    ListNode* head = new ListNode();
    ListNode* curr = head;

    while (!pq.empty()) {
        ListNode* temp = pq.top();
        pq.pop();

        if (temp->next) {
            pq.push(temp->next);
        }

        curr->next = temp;
        curr = curr->next;
    }

    return head->next;
}

ListNode* toLinkedList(const std::vector<int>& nums) {
    ListNode* head = nullptr;
    ListNode* current = nullptr;

    for (int num : nums) {
        ListNode* newNode = new ListNode(num);
        if (!head) {
            head = newNode;
        }
        else {
            current->next = newNode;
        }
        current = newNode;
    }

    return head;
}

void printList(ListNode* head) {
    while (head) {
        std::cout << head->val << " -> ";
        head = head->next;
    }
    std::cout << "nullptr" << std::endl;
}

int main() {
    std::vector<std::vector<int>> lists = {
        {1, 4, 5},
        {1, 3, 4},
        {2, 6}
    };

    std::vector<ListNode*> linkedLists;
    for (const auto& lst : lists) {
        linkedLists.push_back(toLinkedList(lst));
    }

	ListNode* result = mergeKLists(linkedLists);
	printList(result);
}