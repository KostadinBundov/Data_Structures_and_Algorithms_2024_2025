#include <iostream>
#include "HashSet.hpp"

int main() {
    HashSet<int> hashSet;

    std::cout << "Adding elements: 5, 10, 15, 20, 25" << std::endl;
    hashSet.add(5);
    hashSet.add(10);
    hashSet.add(15);
    hashSet.add(20);
    hashSet.add(25);

    std::cout << "Set contents: ";
    for (auto it = hashSet.cbegin(); it != hashSet.cend(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    std::cout << "\nFinding 10: " << (hashSet.find(10) != hashSet.cend() ? "Found" : "Not Found") << std::endl;
    std::cout << "Finding 99: " << (hashSet.find(99) != hashSet.cend() ? "Found" : "Not Found") << std::endl;

    std::cout << "\nRemoving 10..." << std::endl;
    hashSet.remove(10);

    std::cout << "Finding 10 after removal: " << (hashSet.find(10) != hashSet.cend() ? "Found" : "Not Found") << std::endl;

    std::cout << "Set contents after removal: ";
    for (auto it = hashSet.cbegin(); it != hashSet.cend(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    hashSet.add(10);
    hashSet.add(100);

    std::cout << "Set contents after adding again: ";
    for (auto it = hashSet.cbegin(); it != hashSet.cend(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    return 0;
}