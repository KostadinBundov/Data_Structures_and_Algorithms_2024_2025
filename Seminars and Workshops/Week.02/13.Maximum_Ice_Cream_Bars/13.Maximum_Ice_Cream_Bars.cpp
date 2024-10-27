#include <iostream>
#include <vector>
#include <algorithm>

void countingSort(std::vector<int>& costs) {
	constexpr int lowerBound = 1;
	constexpr int upperBound = 100000;
	size_t counterSize = abs(upperBound - lowerBound) + 1;

	std::vector<int> counter(counterSize, 0);

	for (int i = 0; i < costs.size(); i++) {
		counter[costs[i] - lowerBound]++;
	}

	for (int i = 1; i < counter.size(); i++) {
		counter[i] += counter[i - 1];
	}

	std::vector<int> result(costs.size());

	for (int i = costs.size() - 1; i >= 0; i--) {
		int counterIndex = costs[i] - lowerBound;
		int count = counter[counterIndex];

		result[count - 1] = costs[i];
		counter[counterIndex]--;
	}

	for (int i = 0; i < result.size(); i++)
	{
		costs[i] = result[i];
	}
}

int maxIceCream(std::vector<int>& costs, int coins) {
	countingSort(costs);

	int currentCost = 0;
	int count = 0;

	for (int i = 0; i < costs.size(); i++) {
		if (currentCost + costs[i] <= coins) {
			currentCost += costs[i];
			count++;
		}
		else {
			break;
		}
	}

	return count;
}

int main()
{
	std::vector<int> arr = { 1,6,3,1,2,5};
	std::cout << maxIceCream(arr, 20);
}