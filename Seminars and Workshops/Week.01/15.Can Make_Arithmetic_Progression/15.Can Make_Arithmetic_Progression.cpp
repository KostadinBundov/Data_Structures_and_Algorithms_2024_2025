#include <iostream>
#include <vector>
#include <algorithm>

bool canMakeArithmeticProgression(std::vector<int>& arr) {
	std::sort(arr.begin(), arr.end());

	int difference = arr[1] - arr[0];

	for (int i = 0; i < arr.size() - 1; i++)
	{
		if (arr[i + 1] - arr[i] != difference) {
			return false;
		}
	}

	return true;
}

int main()
{
	std::vector<int> arr = { 1,2,4 };
	std::cout << canMakeArithmeticProgression(arr);
}