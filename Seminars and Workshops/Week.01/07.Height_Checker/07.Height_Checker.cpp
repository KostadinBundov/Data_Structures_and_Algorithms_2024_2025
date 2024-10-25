#include <iostream>
#include <vector>
#include <algorithm>

int heightChecker(std::vector<int>& heights) {
	std::vector<int> sortedHeights(heights);
	std::sort(sortedHeights.begin(), sortedHeights.end());

	int counter = 0;

	for (int i = 0; i < heights.size(); i++)
	{
		if (heights[i] != sortedHeights[i]) {
			counter++;
		}
	}

	return counter;
}

int heightCheckerLinear(std::vector<int>& heights) {
	constexpr int lowerBound = 1;
	constexpr int upperBound = 100;
	int counterSize = abs(upperBound - lowerBound) + 1;
	std::vector<int> counter(counterSize, 0);

	for (int i = 0; i < heights.size(); i++) {
		counter[heights[i] - lowerBound]++;
	}

	for (int i = 1; i < counterSize; i++) {
		counter[i] += counter[i - 1];
	}

	int result = 0;

	for (int i = 0; i < heights.size(); i++) {
		int counterIndex = heights[i] - lowerBound;

		int previousIndex = counterIndex == 0 ? 0 : counter[counterIndex - 1];

		if (i < counter[counterIndex] && i >= previousIndex) {
			continue;
		}
		else {
			result++;
		}
	}

	return result;
}

int main()
{
	std::vector<int> arr = { 1,1,4,2,1,3 };
	std::cout << heightChecker(arr) << std::endl;
	std::cout << heightCheckerLinear(arr);
}