#include <iostream>
#include <vector>
#include <queue>
#include <string>

std::vector<std::string> findRelativeRanks(std::vector<int>& score) {
	std::priority_queue<int> pq(score.begin(), score.end());
	std::vector<std::string> rank(score.size());

	unsigned ranking = 1;

	while (!pq.empty()) {
		int athlete = pq.top();
		pq.pop();

		int index = std::find(score.begin(), score.end(), athlete) - score.begin();

		switch (ranking)
		{
		case 1:
			rank[index] = "Gold Medal";
			break;
		case 2:
			rank[index] = "Silver Medal";
			break;
		case 3:
			rank[index] = "Bronze Medal";
			break;
		default:
			rank[index] = std::to_string(ranking);
			break;
		}

		ranking++;
	}

	return rank;
}

int main() {

}