#include <iostream>
#include <vector>
#include <algorithm>

int largestPerimeter(std::vector<int>& nums) {
	std::sort(nums.rbegin(), nums.rend());
	int border = nums.size() - 2;

	for (int i = 0; i < border; i++) {
		int currentSum = nums[i + 1] + nums[i + 2];
		if (currentSum > nums[i]) {
			return currentSum + nums[i];
		}
	}

	return 0;
}

int main()
{
	std::vector<int> arr1 = { 2, 1, 2 };
	std::vector<int> arr2 = { 1, 2, 1, 10 };

	std::cout << largestPerimeter(arr1) << std::endl;
	std::cout << largestPerimeter(arr2) << std::endl;
}