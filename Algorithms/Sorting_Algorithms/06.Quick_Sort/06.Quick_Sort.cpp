#include <iostream>

int partition(int* arr, size_t size) {
	int pivot = arr[size / 2];

	int start = 0;
	int end = size - 1;

	while (true) {
		while (arr[start] < pivot) {
			start++;
		}

		while (arr[end] > pivot) {
			end--;
		}

		if (arr[start] == arr[end]) {
			start++;
		}

		if (start < end) {
			std::swap(arr[start], arr[end]);
		}
		else
		{
			return end;
		}
	}
}

int secondPartition(int* arr, size_t size) {
	if (arr[0] > arr[size - 1]) {
		std::swap(arr[0], arr[size - 1]);
	}

	int pivot = arr[size - 1];
	int left = 0;
	int right = size - 1;

	while (true) {
		while (arr[left] < pivot) {
			left++;
		}

		while (arr[right] > pivot) {
			right--;

			if (left == right) {
				break;
			}
		}

		if (left >= right) {
			break;
		}

		if (arr[left] == arr[right]) {
			left++;
		}
		else {
			std::swap(arr[left], arr[right]);
		}

	}

	std::swap(arr[left], pivot);
	return left;
}

void quickSort(int* arr, size_t size) {
	if (size <= 1) {
		return;
	}

	int pivotIndex = secondPartition(arr, size);
	quickSort(arr, pivotIndex);
	quickSort(arr + pivotIndex, size - pivotIndex);
}

int main()
{
	int arr[6]{ 2, 1, 3, 4, 3, 5 };

	quickSort(arr, 6);
	for (int i = 0; i < 6; i++)
	{
		std::cout << arr[i] << " ";
	}

	return 0;
}