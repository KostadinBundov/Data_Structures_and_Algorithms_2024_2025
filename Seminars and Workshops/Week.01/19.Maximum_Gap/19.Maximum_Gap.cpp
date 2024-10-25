#include <iostream>
#include <vector>
#include <algorithm>

void countingSort(std::vector<int>& arr) {
	int lowerBound = *std::min_element(arr.begin(), arr.end());
	int upperBound = *std::max_element(arr.begin(), arr.end());

	std::vector<int> counter(upperBound - lowerBound + 1, 0);

	for (int i = 0; i < arr.size(); i++) {
		counter[arr[i] - lowerBound]++;
	}

	for (int i = 1; i < counter.size(); i++) {
		counter[i] += counter[i - 1];
	}

	std::vector<int> sortedArr(arr.size());

	for (int i = arr.size() - 1; i >= 0; i--) {
		int index = arr[i] - lowerBound;
		int indexToPut = counter[index] - 1;
		sortedArr[indexToPut] = arr[i];
		counter[index]--;
	}

	for (int i = 0; i < arr.size(); i++) {
		arr[i] = sortedArr[i];
	}
}

int maximumGap(std::vector<int>& nums) {
	if (nums.size() < 2) {
		return 0;
	}

	countingSort(nums);

	int maxDifference = INT32_MIN;

	for (int i = 0; i < nums.size() - 1; i++) {
		int currentDifference = nums[i + 1] - nums[i];

		if (currentDifference > maxDifference) {
			maxDifference = currentDifference;
		}
	}

	return maxDifference;
}

int main()
{
	std::vector<int> nums = { 3, 6, 9, 1 };
	std::cout << maximumGap(nums);
}