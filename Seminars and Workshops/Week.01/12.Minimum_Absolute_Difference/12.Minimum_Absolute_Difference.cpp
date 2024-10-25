#include <iostream>
#include <vector>
#include <algorithm>

	std::vector<std::vector<int>> minimumAbsDifference(std::vector<int>& arr) {
		std::sort(arr.begin(), arr.end());
		int minAbsDifference = INT32_MAX;

		for (int i = 0; i < arr.size() - 1; i++)
		{
			int currentDiff = abs(arr[i + 1] - arr[i]);

			if (currentDiff < minAbsDifference) {
				minAbsDifference = currentDiff;
			}
		}

		std::vector<std::vector<int>> pairs;

		for (int i = 0; i < arr.size() - 1; i++) {
			if (arr[i + 1] - arr[i] == minAbsDifference) {
				pairs.push_back(std::vector<int>({ arr[i], arr[i + 1] }));
			}
		}

		return pairs;
	}

void printPairs(std::vector<std::vector<int>> arr) {
	for (int i = 0; i < arr.size(); i++) {
		for (int j = 0; j < arr[i].size(); j++) {
			std::cout << arr[i][j] << " ";
		}
		std::cout << std::endl;
	}
}

int main() {
	std::vector<int> arr = { 40,11,26,27,-20 };
	printPairs(minimumAbsDifference(arr));
}