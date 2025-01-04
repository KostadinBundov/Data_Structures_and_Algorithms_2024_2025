#pragma once

#include <iostream>
#include <vector>

#include "Color.h"

class Traversal {
public:
	Traversal(std::vector<std::vector<int>> graph, size_t startIndex);

	bool operator<(const Traversal& other) const;
	friend std::ostream& operator<<(std::ostream& os, const Traversal& traversal);

	const std::vector<std::pair<int, int>>& getTreeEdges() const;
	const std::vector<std::pair<int, int>>& getBackEdges() const;
	const std::vector<std::pair<int, int>>& getForwardEdges() const;
	const std::vector<std::pair<int, int>>& getCrossEdges() const;

private:
	std::vector<int> spanningTree;
	std::vector<int> path;
	size_t startIndex;

	std::vector<std::pair<int, int>> treeEdges;
	std::vector<std::pair<int, int>> backEdges;
	std::vector<std::pair<int, int>> forwardEdges;
	std::vector<std::pair<int, int>> crossEdges;

	void dfs(const std::vector<std::vector<int>>& graph, std::vector<Color>& coloredGraph, size_t startIndex);
	void determineEdgeType(const std::vector<Color>& coloredGraph, size_t startvertex, size_t endVertex);

	void exploreGraph(const std::vector<std::vector<int>>& graph);
	bool checkIsVertexDescendant(size_t root, size_t toCheck) const;
};