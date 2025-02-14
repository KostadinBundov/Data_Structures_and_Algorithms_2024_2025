#include <iostream>
#include <vector>

void heapify(std::vector<int>& arr, size_t size, int index) {
	int current = arr[index];

	while (true) {
		int left = 2 * index + 1;
		int right = 2 * index + 2;

		bool shouldGoLeft = left < size && arr[left] > current;
		bool shouldGoRight = right < size && arr[right] > current;

		if (shouldGoLeft && shouldGoRight) {
			if (arr[left] >= arr[right]) {
				std::swap(arr[left], arr[index]);
				index = left;
			}
			else {
				std::swap(arr[right], arr[index]);
				index = right;
			}
		}
		else if (shouldGoLeft) {
			std::swap(arr[left], arr[index]);
			index = left;
		}
		else if (shouldGoRight) {
			std::swap(arr[right], arr[index]);
			index = right;
		}
		else {
			break;
		}
	}
}

void heapSort(std::vector<int>& arr) {
	if (arr.size() <= 1) {
		return;
	}

	int size = arr.size();

	for (int i = size / 2 - 1; i >= 0; i--) {
		heapify(arr, size, i);
	}

	for (int i = size - 1; i >= 0; i--) {
		std::swap(arr[i], arr[0]);

		heapify(arr, i, 0);
	}
}

int main() {
	std::vector<int> arr = { 10, 9, 8, 7, 6, 5, 4, 3, 2 ,1 };
	heapSort(arr);
	for (int i = 0; i < arr.size(); i++) {
		std::cout << arr[i] << " ";
	}
}