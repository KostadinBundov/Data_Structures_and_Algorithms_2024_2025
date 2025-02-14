#include <iostream>
#include <queue>
#include <vector>

class DisjointSet {
	std::vector<size_t> parents;
	std::vector<size_t> heights;

	size_t getParent(size_t vertex) {
		if (parents[vertex] != vertex) {
			parents[vertex] = getParent(parents[vertex]);
		}

		return parents[vertex];
	}
public:
	DisjointSet(size_t size) {
		parents.resize(size);
		heights.resize(size, 1);

		for (int i = 0; i < size; i++) {
			parents[i] = i;
		}
	}

	bool areInOneSet(size_t first, size_t second) {
		return getParent(first) == getParent(second);
	}

	bool Union(size_t first, size_t second) {
		size_t firstParent = getParent(first);
		size_t secondParent = getParent(second);

		if (firstParent == secondParent) { return false; }

		if (heights[firstParent] == heights[secondParent]) {
			parents[firstParent] = secondParent;
			heights[secondParent]++;
		}
		else if (heights[secondParent] > heights[firstParent]) {
			parents[firstParent] = secondParent;
		}
		else {
			parents[secondParent] = firstParent;
		}

		return true;
	}
};

struct Edge {
	Edge(size_t from, size_t to, int weight) : from(from), to(to), weight(weight) { }
	size_t from;
	size_t to;
	int weight;
	bool operator<(const Edge& other) const { return weight > other.weight; }
};

class Graph {
private:
	bool isOriented;
	size_t V;
	std::vector<std::vector<std::pair<size_t, int>>> adj;

public:
	Graph(size_t size, bool isOriented) : isOriented(isOriented), V(size) {
		adj.resize(size);
	}

	void addEdge(size_t from, size_t to, int weight) {
		adj[from].push_back({ to, weight });

		if (!isOriented) {
			adj[to].push_back({ from, weight });
		}
	}

	size_t kruskalAlgorithm(std::vector<Edge>& resultEdges) {
		std::vector<Edge> edges;

		for (int i = 0; i < V; i++) {
			for (int j = 0; i < adj[i].size(); j++) {
				edges.push_back({ i, adj[i][j].first, adj[i][j].second });
			}
		}

		std::sort(edges.begin(), edges.end());

		size_t foundEdges = 0;
		int result = 0;
		DisjointSet set(V);

		for (int i = 0; i < edges.size() && foundEdges < V - 1; i++) {
			if (set.Union(edges[i].from, edges[i].to)) {
				result += edges[i].weight;
				foundEdges++;
				resultEdges.push_back(edges[i]);
			}
		}

		return result;
	}
};

int main() {
	Graph g(6, false); 

	g.addEdge(0, 1, 7);
	g.addEdge(0, 2, 9);
	g.addEdge(0, 5, 14);
	g.addEdge(1, 2, 10);
	g.addEdge(1, 3, 15);
	g.addEdge(2, 3, 11);
	g.addEdge(2, 5, 2);
	g.addEdge(3, 4, 6);
	g.addEdge(4, 5, 9);

	size_t start = 0;
	size_t end = 4;
	std::vector<Edge> path;

	size_t shortestPath = g.kruskalAlgorithm(path);

	if (shortestPath == INT32_MAX) {
		std::cout << "No path found from " << start << " to " << end << ".\n";
	}
	else {
		std::cout << "Shortest path from " << start << " to " << end << ": " << shortestPath << std::endl;
		std::cout << "Path: ";
		for (auto vertex : path) {
			std::cout << vertex.from << "-" << vertex.to << " ";
		}
		std::cout << std::endl;
	}

	return 0;
}