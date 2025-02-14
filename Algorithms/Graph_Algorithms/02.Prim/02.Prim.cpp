#include <iostream>
#include <queue>
#include <vector>

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

	size_t primAlgorithm(std::vector<Edge>& edges) {
		size_t foundEdges = 0;
		std::priority_queue<Edge> pq;
		pq.push({ 0, 0, 0 });

		std::vector<bool> visited(adj.size(), false);

		int result = 0;
		bool isFirstTraverse = true;

		while (foundEdges < V - 1) {
			Edge currEdge = pq.top();
			pq.pop();

			size_t from = currEdge.from;
			size_t to = currEdge.to;
			int weight = currEdge.weight;

			if (visited[to]) {
				continue;
			}

			visited[to] = true;

			for (auto curr : adj[to]) {
				pq.push({ to, curr.first, curr.second });
			}

			if (isFirstTraverse) {
				isFirstTraverse = false;
				continue;
			}

			result += weight;
			foundEdges++;
			edges.push_back(currEdge);
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

	size_t shortestPath = g.primAlgorithm(path);

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