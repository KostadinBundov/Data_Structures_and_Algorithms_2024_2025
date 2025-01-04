#include <iostream>
#include <string>
#include "UnorderedSet.hpp" 

struct CustomHash {
    size_t operator()(const std::string& key) const {
        return key.length();
    }
};

void testEraseIf() {
    UnorderedSet<std::string, CustomHash> mySet;

    mySet.insert("apple");
    mySet.insert("banana");
    mySet.insert("cherry");
    mySet.insert("example");
    mySet.insert("test");

    std::cout << "Set elements before erase_if:" << std::endl;
    for (auto it = mySet.cbegin(); it != mySet.cend(); ++it) {
        std::cout << *it << std::endl;
    }

    std::cout << "\nRemoving elements with length > 5:" << std::endl;
    mySet.erase_if([](const std::string& str) {
        return str.length() > 5;
        });

    std::cout << "Set elements after erase_if:" << std::endl;
    for (auto it = mySet.cbegin(); it != mySet.cend(); ++it) {
        std::cout << *it << std::endl;
    }

    std::cout << "\nRemoving elements that contain the letter 'e':" << std::endl;
    mySet.erase_if([](const std::string& str) {
        return str.find('e') != std::string::npos;
        });

    std::cout << "Set elements after second erase_if:" << std::endl;
    for (auto it = mySet.cbegin(); it != mySet.cend(); ++it) {
        std::cout << *it << std::endl;
    }
}

int main() {
    testEraseIf();
    return 0;
}
