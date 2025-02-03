#include "HashSet.hpp"
#include <iostream>

int main() {
    HashSet<int> mySet;

    mySet.add(10);
    mySet.add(20);
    mySet.add(30);

    auto it = mySet.find(20);
    if (it != mySet.cend()) {
        std::cout << "Found: " << *it << std::endl;
    }
    else {
        std::cout << "Not found" << std::endl;
    }

    mySet.remove(20);

    it = mySet.find(20);
    if (it == mySet.cend()) {
        std::cout << "20 successfully removed" << std::endl;
    }
    else {
        std::cout << "20 is still in the set" << std::endl;
    }

    std::cout << "Elements in the set: ";
    for (auto it = mySet.cbegin(); it != mySet.cend(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    return 0;
}