#include <iostream>
#include "DfsTraversalsCollection.h"

int main() {
    std::vector<std::vector<int>> graph = {
        {1, 2},  // Връх 0
        {2, 3},  // Връх 1
        {1},     // Връх 2
        {0}      // Връх 3
    };

    // Създаваме колекцията от DFS обхождания
    DfsTraversalsCollection collection(graph, 0);

    // Обхождане на всички DFS обхождания
    std::cout << "All dfs traversals:\n";

    for (auto it = collection.begin(); it != collection.end(); ++it) {
        Traversal current = *it;

        // Отпечатване на пътя
        std::cout << "Path: " << current << std::endl;

        // Tree edges
        auto tree = current.getTreeEdges();
        std::cout << "Tree edges: ";
        for (auto var : tree) {
            std::cout << "(" << var.first << " - " << var.second << ") ";
        }
        std::cout << std::endl;

        // Back edges
        auto back = current.getBackEdges();
        std::cout << "Back edges: ";
        for (auto var : back) {
            std::cout << "(" << var.first << " - " << var.second << ") ";
        }
        std::cout << std::endl;

        // Forward edges
        auto forward = current.getForwardEdges();
        std::cout << "Forward edges: ";
        for (auto var : forward) {
            std::cout << "(" << var.first << " - " << var.second << ") ";
        }
        std::cout << std::endl;

        // Cross edges
        auto cross = current.getCrossEdges();
        std::cout << "Cross edges: ";
        for (auto var : cross) {
            std::cout << "(" << var.first << " - " << var.second << ") ";
        }
        std::cout << std::endl;

        // Разделител между обхожданията
        std::cout << "-----------------------------\n";
    }

    return 0;
}
