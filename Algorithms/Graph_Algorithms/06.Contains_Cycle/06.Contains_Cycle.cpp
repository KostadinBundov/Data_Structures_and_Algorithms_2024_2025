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

	bool containsCycleUnoriented(size_t vertex, size_t parent, std::vector<bool>& visited) {
		visited[vertex] = true;

		for (int i = 0; i < adj[vertex].size(); i++) {
			size_t neighbour = adj[vertex][i].first;

			if (neighbour == parent) {
				continue;
			}

			if (!visited[neighbour]) {
				if (containsCycleUnoriented(neighbour, vertex, visited)) {
					return true;
				}
			}
			else {
				return true;
			}
		}

		return false;
	}

	bool containsCycleDFS(size_t vertex, std::vector<bool>& visited, std::vector<bool>& gray) {
		gray[vertex] = true;
		visited[vertex] = true;

		for (int i = 0; i < adj[vertex].size(); i++) {
			size_t neighbour = adj[vertex][i].first;

			if (!visited[neighbour]) {
				if (containsCycleDFS(neighbour, visited, gray)) {
					return true;
				}
			}

			if (gray[neighbour]) {
				return true;
			}
		}

		gray[vertex] = false;
		return false;
	}

	bool containsCycle() {
		std::vector<bool> visited(adj.size(), false);
		std::vector<bool> gray(adj.size(), false);
		bool containsCycle = false;

		for (int i = 0; i < adj.size(); i++) {
			if (!visited[i]) {
				bool check = containsCycleDFS(i, visited, gray);

				if (check) {
					return true;
				}
			}
		}

		return false;
	}
};

int main() {
}