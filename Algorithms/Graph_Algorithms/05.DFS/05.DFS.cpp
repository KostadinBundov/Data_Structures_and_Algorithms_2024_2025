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

	void dfsIterTraversal(size_t index) {
		std::vector<bool> visited(adj.size(), false);

		std::stack<size_t> s;
		s.push(index);

		while (!s.empty()) {
			size_t vertex = s.top();
			s.pop();

			if (visited[vertex]) {
				continue;
			}

			visited[vertex] = true;
			std::cout << vertex << " ";

			for (auto pair : adj[vertex]) {
				size_t neighbour = pair.first;

				s.push(neighbour);
			}
		}
	}

	void dfsRecTraversal(size_t index, std::vector<bool>& visited) {
		visited[index] = true;
		std::cout << index << " ";

		for (auto it : adj[index]) {
			if (!visited[it.first]) {
				dfsRecTraversal(it.first, visited);
			}
		}
	}

	void dfsRec(size_t index) {
		std::vector<bool> visited(adj.size(), false);
		dfsRecTraversal(index, visited);
	}

	void dfsTraversal(size_t index, std::vector<bool>& visited) const {
		visited[index] = true;

		for (int i = 0; i < adj[index].size(); i++) {
			if (!visited[adj[index][i].first]) {
				dfsTraversal(adj[index][i].first, visited);
			}
		}
	}
};

int main() {

}