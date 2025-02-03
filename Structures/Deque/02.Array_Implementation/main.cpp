#include "ArrayDeque.hpp"
#include <iostream>
#include <deque>

bool testPushBack()
{
    ArrayDeque<int> dq;
    dq.push_back(10);
    dq.push_back(20);
    dq.push_back(30);

    return dq.getSize() == 3 && dq[0] == 10 && dq[1] == 20 && dq[2] == 30;
}

bool testPushFront()
{
    ArrayDeque<int> dq;
    dq.push_front(10);
    dq.push_front(20);
    dq.push_front(30);

    return dq.getSize() == 3 && dq[0] == 30 && dq[1] == 20 && dq[2] == 10;
}

bool testPopBack()
{
    ArrayDeque<int> dq;
    dq.push_back(10);
    dq.push_back(20);
    dq.push_back(30);
    dq.pop_back();

    return dq.getSize() == 2 && dq[0] == 10 && dq[1] == 20;
}

bool testPopFront()
{
    ArrayDeque<int> dq;
    dq.push_back(10);
    dq.push_back(20);
    dq.push_back(30);
    dq.pop_front();

    return dq.getSize() == 2 && dq[0] == 20 && dq[1] == 30;
}

bool testEmplaceBack()
{
    ArrayDeque<std::string> dq;
    dq.emplace_back(3, 'a');

    return dq.getSize() == 1 && dq[0] == "aaa";
}

bool testEmplaceFront()
{
    ArrayDeque<std::string> dq;
    dq.emplace_front(3, 'b');

    return dq.getSize() == 1 && dq[0] == "bbb";
}

bool testFrontBackAccess()
{
    ArrayDeque<int> dq;
    dq.push_back(10);
    dq.push_back(20);
    dq.push_front(5);

    return dq.front() == 5 && dq.back() == 20;
}

bool testIsEmpty()
{
    ArrayDeque<int> dq;
    return dq.isEmpty();
}

bool testResize()
{
    ArrayDeque<int> dq;
    for (int i = 0; i < 20; ++i)
    {
        dq.push_back(i);
    }

    bool success = true;
    for (int i = 0; i < 20; ++i)
    {
        success = success && dq[i] == i;
    }

    return success && dq.getSize() == 20;
}

bool testIteratorIncrement()
{
    ArrayDeque<int> dq;
    dq.push_back(1);
    dq.push_back(2);
    dq.push_back(3);

    auto it = dq.begin();
    if (*it != 1)
    {
        return false;
    }

    it++;
    if (*it != 2)
    {
        return false;
    }

    ++it;
    if (*it != 3)
    {
        return false;
    }

    return it == dq.end() - 1;
}

bool testIteratorDecrement()
{
    ArrayDeque<int> dq;
    dq.push_back(1);
    dq.push_back(2);
    dq.push_back(3);

    auto it = dq.end() - 1;
    if (*it != 3)
    {
        return false;
    }

    it--;
    if (*it != 2)
    {
        return false;
    }

    --it;
    if (*it != 1)
    {
        return false;
    }

    return it == dq.begin();
}

bool testIteratorEquality()
{
    ArrayDeque<int> dq;
    dq.push_back(10);
    dq.push_back(20);

    auto it1 = dq.begin();
    auto it2 = dq.begin();

    if (it1 != it2)
    {
        return false;
    }

    ++it2;

    if (it1 == it2)
    {
        return false;
    }

    return true;
}

bool testConstIterator()
{
    ArrayDeque<int> dq;
    dq.push_back(5);
    dq.push_back(15);
    dq.push_back(25);

    ArrayDeque<int>& constDq = dq;
    auto it = constDq.begin();

    if (*it != 5)
    {
        return false;
    }

    ++it;

    if (*it != 15)
    {
        return false;
    }

    ++it;

    if (*it != 25)
    {
        return false;
    }

    return it == constDq.end() - 1;
}

