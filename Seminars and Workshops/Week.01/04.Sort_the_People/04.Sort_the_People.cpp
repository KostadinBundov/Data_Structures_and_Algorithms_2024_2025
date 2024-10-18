#include <iostream>
#include<vector>
#include <string>

using namespace std;

void sort(vector<int>& arr, vector<int>& indexes) {
	for (int i = 0; i < arr.size() - 1; i++) {
		unsigned smallestElementIndex = i;

		for (int j = i + 1; j < arr.size(); j++) {
			if (arr[indexes[smallestElementIndex]] < arr[indexes[j]]) {
				smallestElementIndex = j;
			}
		}

		if (smallestElementIndex != i) {
			std::swap(indexes[i], indexes[smallestElementIndex]);
		}
	}
}

vector<string> sortPeople(vector<string>& names, vector<int>& heights) {
	vector<int>indexes(heights.size());

	for (int i = 0; i < indexes.size(); i++){
		indexes[i] = i;
	}

	sort(heights, indexes);

	vector<string> sortedNames(names.size());

	for (int i = 0; i < sortedNames.size(); i++){
		sortedNames[i] = names[indexes[i]];
	}

	return sortedNames;
}

//vector<string> sortPeople(vector<string>& names, vector<int>& heights) {
//	for (int i = 0; i < names.size() - 1; i++) {
//		unsigned smallestElementIndex = i;
//
//		for (int j = i + 1; j < names.size(); j++) {
//			if (heights[smallestElementIndex] < heights[j]) {
//				smallestElementIndex = j;
//			}
//		}
//
//		if (smallestElementIndex != i) {
//			std::swap(heights[i], heights[smallestElementIndex]);
//			std::swap(names[i], names[smallestElementIndex]);
//		}
//	}
//
//	return names;
//}

int main()
{
	vector<string> names = { "Mary","John","Emma" };
	vector<int> heights = { 180, 165, 170 };

	vector<string> sortedNames = sortPeople(names, heights);

	for (int i = 0; i < sortedNames.size(); i++)
	{
		std::cout << sortedNames[i] << " ";
	}
}