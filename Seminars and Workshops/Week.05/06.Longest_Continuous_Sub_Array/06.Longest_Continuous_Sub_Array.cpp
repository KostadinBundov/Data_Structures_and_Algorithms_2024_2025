#include <iostream>
#include <vector>
#include <deque>
int longestSubarray(std::vector<int>&nums, int limit) {
	std::deque<int> maxElements;
	std::deque<int> minElements;

	int maxLength = 1;
	int startIndex = 0;

	for (int i = 0; i < nums.size(); i++) {
		while (!maxElements.empty() && maxElements.back() < nums[i]) {
			maxElements.pop_back();
		}

		maxElements.push_back(nums[i]);

		while (!minElements.empty() && minElements.back() > nums[i]) {
			minElements.pop_back();
		}

		minElements.push_back(nums[i]);

		if (abs(maxElements.front() - minElements.front()) > limit) {
			if (maxElements.front() == nums[startIndex]) {
				maxElements.pop_front();
			}
			
			if (minElements.front() == nums[startIndex]) {
				minElements.pop_front();
			}

			startIndex++;
		}

		maxLength = std::max(maxLength, i - startIndex + 1);
	}

	return maxLength;
}

int main() {
	std::vector<int> nums = { 8, 2, 4, 7 };
	int limit = 5;
	std::cout << longestSubarray(nums, limit);
}