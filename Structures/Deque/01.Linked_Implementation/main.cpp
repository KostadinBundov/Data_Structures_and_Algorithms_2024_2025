#include <iostream>
#include "LinkedDeque.hpp" 
#include <queue>

int main() {
    LinkedDeque<int> deque;

    std::cout << "Adding elements: push_front(1), push_back(2), push_front(0), push_back(3)" << std::endl;
    deque.push_front(1);
    deque.push_back(2);
    deque.push_front(0);
    deque.push_back(3);

    std::cout << "Front: " << deque.front() << " (Expected: 0)" << std::endl;
    std::cout << "Back: " << deque.back() << " (Expected: 3)" << std::endl;

    std::cout << "Removing elements: pop_front(), pop_back()" << std::endl;
    deque.pop_front();
    deque.pop_back(); 

    std::cout << "Front after pop: " << deque.front() << " (Expected: 1)" << std::endl;
    std::cout << "Back after pop: " << deque.back() << " (Expected: 2)" << std::endl;

    std::cout << "Clearing deque..." << std::endl;
    deque.pop_front();
    deque.pop_back();

    if (deque.isEmpty()) {
        std::cout << "Deque is empty (Expected: true)" << std::endl;
    }

    try {
        deque.pop_front();
    }
    catch (const std::runtime_error& e) {
        std::cout << "Exception caught: " << e.what() << " (Expected: The deque is empty!)" << std::endl;
    }

    std::cout << "Testing iterators: Adding 5, 6, 7, 8 to deque" << std::endl;
    deque.push_back(5);
    deque.push_back(6);
    deque.push_back(7);
    deque.push_back(8);

    std::cout << "Deque elements: ";
    for (auto it = deque.begin(); it != deque.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << "(Expected: 5 6 7 8)" << std::endl;

    std::deque<int> d;

    return 0;
}