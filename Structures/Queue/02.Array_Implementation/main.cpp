#include <iostream>
#include "ArrayQueue.hpp"

int main() {
    ArrayQueue<int> queue;

    std::cout << "Pushing elements: 1, 2, 3, 4" << std::endl;
    queue.push(1);
    queue.push(2);
    queue.push(3);
    queue.push(4);

    std::cout << "Front element: " << queue.front() << std::endl;

    std::cout << "Popping an element..." << std::endl;
    queue.pop();
    std::cout << "Front element after pop: " << queue.front() << std::endl;

    std::cout << "Adding more elements to test resizing..." << std::endl;
    queue.push(5);
    queue.push(6);
    queue.push(7);
    queue.push(8);
    queue.push(9);

    std::cout << "Queue elements: ";
    while (!queue.isEmpty()) {
        std::cout << queue.front() << " ";
        queue.pop();
    }
    std::cout << std::endl;

    try {
        std::cout << "Trying to access front on empty queue..." << std::endl;
        std::cout << queue.front() << std::endl;
    }
    catch (const std::exception& e) {
        std::cout << "Exception caught: " << e.what() << std::endl;
    }

    return 0;
}