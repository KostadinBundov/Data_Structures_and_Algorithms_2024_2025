#include <iostream>
#include <vector>
#include <unordered_set>

int getConsecutiveElements(std::unordered_set<int> set, int element, int count = 0) {
	for (auto& num : set) {
		if (set.find(num + 1) != set.end()) {
			int currCounter = getConsecutiveElements(set, num + 1, count + 1);
		}
	}
}

int longestConsecutive(std::vector<int>& nums) {
	std::unordered_set<int> set(nums.begin(), nums.end());

	for (auto& num : set) {
		
	}
}

int main() {
}