#include <iostream>
#include<vector>

template<class T>
int binarySearch(const T* arr, size_t size, const T& searched)
{
	if (size == 0)
	{
		return -1;
	}

	int middle = size / 2;

	if (arr[middle] == searched)
	{
		return middle;
	}
	else if (arr[middle] > searched)
	{
		return binarySearch(arr, middle, searched);
	}
	else
	{
		return binarySearch(arr + middle + 1, size - middle - 1, searched);
	}
}

template<class Iterator, class T>
Iterator binarySearch(Iterator start, Iterator end, const T& searched)
{
	if (start == end)
	{
		return end;
	}

	Iterator middle = start + std::distance(start, end) / 2;

	if (*middle == searched)
	{
		return middle;
	}
	else if (*middle > searched)
	{
		return binarySearch(start, middle, searched);
	}
	else
	{
		return binarySearch(middle + 1, end, searched);
	}
}

int main()
{
	std::vector<int> arr = { 1, 2, 3, 4, 5, 6, 7 };

	std::cout << binarySearch(arr.data(), arr.size(), 4) << std::endl;
	std::cout << std::distance(arr.begin(), binarySearch(arr.begin(), arr.end(), 4));
}