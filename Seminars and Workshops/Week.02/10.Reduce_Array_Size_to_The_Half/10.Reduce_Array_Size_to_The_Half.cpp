#include <iostream>
#include <vector>
#include <algorithm>

int minSetSize(std::vector<int>& arr) {
	int maxElement = *std::max_element(arr.begin(), arr.end());
	std::vector<int> pairs(maxElement + 1, 0);

	for (int i = 0; i < arr.size(); i++) {
		pairs[arr[i]]++;
	}

	std::sort(pairs.begin(), pairs.end(), [](int a, int b) {return a > b; });

	int currentSize = arr.size();
	int halfSize = arr.size() / 2;
	int index = 0;
	int removedUniqueElementsCount = 0;

	while (currentSize > halfSize) {
		currentSize -= pairs[index++];
		removedUniqueElementsCount++;
	}

	return removedUniqueElementsCount;
}

int main()
{
	std::vector<int> arr = { 7,7,7,7,7,7 };
	std::cout << minSetSize(arr);
}