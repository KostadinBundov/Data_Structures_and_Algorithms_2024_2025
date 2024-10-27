#include <iostream>
#include <vector>
#include <algorithm>

int countPairs(std::vector<int>& nums, int target) {
	std::sort(nums.begin(), nums.end());
	int counter = 0;

	int left = 0;
	int right = nums.size() - 1;

	while (left < right) {
		if (nums[left] + nums[right] < target) {
			counter += right - left;
			left++;
		}
		else {
			right--;
		}
	}

	return counter;
}

int main()
{
	std::vector<int> nums = { -1,1,2,3,1 };
	std::cout << countPairs(nums, 2);
}