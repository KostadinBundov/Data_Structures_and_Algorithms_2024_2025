#include <iostream>
#include <vector>
#include <algorithm>

long long largestPerimeter(std::vector<int>& nums) {

	if (nums.size() < 3) {
		return -1;
	}

	std::sort(nums.begin(), nums.end());
	long long totalSum = 0;

	for (const auto& it : nums) {
		totalSum += it;
	}

	bool isPolygonFormed = false;

	for (int i = nums.size() - 1; i >= 2; i--) {
		if (totalSum - nums[i] > nums[i]) {
			return totalSum;
		}
		else {
			totalSum -= nums[i];
		}
	}

	return -1;
}

int main() {
	std::vector<int> nums1 = { 5, 5, 5 };
	std::vector<int> nums2 = { 1, 12, 1, 2, 5, 50, 3 };
	std::vector<int> nums3 = { 5, 5, 50 };

	std::cout << largestPerimeter(nums1);
}