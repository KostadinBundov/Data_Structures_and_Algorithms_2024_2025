#include <iostream>
#include <vector>
#include <algorithm>

int minPairSum(std::vector<int>& nums) {
	std::sort(nums.begin(), nums.end());
	int max = INT32_MIN;
	int border = nums.size() / 2;

	for (int i = 0; i < border; i++)
	{
		int currentSum = nums[i] + nums[nums.size() - 1 - i];

		if (currentSum > max) {
			max = currentSum;
		}
	}

	return max;
}

int main()
{

}