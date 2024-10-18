#include <iostream>
#include <vector>

using namespace std;

void sort(vector<pair<double, vector<int>>>& arr) {

	for (int i = 0; i < arr.size() - 1; i++) {
		unsigned smallestElementIndex = i;

		for (int j = i + 1; j < arr.size(); j++) {
			if (arr[smallestElementIndex].first > arr[j].first) {
				smallestElementIndex = j;
			}
		}

		if (smallestElementIndex != i) {
			std::swap(arr[i], arr[smallestElementIndex]);
		}
	}
}

vector<vector<int>> kClosest(vector<vector<int>>& points, int k) {

	vector<pair<double, vector<int>>> results(points.size());

	for (int i = 0; i < results.size(); i++)
	{
		results[i].first = sqrt(points[i][0] * points[i][0] + points[i][1] * points[i][1]);
		results[i].second = points[i];
	}

	sort(results);

	vector<vector<int>> finalResult(k);

	for (int i = 0; i < k; i++)
	{
		finalResult[i] = results[i].second;
	}

	return finalResult;
}

int main()
{
	vector<vector<int>> points = { {1, 3}, {-2, 2}};
	int k = 1;

	vector<vector<int>> result = kClosest(points, k);

	for (auto point : result) {
		cout << "[" << point[0] << ", " << point[1] << "]\n";
	}

	return 0;
}