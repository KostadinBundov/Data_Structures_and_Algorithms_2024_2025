#include <iostream>
#include <vector>

void sort(int* arr, size_t size) {
	for (int i = 0; i < size - 1; i++) {
		unsigned smallestElementIndex = i;

		for (int j = i + 1; j < size; j++) {
			if (arr[smallestElementIndex] > arr[j]) {
				smallestElementIndex = j;
			}
		}

		if (smallestElementIndex != i) {
			std::swap(arr[i], arr[smallestElementIndex]);
		}
	}
}

bool canBeEqual(std::vector<int>& target, std::vector<int>& arr) {

	sort(target.data(), target.size());
	sort(arr.data(), arr.size());

	for (int i = 0; i < target.size(); i++){
		if (target[i] != arr[i]){
			return false;
		}
	}

	return true;
}

int main(){

	std::vector<int> target = { 1, 2, 3, 4 };
	std::vector<int> arr = { 2, 4, 1, 3 };

	std::cout << canBeEqual(target, arr);
}