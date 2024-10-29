#include <iostream>
#include <vector>
#include <algorithm>

bool predicate(const std::pair<int, int>& a, const std::pair<int, int>& b) {
	if (a.first < b.first) {
		return true;
	}
	else if (a.first == b.first) {
		return a.second <= b.second;
	}
	else {
		return false;
	}
}

std::vector<std::pair<int, int>> unionIntervals(std::vector<std::pair<int, int>>& intervals) {
	std::sort(intervals.begin(), intervals.end(), predicate);

	std::vector<std::pair<int, int>> resultIntervals;

	std::pair<int, int> currentInterval = intervals[0];

	for (int i = 1; i < intervals.size(); i++) {
		if (intervals[i].first <= currentInterval.second) {
			currentInterval.second = std::max(currentInterval.second, intervals[i].second);
		}
		else {
			resultIntervals.push_back(currentInterval);
			currentInterval = intervals[i];
		}
	}

	resultIntervals.push_back(currentInterval);

	return resultIntervals;
}

int main()
{
	std::vector<std::pair<int, int>> intervals = { {1, 3}, {2, 4}, {5, 7}, {6, 8} };
	std::vector<std::pair<int, int>> result = unionIntervals(intervals);

	for (int i = 0; i < result.size(); i++) {
		std::cout << "[" << result[i].first << ", " << result[i].second << "]" << std::endl;
	}
}