bool testIteratorDereference()
{
    ArrayDeque<int> dq;
    dq.push_back(100);
    dq.push_back(200);
    dq.push_back(300);

    auto it = dq.begin();

    if (*it != 100)
    {
        return false;
    }

    ++it;

    if (*it != 200)
    {
        return false;
    }

    it++;

    if (*it != 300)
    {
        return false;
    }

    return true;
}

bool testCopyConstructor()
{
    ArrayDeque<int> dq;
    dq.push_back(1);
    dq.push_back(2);
    dq.push_back(3);

    ArrayDeque<int> copy(dq);

    if (dq.getSize() != copy.getSize())
    {
        return false;
    }

    while (copy.getSize())
    {
        if (copy.front() != dq.front())
        {
            return false;
        }

        copy.pop_front();
        dq.pop_front();
    }

    return dq.getSize() == copy.getSize();
}

bool testMoveAndAssignment()
{
    constexpr size_t SIZE = 4;

    ArrayDeque<int> d;

    for (size_t i = 0; i < SIZE; i++)
    {
        d.push_back(i);
    }

    ArrayDeque<int> d1;
    d1 = d;

    for (size_t i = 0; i < d1.getSize(); i++)
    {
        if (d1[i] != d[i])
        {
            return false;
        }
    }

    ArrayDeque<int> moved(std::move(d1));

    if (moved.getSize() != SIZE || d1.getSize() != 0)
    {
        return false;
    }

    d1 = std::move(moved);
    moved = std::move(d1);

    if (moved.getSize() != SIZE || d1.getSize() != 0)
    {
        return false;
    }

    while (moved.getSize())
    {
        if (moved.front() != d.front() || moved.back() != d.back())
        {
            return false;
        }

        moved.pop_back();
        d.pop_back();

        if (moved.isEmpty() || d.isEmpty())
        {
            break;
        }

        moved.pop_front();
        d.pop_front();
    }

    return moved.isEmpty() && d.isEmpty();
}

int main()
{
    std::cout << "Test Push Back: " << (testPushBack() ? "PASSED" : "FAILED") << "\n";
    std::cout << "Test Push Front: " << (testPushFront() ? "PASSED" : "FAILED") << "\n";
    std::cout << "Test Pop Back: " << (testPopBack() ? "PASSED" : "FAILED") << "\n";
    std::cout << "Test Pop Front: " << (testPopFront() ? "PASSED" : "FAILED") << "\n";
    std::cout << "Test Emplace Back: " << (testEmplaceBack() ? "PASSED" : "FAILED") << "\n";
    std::cout << "Test Emplace Front: " << (testEmplaceFront() ? "PASSED" : "FAILED") << "\n";
    std::cout << "Test Front and Back Access: " << (testFrontBackAccess() ? "PASSED" : "FAILED") << "\n";
    std::cout << "Test Is Empty: " << (testIsEmpty() ? "PASSED" : "FAILED") << "\n";
    std::cout << "Test Resize: " << (testResize() ? "PASSED" : "FAILED") << "\n";
    std::cout << "Test Iterator Increment: " << (testIteratorIncrement() ? "PASSED" : "FAILED") << "\n";
    std::cout << "Test Iterator Decrement: " << (testIteratorDecrement() ? "PASSED" : "FAILED") << "\n";
    std::cout << "Test Iterator Equality: " << (testIteratorEquality() ? "PASSED" : "FAILED") << "\n";
    std::cout << "Test Const Iterator: " << (testConstIterator() ? "PASSED" : "FAILED") << "\n";
    std::cout << "Test Iterator Dereference: " << (testIteratorDereference() ? "PASSED" : "FAILED") << "\n";
    std::cout << "Test Copy Constructor: " << (testCopyConstructor() ? "PASSED" : "FAILED") << "\n";
    std::cout << "Test Move Constructor And Assignment: " << (testMoveAndAssignment() ? "PASSED" : "FAILED") << "\n";

    return 0;
}