#include "SinglyLinkedList.hpp"
#include <forward_list>

bool testPushFront()
{
    SinglyLinkedList<int> list;
    list.push_front(10);
    list.push_front(20);
    return list.front() == 20 && list.back() == 10 && list.getSize() == 2;
}

bool testPushBack()
{
    SinglyLinkedList<int> list;
    list.push_back(10);
    list.push_back(20);
    return list.front() == 10 && list.back() == 20 && list.getSize() == 2;
}

bool testPopFront()
{
    SinglyLinkedList<int> list;
    list.push_back(10);
    list.push_back(20);
    list.pop_front();
    return list.front() == 20 && list.getSize() == 1;
}

bool testFrontBack()
{
    SinglyLinkedList<int> list;
    list.push_back(10);
    list.push_back(20);
    return list.front() == 10 && list.back() == 20;
}

bool testConstFrontBack()
{
    const SinglyLinkedList<int> list = []() {
        SinglyLinkedList<int> temp;
        temp.push_back(10);
        temp.push_back(20);
        return temp;
        }();
    return list.front() == 10 && list.back() == 20;
}

bool testConcat()
{
    SinglyLinkedList<int> list1, list2;
    list1.push_back(1);
    list1.push_back(2);
    list2.push_back(3);
    list2.push_back(4);
    SinglyLinkedList<int> concatenated = concat(list1, list2);
    return concatenated.front() == 1 && concatenated.back() == 4 && concatenated.getSize() == 4;
}

bool testIterator()
{
    SinglyLinkedList<int> list;
    list.push_back(10);
    list.push_back(20);
    list.push_back(30);

    int sum = 0;
    for (auto it = list.begin(); it != list.end(); ++it)
        sum += *it;

    return sum == 60;
}

bool testConstIterator()
{
    const SinglyLinkedList<int> list = []() {
        SinglyLinkedList<int> temp;
        temp.push_back(10);
        temp.push_back(20);
        temp.push_back(30);
        return temp;
        }();

    int sum = 0;
    for (auto it = list.cbegin(); it != list.cend(); ++it)
        sum += *it;

    return sum == 60;
}

bool testInsertAfter()
{
    SinglyLinkedList<int> list;
    list.push_back(10);
    list.push_back(20);
    auto it = list.begin();
    list.insertAfter(15, it);
    ++it;
    return *it == 15 && list.getSize() == 3;
}

bool testRemoveAfter()
{
    SinglyLinkedList<int> list;
    list.push_back(10);
    list.push_back(20);
    list.push_back(30);
    auto it = list.begin();
    list.removeAfter(it);
    return *it == 10 && *(++it) == 30 && list.getSize() == 2;
}

bool testPushFrontMultipleElements()
{
    SinglyLinkedList<int> list;
    list.push_front(10);
    list.push_front(20);
    list.push_front(30);
    return list.front() == 30 && list.back() == 10 && list.getSize() == 3;
}

bool testPushBackMultipleElements()
{
    SinglyLinkedList<int> list;
    list.push_back(10);
    list.push_back(20);
    list.push_back(30);
    return list.front() == 10 && list.back() == 30 && list.getSize() == 3;
}

bool testPopFrontUntilEmpty()
{
    SinglyLinkedList<int> list;
    list.push_back(10);
    list.push_back(20);
    list.push_back(30);
    list.pop_front();
    list.pop_front();
    list.pop_front();
    return list.getSize() == 0;
}

bool testMixedPushFrontAndBack()
{
    SinglyLinkedList<int> list;
    list.push_back(10);
    list.push_front(20);
    list.push_back(30);
    list.push_front(40);

    bool testPass = list.front() == 40 && list.back() == 30 && list.getSize() == 4;

    list.pop_front();
    list.pop_front();
    testPass = testPass && (list.front() == 10 && list.back() == 30);

    return testPass;
}


bool testRemoveAfterVariousPositions()
{
    SinglyLinkedList<int> list;
    list.push_back(10);
    list.push_back(20);
    list.push_back(30);
    list.push_back(40);

    // Remove after head
    auto it = list.begin();
    it = list.removeAfter(it);
    bool testPass = list.getSize() == 3 && list.front() == 10 && *(it) == 30 && *(it + 1) == 40;
    it = list.removeAfter(it);
    testPass &= list.back() == 30 && list.getSize() == 2 && it == list.end();

    return testPass;
}

