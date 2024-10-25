#include <iostream>
#include <vector>
#include <algorithm>

int maximumProduct(std::vector<int>& nums) {
	std::sort(nums.begin(), nums.end());

	int firstSum = nums[nums.size() - 1] * nums[nums.size() - 2] * nums[nums.size() - 3];
	int secondSum = nums[0] * nums[1] * nums[nums.size() - 1];

	return std::max(firstSum, secondSum);
}

int main()
{
	std::vector<int> arr = { -100,-98,-1,2,3,4 };
	std::cout << maximumProduct(arr);
}