#include <iostream>
#include <vector>
#include <unordered_map>

int findLHS(std::vector<int>& nums) {
	std::unordered_map<int, int> map;

	for (auto num : nums) {
		map[num] += 1;
	}

	int longestSequence = 0;

	for (auto& pair : map) {
		if (map.find(pair.first + 1) != map.end()) {
			longestSequence = std::max(longestSequence, pair.second + map[pair.first + 1]);
		}
	}

	return longestSequence;
}

int main() {
	std::vector<int> nums = { 1,3,2,2,5,2,3,7 };

	std::cout << findLHS(nums);
}