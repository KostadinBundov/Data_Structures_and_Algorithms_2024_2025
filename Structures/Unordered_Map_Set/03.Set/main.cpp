#include "HashSet.hpp"
#include <iostream>

int main() {
    HashSet<int> mySet;

    mySet.add(10);
    mySet.add(20);
    mySet.add(30);
    mySet.add(40);
    mySet.add(50);

    std::cout << "Set size after insertions: " << mySet.getSize() << std::endl;

    auto it = mySet.find(20);
    if (it != mySet.cend()) {
        std::cout << "Found: " << *it << std::endl;
    }
    else {
        std::cout << "20 not found" << std::endl;
    }

    bool removed = mySet.remove(20);
    std::cout << "Remove 20: " << (removed ? "Success" : "Failed") << std::endl;

    it = mySet.find(20);
    std::cout << "Find 20 after removal: " << (it == mySet.cend() ? "Not found" : "Still in set") << std::endl;

    std::cout << "Elements in set: ";
    for (auto it = mySet.cbegin(); it != mySet.cend(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    mySet.clear();
    std::cout << "Set cleared. Is empty? " << (mySet.isEmpty() ? "Yes" : "No") << std::endl;

    return 0;
}