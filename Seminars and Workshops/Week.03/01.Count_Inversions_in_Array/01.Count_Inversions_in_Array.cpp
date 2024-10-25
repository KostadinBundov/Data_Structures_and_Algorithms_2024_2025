#include <iostream>
#include <vector>

unsigned getInversionsCount(const std::vector<int>& arr) {
	unsigned counter = 0;

	for (int i = 0; i < arr.size() - 1; i++) {
		for (int j = i + 1; j < arr.size(); j++) {
			if (arr[i] > arr[j]) {
				counter++;
			}
		}
	}

	return counter;
}

int main() {
	std::vector<int> arr = { 2, 4, 1, 3, 5 };
	std::cout << getInversionsCount(arr);
}