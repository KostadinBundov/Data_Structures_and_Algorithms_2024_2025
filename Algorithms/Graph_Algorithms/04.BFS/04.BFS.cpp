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


	void bfsTraversal(size_t index, std::vector<bool>& visited) const {
		std::queue<size_t > q;

		while (!q.empty()) {
			size_t vertex = q.front();
			q.pop();

			for (auto neighbour : adj[vertex]) {
				if (!visited[neighbour.first]) {
					q.push(neighbour.first);
					visited[neighbour.first] = true;
				}
			}
		}
	}
};

int main() {
	
}