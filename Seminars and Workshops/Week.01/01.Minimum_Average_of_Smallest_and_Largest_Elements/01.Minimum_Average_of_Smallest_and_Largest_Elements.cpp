#include <iostream>
#include <vector>

void sort(int* arr, size_t size) {
	for (int i = 0; i < size - 1; i++) {
		unsigned smallestElementIndex = i;

		for (int j = i + 1; j < size; j++) {
			if (arr[smallestElementIndex] > arr[j]) {
				smallestElementIndex = j;
			}
		}

		if (smallestElementIndex != i) {
			std::swap(arr[i], arr[smallestElementIndex]);
		}
	}
}

double minimumAverage(std::vector<int>& nums) {

	sort(nums.data(), nums.size());

	double minAverageValue = DBL_MAX;

	int border = nums.size() / 2;

	for (int i = 0, j = nums.size() - 1; i < border; i++, j--) {
		double currentAverageValue = (nums[i] + nums[j]) / 2.0;

		if (minAverageValue > currentAverageValue) {
			minAverageValue = currentAverageValue;
		}
	}

	return minAverageValue;
}

int main()
{
	int n;
	std::cin >> n;

	std::vector<int> nums = { 7, 8, 3, 4, 15, 13, 4, 1 };

	std::cout << minimumAverage(nums);
}