#pragma once

#include "Traversal.h"

#include <set>
#include <vector>

class DfsTraversalsCollection {
public:
    class ConstIterator {
    public:
        ConstIterator(std::set<Traversal>::iterator it);

        const Traversal& operator*() const;
        const Traversal* operator->() const;

        ConstIterator& operator++();
        ConstIterator operator++(int);

        ConstIterator& operator--();
        ConstIterator operator--(int);

        bool operator==(const ConstIterator& other) const;
        bool operator!=(const ConstIterator& other) const;

    private:
        std::set<Traversal>::iterator it;
    };

	DfsTraversalsCollection(std::vector<std::vector<int>> graph, size_t startIndex);

    ConstIterator begin() const { return ConstIterator(traversals.begin()); }
    ConstIterator end() const { return ConstIterator(traversals.end()); }

private:
    std::set<Traversal> traversals;

    void getArrayPermutations(std::vector<int>& arr, std::vector<std::vector<int>>& permutations, size_t index) const;
    void getAllGraphTraversals(std::vector<std::vector<int>>& adjacencyList, size_t vertexIndexð, size_t startIndex);
};