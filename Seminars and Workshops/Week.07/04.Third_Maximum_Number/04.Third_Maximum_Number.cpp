#include <iostream>
#include <vector>
#include <set>

int thirdMax(std::vector<int>& nums) {
	std::set<int> set;

	for (int i = 0; i < nums.size(); i++) {
		set.insert(nums[i]);
	}


	if (set.size() < 3) {
		return *set.rbegin();
	}

	auto it = set.rbegin();
	it++;
	it++;

	return *it;
}

int main() {

}