#include <iostream>
#include <string>
#include "HashMap.hpp"

int main() {
    HashMap<int, std::string> hashMap;

    std::cout << "Adding elements..." << std::endl;
    hashMap.add(1, "Apple");
    hashMap.add(2, "Banana");
    hashMap.add(3, "Cherry");
    hashMap.add(4, "Date");

    std::cout << "Current HashMap contents: " << std::endl;
    for (auto it = hashMap.cbegin(); it != hashMap.cend(); ++it) {
        std::cout << it->first << ": " << it->second << std::endl;
    }

    std::cout << "\nSearching for key 3: ";
    auto it = hashMap.find(3);
    if (it != hashMap.cend()) {
        std::cout << "Found - " << it->first << ": " << it->second << std::endl;
    }
    else {
        std::cout << "Not found!" << std::endl;
    }

    std::cout << "\nRemoving key 2..." << std::endl;
    hashMap.remove(2);

    std::cout << "Checking if key 2 exists: ";
    it = hashMap.find(2);
    if (it != hashMap.cend()) {
        std::cout << "Found - " << it->first << ": " << it->second << std::endl;
    }
    else {
        std::cout << "Not found!" << std::endl;
    }

    std::cout << "\nTesting resize operation..." << std::endl;
    for (int i = 5; i <= 20; i++) {
        hashMap.add(i, "Value_" + std::to_string(i));
    }

    std::cout << "Final HashMap contents after resize: " << std::endl;
    for (auto it = hashMap.cbegin(); it != hashMap.cend(); ++it) {
        std::cout << it->first << ": " << it->second << std::endl;
    }

    std::cout << "\nTesting clear() function..." << std::endl;
    hashMap.clear();

    hashMap.add(1, "koko");

    auto iter = hashMap.find(1);
    std::cout << iter->second;

    std::cout << "Is HashMap empty? " << (hashMap.isEmpty() ? "Yes" : "No") << std::endl;

    return 0;
}
