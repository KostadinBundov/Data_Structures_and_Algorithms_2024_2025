#include <iostream>
#include <vector>
#include <cmath>

void putKTimes(std::vector<int>& result, int& index, int value, int times) {
    for (int i = 0; i < times; i++) {
        result[index++] = value;
    }
}

void rearrangeArray(std::vector<int>& arr) {
    constexpr int lowerBound = -100;
    constexpr int upperBound = 100;
    int size = upperBound - lowerBound + 1;

    std::vector<int> counter(size, 0);

    for (int i = 0; i < arr.size(); i++) {
        int value = arr[i];
        counter[value - lowerBound]++;
    }

    std::vector<int> result(arr.size(), 0);
    int index = 0;

    int secondSize = size / 2;

    for (int i = 0; i < secondSize; i++) {
        int positiveValue = i + 1;
        int negativeValue = -positiveValue; 

        int posCount = counter[positiveValue - lowerBound];
        int negCount = counter[negativeValue - lowerBound];

        if (negCount > 0) {
            putKTimes(result, index, negativeValue, negCount);
        }
        if (posCount > 0) {
            putKTimes(result, index, positiveValue, posCount);
        }
    }

    arr = result;
}

int main() {
    std::vector<int> arr = { -1, 5, 3, 100, 0, -3, -100, -5, 1 };

    rearrangeArray(arr);

    for (int i = 0; i < arr.size(); i++) {
        std::cout << arr[i] << " ";
    }
}
