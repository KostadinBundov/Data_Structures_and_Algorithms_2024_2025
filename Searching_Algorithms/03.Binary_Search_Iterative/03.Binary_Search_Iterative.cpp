#include <iostream>
#include <vector>

template<class T>
int binarySearch(const T* arr, size_t size, const T& searched)
{
	int startIndex = 0;
	int endIndex = size - 1;

	while (endIndex >= startIndex)
	{
		//garantee we won't overflow the data type
		int middleIndex = startIndex + (endIndex - startIndex) / 2;

		if (arr[middleIndex] == searched)
		{
			return middleIndex;
		}
		else if (arr[middleIndex] > searched)
		{
			endIndex = middleIndex - 1;
		}
		else
		{
			startIndex = middleIndex + 1;
		}
	}

	return -1;
}

//the end Iterator points one position after the last element of the sequence
template <typename Iterator, typename T>
Iterator binarySearch(Iterator start, Iterator end, const T& value)
{
	Iterator left = start;
	Iterator right = end;

	while (left < right)
	{
		Iterator middle = left + std::distance(left, right) / 2;

		if (*middle == value)
		{
			return middle;
		}
		else if (*middle < value)
		{
			left = middle + 1;
		}
		else
		{
			right = middle;
		}
	}

	return end;
}


int main()
{
	std::vector<int> arr = { 1, 2, 3, 4, 5, 6, 7 };

	std::cout << binarySearch<int>(arr.data(), arr.size(), 4);
}