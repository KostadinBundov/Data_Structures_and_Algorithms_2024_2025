#include <iostream>
#include <vector>
#include <algorithm>

bool predicate(const std::vector<int>& a, const std::vector<int>& b) {
	return sqrt(a[0] * a[0] + a[1] * a[1]) < sqrt(b[0] * b[0] + b[1] * b[1]);
}

std::vector<std::vector<int>> kClosest(std::vector<std::vector<int>>& points, int k) {
	std::sort(points.begin(), points.end(), predicate);
	
	return std::vector<std::vector<int>>(points.begin(), points.begin() + k);
}

int main() {
	std::vector<std::vector<int>> points = { {1, 3}, {-2, 2} };
	int k = 1;

	std::vector<std::vector<int>> result = kClosest(points, k);

	for (auto point : result) {
		std::cout << "[" << point[0] << ", " << point[1] << "]\n";
	}

	return 0;
}