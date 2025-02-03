#include <iostream>
#include "PriorityQueue.hpp"

int main() {
    PriorityQueue<int, std::less<int>> maxHeap;
    maxHeap.push(10);
    maxHeap.push(20);
    maxHeap.push(5);
    maxHeap.push(30);

    std::cout << "Max Heap: ";
    while (!maxHeap.isEmpty()) {
        std::cout << maxHeap.top() << " ";
        maxHeap.pop();
    }
    std::cout << std::endl;

    PriorityQueue<int, std::greater<int>> minHeap;
    minHeap.push(10);
    minHeap.push(20);
    minHeap.push(5);
    minHeap.push(30);

    std::cout << "Min Heap: ";
    while (!minHeap.isEmpty()) {
        std::cout << minHeap.top() << " ";
        minHeap.pop();
    }
    std::cout << std::endl;

    return 0;
}
