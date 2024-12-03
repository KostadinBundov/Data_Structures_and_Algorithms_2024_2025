#include <iostream>
#include <vector>
#include <queue>

int lastStoneWeight(std::vector<int>& stones) {
	std::priority_queue<int> pq(stones.begin(), stones.end());

	while (pq.size() > 1) {
		int heaviestStone = pq.top();
		pq.pop();

		int secondHeaviestStone = pq.top();
		pq.pop();

		if (heaviestStone != secondHeaviestStone) {
			pq.push(heaviestStone - secondHeaviestStone);
		}
	}

	if (pq.empty()) {
		return 0;
	}
	else {
		return pq.top();
	}
}

int main() {
	std::vector<int> arr = { 2, 2 };

	std::cout << lastStoneWeight(arr);
}