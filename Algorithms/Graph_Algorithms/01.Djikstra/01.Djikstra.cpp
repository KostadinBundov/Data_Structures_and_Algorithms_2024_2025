#include <iostream> 
#include <vector>
#include <queue>

class Graph {
public:
	Graph(size_t size, bool isOriented) : adj(size), isOriented(isOriented) { }

	void addEdge(int start, int end, int weight) {
		adj[start].push_back({ end, weight });

		if (!isOriented) {
			adj[end].push_back({ start, weight });
		}
	}

	size_t djikstra(int start, int end, std::vector<int>& path) {
		struct distanceToVertex {
			int vertex;
			int distance;

			distanceToVertex(int vertex, int distance) : vertex(vertex), distance(distance) { }

			bool operator<(const distanceToVertex& other) const {
				return distance > other.distance;
			}
		};

		std::vector<int> distances(adj.size(), INT32_MAX);
		distances[start] = 0;

		std::priority_queue<distanceToVertex> pq;
		pq.push(distanceToVertex(start, 0));

		std::vector<int> parentArr(adj.size());

		while (!pq.empty()) {
			distanceToVertex nearestDistanceToVertexInfo = pq.top();
			pq.pop();

			int vertex = nearestDistanceToVertexInfo.vertex;
			int currDistance = nearestDistanceToVertexInfo.distance;

			if (vertex == end) {
				int currParent = parentArr[end];
				while (currParent != start) {
					path.push_back(currParent);
					currParent = parentArr[currParent];
				}

				std::reverse(path.begin(), path.end());
				break;
			}

			for (auto neighbour : adj[vertex]) {
				int newDistance = currDistance + neighbour.second;

				if (distances[neighbour.first] > newDistance) {
					distances[neighbour.first] = newDistance;
					parentArr[neighbour.first] = vertex;
					pq.push(distanceToVertex(neighbour.first, newDistance));
				}

			}
		}

		return distances[end];
	}

private:
	std::vector<std::vector<std::pair<int, int>>> adj;
	bool isOriented = false;
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

	std::vector<int> v;
	size_t shortestPath = g.djikstra(0, 4, v);

	std::cout << shortestPath;
}