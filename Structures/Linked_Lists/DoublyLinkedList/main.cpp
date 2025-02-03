#include <iostream>
#include "DoublyLinkedList.hpp"

bool testInitialization() {
    DoublyLinkedList<int> list;
    if (list.isEmpty() && list.getSize() == 0) {
        std::cout << "testInitialization passed\n";
        return true;
    }
    else {
        std::cout << "testInitialization failed\n";
        return false;
    }
}

bool testPushBackAndBack() {
    DoublyLinkedList<int> list;
    list.push_back(10);
    if (!list.isEmpty() && list.getSize() == 1 && list.back() == 10) {
        list.push_back(20);
        if (list.getSize() == 2 && list.back() == 20) {
            std::cout << "testPushBackAndBack passed\n";
            return true;
        }
    }
    std::cout << "testPushBackAndBack failed\n";
    return false;
}

bool testPushFrontAndFront() {
    DoublyLinkedList<int> list;
    list.push_front(10);
    if (!list.isEmpty() && list.getSize() == 1 && list.front() == 10) {
        list.push_front(20);
        if (list.getSize() == 2 && list.front() == 20) {
            std::cout << "testPushFrontAndFront passed\n";
            return true;
        }
    }
    std::cout << "testPushFrontAndFront failed\n";
    return false;
}

bool testPopBack() {
    DoublyLinkedList<int> list;
    list.push_back(10);
    list.push_back(20);
    list.pop_back();
    if (list.getSize() == 1 && list.back() == 10) {
        list.pop_back();
        if (list.isEmpty()) {
            std::cout << "testPopBack passed\n";
            return true;
        }
    }
    std::cout << "testPopBack failed\n";
    return false;
}

bool testPopFront() {
    DoublyLinkedList<int> list;
    list.push_front(10);
    list.push_front(20);
    list.pop_front();
    if (list.getSize() == 1 && list.front() == 10) {
        list.pop_front();
        if (list.isEmpty()) {
            std::cout << "testPopFront passed\n";
            return true;
        }
    }
    std::cout << "testPopFront failed\n";
    return false;
}

bool testInsertAndRemove() {
    DoublyLinkedList<int> list;
    list.push_back(10);
    list.push_back(30);
    auto it = list.begin();
    ++it;

    list.insert(it, 20);

    std::cout << list.getSize() << " " << *list.begin() << " " << *++list.begin() << " " << *++(++list.begin()) << std::endl;
    if (list.getSize() == 3 && *++list.begin() == 20) {
        list.remove(list.begin());
        if (list.getSize() == 2 && list.front() == 20) {
            std::cout << "testInsertAndRemove passed\n";
            return true;
        }
    }
    std::cout << "testInsertAndRemove failed\n";
    return false;
}

bool testIteratorTraversal() {
    DoublyLinkedList<int> list;
    list.push_back(10);
    list.push_back(20);
    list.push_back(30);
    auto it = list.begin();
    if (*it == 10 && *(++it) == 20 && *(++it) == 30) {
        std::cout << "testIteratorTraversal passed\n";
        return true;
    }
    std::cout << "testIteratorTraversal failed\n";
    return false;
}

bool testFrontOnEmptyList() {
    DoublyLinkedList<int> list;
    try {
        list.front();
        std::cout << "testFrontOnEmptyList failed\n";
        return false;
    }
    catch (...) {
        std::cout << "testFrontOnEmptyList passed\n";
        return true;
    }
}

bool testBackOnEmptyList() {
    DoublyLinkedList<int> list;
    try {
        list.back();
        std::cout << "testBackOnEmptyList failed\n";
        return false;
    }
    catch (...) {
        std::cout << "testBackOnEmptyList passed\n";
        return true;
    }
}

bool testPushBackMultipleElements() {
    DoublyLinkedList<int> list;
    for (int i = 1; i <= 10; ++i) {
        list.push_back(i);
    }
    bool passed = list.getSize() == 10 && list.back() == 10;
    std::cout << (passed ? "testPushBackMultipleElements passed\n" : "testPushBackMultipleElements failed\n");
    return passed;
}

bool testPushFrontMultipleElements() {
    DoublyLinkedList<int> list;
    for (int i = 1; i <= 10; ++i) {
        list.push_front(i);
    }
    bool passed = list.getSize() == 10 && list.front() == 10;
    std::cout << (passed ? "testPushFrontMultipleElements passed\n" : "testPushFrontMultipleElements failed\n");
    return passed;
}

bool testClearList() {
    DoublyLinkedList<int> list;
    for (int i = 0; i < 5; ++i) {
        list.push_back(i);
    }
    list.clear();
    bool passed = list.isEmpty() && list.getSize() == 0;
    std::cout << (passed ? "testClearList passed\n" : "testClearList failed\n");
    return passed;
}

bool testCopyConstructor() {
    DoublyLinkedList<int> list;
    list.push_back(10);
    list.push_back(20);
    DoublyLinkedList<int> copyList(list);
    bool passed = (copyList.getSize() == 2) && (copyList.front() == 10) && (copyList.back() == 20);
    std::cout << (passed ? "testCopyConstructor passed\n" : "testCopyConstructor failed\n");
    return passed;
}

bool testAssignmentOperator() {
    DoublyLinkedList<int> list1;
    list1.push_back(10);
    list1.push_back(20);
    DoublyLinkedList<int> list2;
    list2.push_back(30);
    list2 = list1;

    bool passed = (list2.getSize() == 2) && (list2.front() == 10) && (list2.back() == 20);
    std::cout << (passed ? "testAssignmentOperator passed\n" : "testAssignmentOperator failed\n");
    return passed;
}

bool testIteratorIncrement() {
    DoublyLinkedList<int> list;
    list.push_back(10);
    list.push_back(20);
    list.push_back(30);
    auto it = list.begin();
    if (*it == 10 && *(++it) == 20 && *(++it) == 30) {
        std::cout << "testIteratorIncrement passed\n";
        return true;
    }
    std::cout << "testIteratorIncrement failed\n";
    return false;
}

int main() {
    int passedTests = 0;
    passedTests += testInitialization();
    passedTests += testPushBackAndBack();
    passedTests += testPushFrontAndFront();
    passedTests += testPopBack();
    passedTests += testPopFront();
    passedTests += testInsertAndRemove();
    passedTests += testIteratorTraversal();
    passedTests += testFrontOnEmptyList();
    passedTests += testBackOnEmptyList();
    passedTests += testPushBackMultipleElements();
    passedTests += testPushFrontMultipleElements();
    passedTests += testClearList();
    passedTests += testCopyConstructor();
    passedTests += testAssignmentOperator();
    passedTests += testIteratorIncrement();

    std::cout << passedTests << " out of 15 tests passed\n";
    return 0;
}