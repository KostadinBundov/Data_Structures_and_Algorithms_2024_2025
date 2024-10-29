#include <iostream>
#include <vector>

void countingSort(std::vector<int>& arr) {
    constexpr int LOWER_BOUND = -100;
    constexpr int UPPER_BOUND = 100;
    int size = UPPER_BOUND - LOWER_BOUND + 1;

    std::vector<int> counter(size, 0);

    for (int i = 0; i < arr.size(); i++) {
        int value = arr[i];
        counter[value - LOWER_BOUND]++;
    }

    for (int i = 1; i < counter.size(); i++)
    {
        counter[i] += counter[i - 1];
    }

    std::vector<int> result(arr.size(), 0);

    for (int i = arr.size() - 1; i >= 0; i--)
    {
        int index = counter[arr[i] - LOWER_BOUND] - 1;
        result[index] = arr[i];
        counter[arr[i] - LOWER_BOUND]--;
    }

    arr = result;
}

int main()
{
    std::vector<int> arr = { 55, -19, 27, 0, -100, 100, -35, 11 };
    countingSort(arr);

    for (int i = 0; i < arr.size(); i++) {
        std::cout << arr[i] << " ";
    }
}