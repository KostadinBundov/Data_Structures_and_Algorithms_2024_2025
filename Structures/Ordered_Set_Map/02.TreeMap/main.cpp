#include <iostream>
#include "TreeMap.hpp"

int main() {
    TreeMap<int, std::string> myMap;

    myMap.add(10, "ten");
    myMap.add(20, "twenty");
    myMap.add(5, "five");
    myMap.add(15, "fifteen");

    std::cout << "In-order traversal of the TreeMap:\n";
    for (auto it = myMap.cbegin(); it != myMap.cend(); ++it)
        std::cout << (*it).first << " -> " << (*it).second << "\n";

    std::cout << "\nFind tests:\n";
    std::cout << "Does the TreeMap contain 10? " << (myMap.find(10) ? "Yes" : "No") << "\n";
    std::cout << "Does the TreeMap contain 25? " << (myMap.find(25) ? "Yes" : "No") << "\n";

    std::cout << "\nRemoving key 10...\n";
    if (myMap.remove(10))
        std::cout << "Key 10 removed.\n";
    else
        std::cout << "Key 10 not found.\n";


    std::cout << "After removal:\n";
    for (auto it = myMap.cbegin(); it != myMap.cend(); ++it) {
        std::cout << (*it).first << " -> " << (*it).second << "\n";
    }

    std::cout << "\nSize of the TreeMap: " << myMap.getSize() << "\n";
    std::cout << "Is the TreeMap empty? " << (myMap.isEmpty() ? "Yes" : "No") << "\n";

    std::cout << "\nInserting duplicate key 5...\n";
    if (!myMap.add(5, "duplicate"))
        std::cout << "Duplicate key 5 was not inserted.\n";


    std::cout << "\nFinal TreeMap state:\n";
    for (auto it = myMap.cbegin(); it != myMap.cend(); ++it)
        std::cout << (*it).first << " -> " << (*it).second << "\n";


    return 0;
}