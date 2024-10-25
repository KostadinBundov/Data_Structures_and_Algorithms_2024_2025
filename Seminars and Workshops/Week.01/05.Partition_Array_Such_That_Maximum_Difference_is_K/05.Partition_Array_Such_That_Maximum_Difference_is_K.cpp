#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int partitionArray(vector<int>& nums, int k) {
	sort(nums.begin(), nums.end());

	int partitionsCount = 1;
	int min = nums[0];

	for (int i = 0; i < nums.size(); i++) {

		if (nums[i] - min > k) {
			partitionsCount++;
			min = nums[i];
		}
	}

	return partitionsCount;
}

int main()
{
	vector<int> nums = { 2,2, 4, 5 };
	cout << partitionArray(nums, 0);
}