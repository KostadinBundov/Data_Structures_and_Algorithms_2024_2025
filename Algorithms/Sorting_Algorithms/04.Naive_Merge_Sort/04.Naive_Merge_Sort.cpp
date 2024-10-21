#include <iostream>

template<class T>
void merge(T* firstArr, size_t firstSize, T* secondArr, size_t secondSize) {
	T* resultArr = new T[firstSize + secondSize];

	int firstPointer = 0;
	int secondPointer = 0;
	int resultPointer = 0;

	while (firstPointer < firstSize && secondPointer < secondSize) {
		if (firstArr[firstPointer] < secondArr[secondPointer]) {
			resultArr[resultPointer++] = firstArr[firstPointer++];
		}
		else {
			resultArr[resultPointer++] = secondArr[secondPointer++];
		}
	}

	while (firstPointer < firstSize) {
		resultArr[resultPointer++] = firstArr[firstPointer++];
	}

	while (secondPointer < secondSize) {
		resultArr[resultPointer++] = secondArr[secondPointer++];
	}

	int resultSize = firstSize + secondSize;

	for (int i = 0; i < resultSize; i++) {
		firstArr[i] = resultArr[i];
	}

	delete[] resultArr;     
}

template<class T>
void mergeSort(T* arr, size_t size) {
	if (size <= 1) {
		return;
	}

	int middle = size / 2;

	mergeSort(arr, middle);
	mergeSort(arr + middle, size - middle);
	merge(arr, middle, arr + middle, size - middle);
}

int main() {
	int arr[5]{ 5, 4, 3, 2, 1 };

	mergeSort<int>(arr, 5);

	for (int i = 0; i < 5; i++)
	{
		std::cout << arr[i] << " ";
	}

	return 0;
}