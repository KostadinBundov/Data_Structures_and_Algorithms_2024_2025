#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int maxScore(vector<int>& nums) {

    sort(nums.begin(), nums.end(), greater<int>());

    int currentSum = 0;
    int count = 0;

    for (int i = 0; i < nums.size(); i++) {
        currentSum += nums[i];

        if (currentSum >= 0) {
            count++;
        }
    }

    return count;
}

int main() {
    vector<int> nums{ 2, -1, 0, 1, -3, 3, -3 };
    cout << maxScore(nums);
}
