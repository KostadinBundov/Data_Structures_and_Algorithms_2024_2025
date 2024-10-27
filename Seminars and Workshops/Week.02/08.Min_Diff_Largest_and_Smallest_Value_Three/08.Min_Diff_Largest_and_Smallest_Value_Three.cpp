#include <iostream>
#include <vector>
#include <algorithm>

int minDifference(std::vector<int>& nums) {
    int maxRemovedElement = 3;

    if (nums.size() <= maxRemovedElement + 1) {
        return 0;
    }

    std::sort(nums.begin(), nums.end());

    int minIndex = 0;
    int maxIndex = nums.size() - 1;
    int minDifference = INT32_MAX;

    for (int i = 0; i <= maxRemovedElement; i++)
    {
        minIndex = i;
        maxIndex = nums.size() - 1 - (maxRemovedElement - i);
        int currDifference = nums[maxIndex] - nums[minIndex];

        if (currDifference < minDifference) {
            minDifference = currDifference;
        }
    }

    return minDifference;
}

int main()
{
	std::vector<int> nums = { 6,6,0,1,1,4,6 };
	std::cout << minDifference(nums);
}