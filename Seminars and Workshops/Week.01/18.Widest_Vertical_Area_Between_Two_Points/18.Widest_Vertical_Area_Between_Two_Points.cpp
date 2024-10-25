#include <iostream>
#include <vector>
#include <algorithm>

bool predicate(const std::vector<int>& firstPoint, const std::vector<int>& secondPoint) {
	return firstPoint[0] < secondPoint[0];
}

int maxWidthOfVerticalArea(std::vector<std::vector<int>>& points) {
	std::sort(points.begin(), points.end(), predicate);
	int maxWidth = INT32_MIN;

	for (int i = 0; i < points.size() - 1; i++) {
		int currentWidth = points[i + 1][0] - points[i][0];

		if (currentWidth > maxWidth) {
			maxWidth = currentWidth;
		}
	}

	return maxWidth;
}

int main()
{
	std::vector<std::vector<int>> points = { {3, 1},{9, 0},{1, 0},{1, 4}, {5, 3}, {8, 8} };

	std::cout << maxWidthOfVerticalArea(points);
}