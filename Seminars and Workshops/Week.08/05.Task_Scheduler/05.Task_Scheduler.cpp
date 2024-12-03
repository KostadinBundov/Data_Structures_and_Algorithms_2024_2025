#include <iostream>
#include <vector>
#include <queue>
#include <map>

struct comp {
	bool operator()(std::pair<char, int> a, std::pair<char, int> b) {
		return a.second < b.second;
	}
};

int leastInterval(std::vector<char>& tasks, int n) {
	std::map<char, int> map;

	for (int i = 0; i < tasks.size(); i++) {
		map[tasks[i]]++;
	}

	std::priority_queue<std::pair<char, int>, std::vector<std::pair<char, int>>, comp> pq;

	for (auto mapEntity : map) {
		pq.push(mapEntity);
	}

	int totalIntervalsCount = 0;

	while (!pq.empty()) {
		std::vector<std::pair<char, int>> forLater;
		int currInterval = 0;

		while (!pq.empty() && currInterval <= n) {
			std::pair<char, int> currPair = pq.top();
			pq.pop();

			if (currPair.second > 1) {
				forLater.push_back({ currPair.first, currPair.second - 1 });
			}

			totalIntervalsCount++;
			currInterval++;
		}

		for (auto val : forLater) {
			pq.push(val);
		}

		if (!pq.empty()) {
			totalIntervalsCount += (n - currInterval + 1);
		}
	}

	return totalIntervalsCount;
}

int main() {
	std::vector<char> arr = { 'A','C','A','B','D','B' };
	//std::vector<char> arr = { 'A','A','A','B','B','B' };
	std::cout << leastInterval(arr, 1);
}