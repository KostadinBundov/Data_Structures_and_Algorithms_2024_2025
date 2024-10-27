#include <iostream>
#include <vector>
#include <algorithm>

std::vector<int> sortArrayByParity(std::vector<int>& nums) {
	std::vector<int> result(nums.size());

	int leftIndex = 0;
	int rightIndex = nums.size() - 1;

	for (int i = 0; i < nums.size(); i++)
	{
		if (nums[i] % 2 == 0) {
			result[leftIndex++] = nums[i];
		}
		else {
			result[rightIndex--] = nums[i];
		}
	}

	return result;
}

int main()
{
	std::vector<int> arr = { 3, 1, 2, 4 };
	std::vector<int> result = sortArrayByParity(arr);

	for (int i = 0; i < result.size(); i++)
	{
		std::cout << result[i] << " ";
	}
}