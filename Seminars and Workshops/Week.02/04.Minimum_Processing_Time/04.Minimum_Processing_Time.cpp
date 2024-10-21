#include <iostream>
#include <vector>
#include <algorithm>

constexpr int CORES_COUNT = 4;

int minProcessingTime(std::vector<int>& processorTime, std::vector<int>& tasks) {
	std::sort(processorTime.begin(), processorTime.end());
	std::sort(tasks.begin(), tasks.end(), [](int a, int b) {return a > b; });

	int minProcessingTime = INT32_MIN;
	int current = INT32_MIN;
	int processorIndex = 0;

	for (int i = 0; i < tasks.size(); i++) {
		current = std::max(current, tasks[i] + processorTime[processorIndex]);

		if ((i + 1) % CORES_COUNT == 0) {
			minProcessingTime = std::max(minProcessingTime, current);
			processorIndex++;
			current = INT32_MIN;
		}
	}

	return minProcessingTime;
}

int main() {
	std::vector<int> tasks = { 2, 2, 3, 1, 8, 7, 4, 5 };
	std::vector<int> processorTime = { 8, 10 };
	std::cout << minProcessingTime(processorTime, tasks) << std::endl;

	std::vector<int> tasks2 = { 2,3,1,2,5,8,4,3 };
	std::vector<int> processorTime2 = { 10, 20 };
	std::cout << minProcessingTime(processorTime2, tasks2) << std::endl;
}