#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

class KthLargest {
public:
    std::priority_queue<int, std::vector<int>, std::greater<int>> pq;
    int k;

    KthLargest(int k, std::vector<int>& nums) {
        this->k = k;

        for (auto a : nums) {
            pq.push(a);
            
            if (pq.size() > k) {
                pq.pop();
            }
        }
    }

    int add(int val) {
        pq.push(val);

        if (pq.size() > k) {
            pq.pop();
        }

        return pq.top();
    }
};

int main() {
    std::vector<int> arr = { 4, 5, 8, 2 };
    KthLargest a(3, arr);

    a.add(3);
    a.add(5);
    a.add(10);
}