#include <iostream>
#include <string>
#include "HashMap.hpp"

int main() {
    HashMap<int, std::string> hashMap;

    hashMap.add(1, "one");
    hashMap.add(2, "two");
    hashMap.add(3, "three");
    hashMap.add(4, "four");
    hashMap.add(5, "five");

    std::cout << "Added 5 elements.\n";

    int searchKey = 3;
    auto it = hashMap.find(searchKey);
    if (it != hashMap.cend()) {
        std::cout << "Found: " << it->first << " -> " << it->second << "\n";
    }
    else {
        std::cout << "Key " << searchKey << " not found!\n";
    }

    std::cout << "Removing key 3...\n";
    hashMap.remove(3);

    it = hashMap.find(3);
    if (it != hashMap.cend()) {
        std::cout << "Error: Key 3 still exists after removal!\n";
    }
    else {
        std::cout << "Key 3 successfully removed.\n";
    }

    std::cout << "Current size: " << hashMap.getSize() << "\n";

    return 0;
}
