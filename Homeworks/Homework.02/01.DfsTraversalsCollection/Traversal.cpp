#include "Traversal.h"

void Traversal::dfs(const std::vector<std::vector<int>>& graph, std::vector<Color>& coloredGraph, size_t vertexIndex) {
	path.push_back(vertexIndex);

	coloredGraph[vertexIndex] = Color::GRAY;

	for (auto neighbour : graph[vertexIndex]) {
		determineEdgeType(coloredGraph, vertexIndex, neighbour);

		if (coloredGraph[neighbour] == Color::WHITE) {
			spanningTree[neighbour] = vertexIndex;
			dfs(graph, coloredGraph, neighbour);
		}
	}

	coloredGraph[vertexIndex] = Color::BLACK;
}

void Traversal::determineEdgeType(const std::vector<Color>& coloredGraph, size_t startVertex, size_t endVertex) {
	switch (coloredGraph[endVertex])
	{
	case Color::WHITE:
		treeEdges.push_back(std::make_pair(startVertex, endVertex));
		break;
	case Color::GRAY:
		backEdges.push_back(std::make_pair(startVertex, endVertex));
		break;
	case Color::BLACK:
		if (checkIsVertexDescendant(startVertex, endVertex)) {
			forwardEdges.push_back(std::make_pair(startVertex, endVertex));
		}
		else {
			crossEdges.push_back(std::make_pair(startVertex, endVertex));
		}

		break;
	}
}

void Traversal::exploreGraph(const std::vector<std::vector<int>>& graph) {
	std::vector<Color> coloredGraph(graph.size(), Color::WHITE);
	dfs(graph, coloredGraph, startIndex);
}

bool Traversal::checkIsVertexDescendant(size_t root, size_t toCheck) const {
	int parent = spanningTree[toCheck];

	if (parent == -2) {
		return false;
	}

	while (parent != -1) {
		if (parent == root) {
			return true;
		}

		parent = spanningTree[parent];
	}

	return false;
}

Traversal::Traversal(std::vector<std::vector<int>> graph, size_t startIndex) {
	this->startIndex = startIndex;

	spanningTree.resize(graph.size(), -2);
	spanningTree[startIndex] = -1;

	exploreGraph(graph);
}

bool Traversal::operator<(const Traversal& other) const {
	return path < other.path;
}

const std::vector<std::pair<int, int>>& Traversal::getTreeEdges() const {
	return treeEdges;
}

const std::vector<std::pair<int, int>>& Traversal::getBackEdges() const {
	return backEdges;
}

const std::vector<std::pair<int, int>>& Traversal::getForwardEdges() const {
	return forwardEdges;
}

const std::vector<std::pair<int, int>>& Traversal::getCrossEdges() const {
	return crossEdges;
}

std::ostream& operator<<(std::ostream& os, const Traversal& traversal) {
	for (size_t i = 0; i < traversal.path.size(); i++) {
		os << traversal.path[i];

		if (i < traversal.path.size() - 1) {
			os << " ";
		}
	}

	return os;
}