#include <iostream>
#include "TreeSet.hpp"

bool testInsert()
{
    TreeSet<int> tree;

    if (!tree.add(10)) return false;
    if (!tree.add(5)) return false;
    if (!tree.add(20)) return false;
    if (tree.add(10)) return false; // Duplicate insert should return false

    if (tree.getSize() != 3) return false; // Only 3 unique elements inserted
    if (!tree.find(10)) return false;
    if (!tree.find(5)) return false;
    if (!tree.find(20)) return false;
    if (tree.find(15)) return false;

    return true;
}

bool testFind()
{
    TreeSet<int> tree;
    tree.add(10);
    tree.add(5);
    tree.add(20);

    if (!tree.find(10)) return false;
    if (!tree.find(5)) return false;
    if (!tree.find(20)) return false;
    if (tree.find(15)) return false; // 15 is not in the tree

    return true;
}

bool testRemove()
{
    TreeSet<int> tree;
    tree.add(10);
    tree.add(5);
    tree.add(20);

    if (!tree.remove(5)) return false; // 5 should be removed
    if (tree.find(5)) return false; // 5 should no longer be in the tree
    if (tree.getSize() != 2) return false;

    if (!tree.remove(10)) return false; // 10 should be removed
    if (tree.find(10)) return false; // 10 should no longer be in the tree
    if (tree.getSize() != 1) return false;

    if (!tree.remove(20)) return false; // 20 should be removed
    if (tree.find(20)) return false; // 20 should no longer be in the tree
    if (!tree.isEmpty()) return false; // Tree should be empty now

    return true;
}

bool testCustomComparator()
{
    auto comp = [](int a, int b) { return a > b; };
    TreeSet<int, decltype(comp)> tree(comp);

    tree.add(10);
    tree.add(5);
    tree.add(20);

    if (!tree.find(10)) return false;
    if (!tree.find(5)) return false;
    if (!tree.find(20)) return false;

    // Testing the order through structure traversal (in this case, assumed order check)
    if (tree.getSize() != 3) return false;
    return true;
}

int main()
{
    TreeSet<int> b;
    b.add(3);
    b.add(1);
    b.add(2);
    b.add(4);
    b.add(0);

    std::cout << "Test Insert: " << (testInsert() ? "Passed" : "Failed") << std::endl;
    std::cout << "Test Find: " << (testFind() ? "Passed" : "Failed") << std::endl;
    std::cout << "Test Remove: " << (testRemove() ? "Passed" : "Failed") << std::endl;
    std::cout << "Test Custom Comparator: " << (testCustomComparator() ? "Passed" : "Failed") << std::endl;

    return 0;
}