bool testConcatLargeLists()
{
    SinglyLinkedList<int> list1, list2;
    for (int i = 1; i <= 100; ++i) list1.push_back(i);
    for (int i = 101; i <= 200; ++i) list2.push_back(i);

    SinglyLinkedList<int> concatenated = concat(list1, list2);

    bool testPass = concatenated.getSize() == 200 && concatenated.front() == 1 && concatenated.back() == 200;

    // Verify ordering of elements in concatenated list
    auto it = concatenated.begin();
    for (int i = 1; i <= 200; ++i, ++it) {
        testPass = testPass && (*it == i);
    }

    return testPass;
}

bool testIteratorOnEmptyList()
{
    SinglyLinkedList<int> list;
    bool testPass = true;
    for (auto it = list.begin(); it != list.end(); ++it) {
        testPass = false; // Should never enter this loop
    }
    return testPass && list.isEmpty();
}

bool testIteratorIncrementAndComparison()
{
    SinglyLinkedList<int> list;
    for (int i = 1; i <= 5; ++i) list.push_back(i);

    auto it = list.begin();
    it += 2; // Move to the third element
    bool testPass = *it == 3;

    // Test operator+
    auto it2 = it + 2; // Should point to the 5th element
    testPass = testPass && (*it2 == 5);

    return testPass;
}

bool testConstIteratorUsage()
{
    const SinglyLinkedList<int> list = []() {
        SinglyLinkedList<int> temp;
        for (int i = 1; i <= 5; ++i) temp.push_back(i);
        return temp;
        }();

    bool testPass = true;
    int expectedValue = 1;
    for (auto it = list.cbegin(); it != list.cend(); ++it) {
        testPass = testPass && (*it == expectedValue++);
    }

    return testPass && expectedValue == 6;
}

int main()
{
    std::cout << "Test Push Front: " << testPushFront() << std::endl;
    std::cout << "Test Push Back: " << testPushBack() << std::endl;
    std::cout << "Test Pop Front: " << testPopFront() << std::endl;
    std::cout << "Test Front and Back: " << testFrontBack() << std::endl;
    std::cout << "Test Const Front and Back: " << testConstFrontBack() << std::endl;
    std::cout << "Test Concat: " << testConcat() << std::endl;
    std::cout << "Test Iterator: " << testIterator() << std::endl;
    std::cout << "Test Const Iterator: " << testConstIterator() << std::endl;
    std::cout << "Test Insert After: " << testInsertAfter() << std::endl;
    std::cout << "Test Remove After: " << testRemoveAfter() << std::endl;
    std::cout << "Test Push Front Multiple Elements: " << testPushFrontMultipleElements() << std::endl;
    std::cout << "Test Push Back Multiple Elements: " << testPushBackMultipleElements() << std::endl;
    std::cout << "Test Pop Front Until Empty: " << testPopFrontUntilEmpty() << std::endl;
    std::cout << "Test Mixed Push Front and Back: " << testMixedPushFrontAndBack() << std::endl;
    std::cout << "Test Remove After Various Positions: " << testRemoveAfterVariousPositions() << std::endl;
    std::cout << "Test Concat Large Lists: " << testConcatLargeLists() << std::endl;
    std::cout << "Test Iterator on Empty List: " << testIteratorOnEmptyList() << std::endl;
    std::cout << "Test Iterator Increment and Comparison: " << testIteratorIncrementAndComparison() << std::endl;
    std::cout << "Test Iterator Increment and Comparison: " << testConstIteratorUsage() << std::endl;

    //SinglyLinkedList<int> temp;
    //temp.push_front(1);

    //auto it = temp.cbegin();

    //temp.insertAfter(2, it);
    //std::cout << temp.front() << std::endl;

    //std::cout << temp.back() << std::endl;

    //it++;

    //temp.removeAfter(it);
   
    std::forward_list<int> s;
    
    s.push_front(1);
    auto it2 = s.cbegin();
    s.emplace_after(it2, 2);
    std::cout << s.front() << std::endl;
    it2++;
    s.erase_after(it2);

    std::cout << s.front();
}