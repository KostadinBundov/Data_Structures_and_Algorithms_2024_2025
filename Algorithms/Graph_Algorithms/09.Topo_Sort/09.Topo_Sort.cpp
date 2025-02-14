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

			//the parent vertex
			if (neighbour == parent) {
				continue;
			}

			if (!visited[neighbour]) {
				//newly visited
				if (containsCycleUnoriented(neighbour, vertex, visited)) {
					return true;
				}
			}
			else {
				//already visited
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

	bool helper(size_t index, std::vector<bool>& visited, std::vector<bool>& gray) const {
		visited[index] = true;
		gray[index] = true;

		for (auto child : adj[index]) {
			if (!visited[child.first]) {
				bool check = helper(child.first, visited, gray);

				if (check) { return true; }
			}

			if (gray[child.first]) {
				return true;
			}
		}
	}

	bool cycle() const {
		std::vector<bool> visited(V, false);
		std::vector<bool> gray(V, false);

		for (int i = 0; i < V; i++) {
			if (!visited[i]) {
				bool check = helper(i, visited, gray);

				if (check) {
					return true;
				}
			}
		}

		return false;
	}

	void topoDfs(size_t index, std::vector<bool>& visited, std::vector<int>& result) const {
		visited[index] = true;

		for (auto child : adj[index]) {
			if (!visited[child.first]) {
				topoDfs(child.first, visited, result);
			}
		}

		result.push_back(index);
	}

	std::vector<int> topoSort() const {
		if (isOriented == false) {
			return {  };
		}
		if (cycle() == true) {
			return { };
		}

		std::vector<bool> visited(adj.size(), false);
		std::vector<int> sortedElements;

		for (int i = 0; i < V; i++) {
			if (!visited[i]) {
				topoDfs(i, visited, sortedElements);
			}
		}

		std::reverse(sortedElements.begin(), sortedElements.end());

		return sortedElements;
	}
};

int main() {
}