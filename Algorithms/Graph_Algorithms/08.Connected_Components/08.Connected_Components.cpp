#include <iostream>
#include <vector>
#include <queue>
#include <stack>

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

	void dfsTraversal(size_t index, std::vector<bool>& visited) const {
		visited[index] = true;

		for (int i = 0; i < adj[index].size(); i++) {
			if (!visited[adj[index][i].first]) {
				dfsTraversal(adj[index][i].first, visited);
			}
		}
	}

	size_t getComponentsCount() const {
		size_t result = 0;
		std::vector<bool> visited(adj.size(), false);

		for (int i = 0; i < adj.size(); i++) {
			if (!visited[i]) {
				dfsTraversal(i, visited);
				result++;
			}
		}

		return result;
	}
};

int main() {
}