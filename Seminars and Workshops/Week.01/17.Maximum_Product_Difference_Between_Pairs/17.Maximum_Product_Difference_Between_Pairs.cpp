#include <iostream>
#include <vector>
#include <algorithm>

int maxProductDifference(std::vector<int>& nums) {
	std::sort(nums.begin(), nums.end());

	return (nums[nums.size() - 1] * nums[nums.size() - 2]) - (nums[0] * nums[1]);
}

int maxProductDifference2(std::vector<int>& nums) {
	int firstMin = INT32_MAX;
	int secondMin = INT32_MAX;
	int firstMax = INT32_MIN;
	int secondMax = INT32_MIN;

	for (int i = 0; i < nums.size(); i++)
	{
		if (nums[i] >= firstMax) {
			secondMax = firstMax;
			firstMax = nums[i];
		}
		else if (nums[i] > secondMax) {
			secondMax = nums[i];
		}

		if (nums[i] <= firstMin) {
			secondMin = firstMin;
			firstMin = nums[i];
		}
		else if (nums[i] < secondMin) {
			secondMin = nums[i];
		}
	}

	return firstMax * secondMax - firstMin * secondMin;
}

int main()
{
	std::vector<int> arr = { 1,6,7,5,2,4,10,6,4 };
	std::cout << maxProductDifference2(arr);
}