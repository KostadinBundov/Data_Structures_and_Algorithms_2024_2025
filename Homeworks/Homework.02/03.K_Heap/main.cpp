#include <iostream>
#include <vector>
#include <stdexcept>
#include "PriorityQueueKaryHeap.hpp"

int main() {
    try {
        PriorityQueueKaryHeap<int> pq(3);

        std::cout << "Is the heap empty? " << std::boolalpha << pq.isEmpty() << std::endl;
        std::cout << "Heap size: " << pq.size() << std::endl;

        std::cout << "\nInserting elements: 10, 20, 15, 30, 25" << std::endl;
        pq.push(10);
        pq.push(20);
        pq.push(15);
        pq.push(30);
        pq.push(25);

        std::cout << "Heap size after insertions: " << pq.size() << std::endl;
        std::cout << "Top element (peek): " << pq.peek() << std::endl;

        std::cout << "\nRemoving elements from the heap:" << std::endl;
        while (!pq.isEmpty()) {
            std::cout << "Top element: " << pq.peek() << " (removing)" << std::endl;
            pq.pop();
        }

        std::cout << "\nTrying to peek or pop from an empty heap:" << std::endl;
        try {
            std::cout << "Peek: " << pq.peek() << std::endl;
        }
        catch (const std::out_of_range& e) {
            std::cout << "Caught exception: " << e.what() << std::endl;
        }

        try {
            pq.pop();
        }
        catch (const std::out_of_range& e) {
            std::cout << "Caught exception: " << e.what() << std::endl;
        }

        std::vector<int> initialData = { 5, 30, 20, 80, 10, 50 };
        std::cout << "\nCreating a heap with initial data: {40, 30, 20, 10, 50}" << std::endl;
        PriorityQueueKaryHeap<int> pq2(initialData, 3);

        std::cout << "Heap size: " << pq2.size() << std::endl;
        std::cout << "Top element (peek): " << pq2.peek() << std::endl;

        std::cout << "\nRemoving elements from the heap initialized with data:" << std::endl;
        while (!pq2.isEmpty()) {
            std::cout << "Top element: " << pq2.peek() << " (removing)" << std::endl;
            pq2.pop();
        }

    }
    catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    return 0;
}
