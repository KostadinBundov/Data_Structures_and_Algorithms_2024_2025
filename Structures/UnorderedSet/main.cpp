#include <iostream>
#include <string>
#include "UnorderedSet.hpp"

int main() {
    UnorderedSet<int> uset;

    uset.insert(10);
    uset.insert(20);
    uset.insert(30);

    std::cout << "Elements after insertion: ";
    for (auto it = uset.cbegin(); it != uset.cend(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    if (uset.find(20) != uset.cend()) {
        std::cout << "Element 20 exists." << std::endl;
    }
    else {
        std::cout << "Element doesn't 20 exist." << std::endl;
    }

    uset.remove(20);

    std::cout << "Elements after removing 20: ";
    for (auto it = uset.cbegin(); it != uset.cend(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    std::cout << "The set is empty: " << (uset.empty() ? "Yes" : "No") << std::endl;

    uset.insert(40);
    uset.insert(50);
    uset.insert(60);

    std::cout << "Elements before erase_if: ";
    for (auto it = uset.cbegin(); it != uset.cend(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    uset.erase_if([](int x) { return x > 30; });

    std::cout << "Elements after erase_if (x > 30): ";
    for (auto it = uset.cbegin(); it != uset.cend(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    uset.clear();
    std::cout << "The set is cleared." << std::endl;
    std::cout << "Is set empty: " << (uset.empty() ? "Yes" : "No") << std::endl;

    return 0;
}