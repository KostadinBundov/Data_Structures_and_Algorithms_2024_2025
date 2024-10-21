#include <iostream>

template<class T>
void merge(T* firstArr, size_t firstSize, T* secondArr, size_t secondSize, T* buffer) {
	int bufferPointer = 0;
	int secondPointer = 0;
	int resultPointer = 0;

	while (bufferPointer < firstSize && secondPointer < secondSize) {
		if (firstArr[bufferPointer] < secondArr[secondPointer]) {
			buffer[resultPointer++] = firstArr[bufferPointer++];
		}
		else {
			buffer[resultPointer++] = secondArr[secondPointer++];
		}
	}

	while (bufferPointer < firstSize) {
		buffer[resultPointer++] = firstArr[bufferPointer++];
	}

	while (secondPointer < secondSize) {
		buffer[resultPointer++] = secondArr[secondPointer++];
	}
}

template<class T>
void mergeSortWrapped(T* arr, size_t size, T* buffer) {
	if (size <= 1) {
		return;
	}

	int middle = size / 2;

	mergeSortWrapped(arr, middle, buffer);
	mergeSortWrapped(arr + middle, size - middle, buffer);
	merge(arr, middle, arr + middle, size - middle, buffer);

	for (int i = 0; i < size; i++) {
		arr[i] = buffer[i];
	}
}

template<class T>
void mergeSort(T* arr, size_t size) {
	T* buffer = new T[size];
	mergeSortWrapped(arr, size, buffer);
	delete[] buffer;
}

int main()
{
	int arr[5]{ 5, 4, 3, 2, 1 };

	mergeSort<int>(arr, 5);

	for (int i = 0; i < 5; i++)
	{
		std::cout << arr[i] << " ";
	}

	return 0;
}