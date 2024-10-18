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

int maxProduct(std::vector<int>& nums) {

	sort(nums.data(), nums.size());

	return (nums[nums.size() - 1] - 1) * (nums[nums.size() - 2] - 1);
}

int main()
{
	std::vector<int> nums = { 1,5,4,5 };

	std::cout << maxProduct(nums);
}