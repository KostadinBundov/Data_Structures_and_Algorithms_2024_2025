#include <iostream>
#include <vector>
#include <queue>

long long pickGifts(std::vector<int>& gifts, int k) {
	std::priority_queue<int> pq(gifts.begin(), gifts.end());

	for (int i = 0; i < k; i++) {
		int value = sqrt(pq.top());
		pq.pop();
		pq.push(value);
	}

	long long totalSum = 0;

	while (!pq.empty()) {
		totalSum += pq.top();
		pq.pop();
	}

	return totalSum;
}

int main() {
	std::vector<int> arr = { 25,64,9,4,100 };
	int k = 4;

	std::cout << pickGifts(arr, k);
}
