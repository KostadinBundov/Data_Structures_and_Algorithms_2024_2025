#include <iostream>
#include <vector>
#include <algorithm>

std::vector<int> numberGame(std::vector<int>& nums) {
	std::sort(nums.begin(), nums.end());

	std::vector<int> result(nums.size());

	for (int i = 0; i < nums.size() - 1; i+= 2)
	{
		result[i] = nums[i + 1];
		result[i + 1] = nums[i];
	}

	return result;
}

int main()
{
	std::vector<int> arr = { 5,4,2,3 };
	std::vector<int> res = numberGame(arr);

	for (int i = 0; i < res.size(); i++)
	{
		std::cout << res[i] << " ";
	}
}