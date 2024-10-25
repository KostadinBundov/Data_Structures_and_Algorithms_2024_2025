#include <iostream>
#include <vector>
#include <algorithm>

bool sortPredicate(const std::vector<int>& a, const std::vector<int>& b) {
	return a[1] > b[1];
}

int maximumUnits(std::vector<std::vector<int>>& boxTypes, int truckSize) {
	std::sort(boxTypes.begin(), boxTypes.end(), sortPredicate);

	int unitsCount = 0;
	int index = 0;

	while (truckSize != 0 && index < boxTypes.size()) {
		int boxesCount = std::min(boxTypes[index][0], truckSize);

		unitsCount += boxesCount * boxTypes[index][1];

		index++;
		truckSize -= boxesCount;
	}

	return unitsCount;
}

int main()
{
	//std::vector<std::vector<int>> arr = { {1, 3},{2, 2},{3, 1} };
	std::vector<std::vector<int>> arr = { {5,10},{2,5},{4,7},{3,9} }; 
	std::cout << maximumUnits(arr, 10);
}