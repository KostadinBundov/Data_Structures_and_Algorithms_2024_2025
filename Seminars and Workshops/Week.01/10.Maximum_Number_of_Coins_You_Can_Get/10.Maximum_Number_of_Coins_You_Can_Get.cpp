#include <iostream>
#include <vector>
#include <algorithm>

int maxCoins(std::vector<int>& piles) {

	std::sort(piles.begin(), piles.end());
	int sum = 0;

	for (int i = piles.size() / 3; i < piles.size(); i+= 2)
	{
		sum += piles[i];
	}

	return sum;
}

int main()
{

}