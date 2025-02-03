#include <iostream>
#include "HashMap.hpp"

int main() {
    HashMap<int, std::string> myMap;

    std::cout << "Adding pairs (1, \"apple\"), (2, \"banana\"), (3, \"cherry\")\n";
    myMap.add(1, "apple");
    myMap.add(2, "banana");
    myMap.add(3, "cherry");

    std::cout << "Size of the map: " << myMap.getSize() << "\n";

    std::cout << "Searching for key 2: ";
    {
        auto searchIt = myMap.find(2);
        if (searchIt != myMap.cend()) {
            std::cout << "Found: " << searchIt->second << "\n";
        }
        else {
            std::cout << "Not found\n";
        }
    }

    std::cout << "Searching for key 4: ";
    {
        auto searchIt = myMap.find(4);
        if (searchIt != myMap.cend()) {
            std::cout << "Found: " << searchIt->second << "\n";
        }
        else {
            std::cout << "Not found\n";
        }
    }

    std::cout << "Removing key 2\n";
    myMap.remove(2);

    std::cout << "Searching for key 2 after deletion: ";
    {
        auto searchIt = myMap.find(2);
        if (searchIt != myMap.cend()) {
            std::cout << "Found: " << searchIt->second << "\n";
        }
        else {
            std::cout << "Not found\n";
        }
    }

    std::cout << "All elements in the map: \n";
    for (auto iter = myMap.cbegin(); iter != myMap.cend(); ++iter) {
        std::cout << "Key: " << iter->first << ", Value: " << iter->second << "\n";
    }

    return 0;
}
