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


	int shortestPath(size_t start, size_t end) {
		std::vector<bool> visited(adj.size(), false);

		std::queue<size_t> q;
		q.push(start);
		visited[start] = true;

		size_t pathLength = 0;

		while (!q.empty()) {
			size_t levelSize = q.size();

			for (int i = 0; i < levelSize; i++) {
				size_t currVertex = q.front();
				q.pop();

				for (int j = 0; j < adj[currVertex].size(); j++) {
					size_t neighbour = adj[currVertex][j].first;

					if (visited[neighbour]) {
						continue;
					}

					if (neighbour == end) {
						return pathLength + 1;
					}

					q.push(neighbour);
					visited[neighbour] = true;
				}
			}

			pathLength++;
		}

		return -1;
	}
};

int main() {
}