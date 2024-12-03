#include <iostream>
#include <vector>

int kthSmallest(std::vector<std::vector<int>>& matrix, int k) {
	int left = matrix[0][0];
	int right = matrix[matrix.size() - 1][matrix.size() - 1];

	while (left < right) {
		int middle = left + (right - left) / 2;

		int row = 0;
		int col = matrix.size() - 1;

		int smallerElementsCount = 0;

		while (row < matrix.size() && col >= 0) {
			if (matrix[row][col] <= middle) {
				smallerElementsCount += col + 1;
				row++;
			}
			else {
				col -= 1;
			}
		}

		if (smallerElementsCount < k) {
			left = middle + 1;
		}
		else {
			right = middle;
		}
	}

	return left;
}

int main() {
	std::vector<std::vector<int>> matrix(2);
	matrix[0] = { -5, -4 };
	matrix[1] = { -5, -4 };

	std::cout << kthSmallest(matrix, 2);
}