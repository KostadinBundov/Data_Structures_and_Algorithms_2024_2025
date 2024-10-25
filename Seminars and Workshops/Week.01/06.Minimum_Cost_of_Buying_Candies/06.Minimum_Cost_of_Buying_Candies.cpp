#include <iostream>
#include <vector>
#include <algorithm>

int minimumCost(std::vector<int>& cost) {
	std::sort(cost.begin(), cost.end());

	int minimumCost = 0;

	if (cost.size() == 1) {
		return cost[0];
	}

	for (int i = cost.size() - 1; i >= 0; i -= 3) {
		if (i == 0) {
			minimumCost += cost[i];
		}
		else {
			minimumCost += cost[i] + cost[i - 1];
		}
	}

	return minimumCost;
}

int main()
{
	std::vector<int> arr = { 1, 2, 3, 4, 5 };
	std::cout << minimumCost(arr) << std::endl;
}