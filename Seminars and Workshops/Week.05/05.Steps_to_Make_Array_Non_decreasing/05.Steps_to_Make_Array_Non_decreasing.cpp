#include <iostream>
#include <vector>
#include <stack>

int totalSteps(std::vector<int>& nums) {
	int totalSteps = 0;
	std::stack<std::pair<int, int>> nonDecreasingArr;
	nonDecreasingArr.push({ nums[nums.size() - 1], 0 });

	for (int i = nums.size() - 2; i >= 0; --i) {
		int currentSteps = 0;

		while (!nonDecreasingArr.empty() && nonDecreasingArr.top().first < nums[i]) {

			if (currentSteps >= nonDecreasingArr.top().second) {
				currentSteps++;
			}
			else {
				currentSteps = nonDecreasingArr.top().second;
			}

			nonDecreasingArr.pop();
		}

		totalSteps = std::max(totalSteps, currentSteps);
		nonDecreasingArr.push({ nums[i], currentSteps });
	}

	return totalSteps;
}

int main() {
	std::vector<int> arr = { 5,3,4,4,7,3,6,11,8,5,11 };
	std::cout << totalSteps(arr);
}