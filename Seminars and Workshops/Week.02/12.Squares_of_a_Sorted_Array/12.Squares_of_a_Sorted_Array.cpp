#include <iostream>
#include <vector>
#include <algorithm>

std::vector<int> sortedSquares(std::vector<int>& nums) {
	std::vector<int> result(nums.size());

	int left = 0;
	int right = nums.size() - 1;
	int index = nums.size() - 1;

	while (left <= right) {

		if (abs(nums[left]) > abs(nums[right])) {
			result[index--] = nums[left] * nums[left];
			left++;
		}
		else {
			result[index--] = nums[right] * nums[right];
			right--;
		}
	}

	return result;
}

int main()
{
	std::vector<int> arr = { -4,-1,0,3,10 };
	std::vector<int> result = sortedSquares(arr);

	for (int i = 0; i < result.size(); i++)
	{
		std::cout << result[i] << " ";
	}
}