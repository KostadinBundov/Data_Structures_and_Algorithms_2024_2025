#include "Vector.h"
#include <iostream>

int main() {
    Vector<> bitVector;

    bitVector.push_back(true);
    bitVector.push_back(false);
    bitVector.push_back(true);
    bitVector.push_back(false);

    std::cout << "Elements after adding: ";
    for (auto it = bitVector.begin(); it != bitVector.end(); it++) {
        std::cout << (*it ? "1" : "0") << " ";
    }
    std::cout << std::endl;

    bitVector.pop_back();
    std::cout << "Elements after pop_back: ";
    for (auto it = bitVector.begin(); it != bitVector.end(); ++it) {
        std::cout << (*it ? "1" : "0") << " ";
    }
    std::cout << std::endl;

    bitVector.insert(bitVector.cbegin(), true);
    std::cout << "Elements after insert at the beginning: ";
    for (auto it = bitVector.begin(); it != bitVector.end(); ++it) {
        std::cout << (*it ? "1" : "0") << " ";
    }
    std::cout << std::endl;

    bitVector.pop_front();
    std::cout << "Elements after pop_front: ";
    for (auto it = bitVector.begin(); it != bitVector.end(); it++) {
        std::cout << (*it ? "1" : "0") << " ";
    }
    std::cout << std::endl;

    bitVector[1] = true;
    std::cout << "Elements after changing index 1 to true: ";
    for (auto it = bitVector.begin(); it != bitVector.end(); it++) {
        std::cout << (*it ? "1" : "0") << " ";
    }
    std::cout << std::endl;

    std::cout << "Elements in reverse order: ";
    for (auto it = bitVector.rbegin(); it != bitVector.rend(); ++it) {
        std::cout << (*it ? "1" : "0") << " ";
    }
    std::cout << std::endl;

    return 0;
}