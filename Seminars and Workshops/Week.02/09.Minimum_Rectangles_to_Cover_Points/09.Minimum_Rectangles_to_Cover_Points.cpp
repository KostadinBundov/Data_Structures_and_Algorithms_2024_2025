#include <iostream>
#include <vector>
#include <algorithm>

bool predicate(const std::vector<int>& firstPoint, const std::vector<int>& secondPoint) {
	return firstPoint[0] < secondPoint[0];
}

int minRectanglesToCoverPoints(std::vector<std::vector<int>>& points, int w) {
	std::sort(points.begin(), points.end(), predicate);
	int counter = 0;
	int rectangleWidth = 0;

	int rectangleX = points[0][0];

	for (int i = 1; i < points.size(); i++)
	{
		if (points[i][0] - rectangleX > w) {
			counter++;
			rectangleX = points[i][0];
		}
	}

	return counter + 1;
}

int main()
{
	std::vector<std::vector<int>> arr = { {2, 1}, {1, 0}, {1, 4}, {1, 8}, {3, 5}, {4, 6} };
	std::vector<std::vector<int>> arr2 = { {0, 0}, {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6} };
	std::cout << minRectanglesToCoverPoints(arr, 1) << std::endl;
	std::cout << minRectanglesToCoverPoints(arr2, 2) << std::endl;
}