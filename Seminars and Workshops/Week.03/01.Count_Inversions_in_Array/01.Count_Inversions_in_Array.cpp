#include <iostream>
#include <vector>

void merge(int* firstArr, size_t firstSize, int* secondArr, size_t secondSize, int* buffer, int& counter) {
    int firstIndex = 0;
    int secondIndex = 0;
    int resultIndex = 0;

    while (firstIndex < firstSize && secondIndex < secondSize) {
        if (firstArr[firstIndex] <= secondArr[secondIndex]) {
            buffer[resultIndex++] = firstArr[firstIndex++];
        }
        else {
            buffer[resultIndex++] = secondArr[secondIndex++];
            counter += (firstSize - firstIndex);
        }
    }

    while (firstIndex < firstSize) {
        buffer[resultIndex++] = firstArr[firstIndex++];
    }

    while (secondIndex < secondSize) {
        buffer[resultIndex++] = secondArr[secondIndex++];
    }
}

void mergeSortWrapped(int* arr, size_t size, int* buffer, int& counter) {
    if (size <= 1) {
        return;
    }

    int middle = size / 2;

    mergeSortWrapped(arr, middle, buffer, counter);
    mergeSortWrapped(arr + middle, size - middle, buffer + middle, counter);
    merge(arr, middle, arr + middle, size - middle, buffer, counter);

    for (int i = 0; i < size; i++) {
        arr[i] = buffer[i];
    }
}

int mergeSort(std::vector<int>& arr) {
    if (arr.size() == 0) {
        return 0;
    }

    std::vector<int> buffer(arr.size());
    int inversionsCount = 0;
    mergeSortWrapped(arr.data(), arr.size(), buffer.data(), inversionsCount);

    return inversionsCount;
}

int main() {
	std::vector<int> arr = {2, 4, 1, 3, 5};
	std::cout << mergeSort(arr);
}