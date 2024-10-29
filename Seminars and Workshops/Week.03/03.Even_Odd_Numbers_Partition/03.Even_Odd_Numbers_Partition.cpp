#include <iostream>
#include <vector>
#include <algorithm>

bool isPrime(int num) {
	if (num <= 1) {
		return false;
	}

	int bound = sqrt(num);

	for (int i = 2; i <= bound; i++)
	{
		if (num % i == 0) {
			return false;
		}
	}

	return true;
}

int main()
{
	std::vector<int> arr = { 10, 3, 5, 9, 2, 8 };
	std::partition(arr.begin(), arr.end(), isPrime);

	for (int i = 0; i < arr.size(); i++) {
		std::cout << arr[i] << " ";
	}
}