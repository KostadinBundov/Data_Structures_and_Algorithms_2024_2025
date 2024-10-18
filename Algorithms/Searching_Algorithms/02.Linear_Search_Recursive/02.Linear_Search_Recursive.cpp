#include <iostream>

template<class T>
bool linearSearch(const T* arr, size_t size, const T& searched)
{
	if (size == 0)
	{
		return false;
	}

	return *arr == searched || linearSearch(++arr, --size, searched);
}

template<class T>
int linearSearch(const T* arr, size_t size, const T& searched, unsigned currentIndex = 0)
{
	if (size == 0)
	{
		return -1;
	}

	if (*arr == searched)
	{
		return currentIndex;
	}

	return linearSearch(++arr, --size, searched, currentIndex + 1);
}

template<class Iterator, class T>
Iterator linearSearch(Iterator begin, Iterator end, const T& searched)
{
	if (begin == end)
	{
		return end;
	}

	if (*begin == searched)
	{
		return begin;
	}

	return linearSearch(++begin, end, searched);
}

int main()
{
	int arr[7]{ 1, 2, 3, 4, 5, 6, 7 };

	std::cout << linearSearch<int*, int>(arr, arr + 7, 5) << std::endl;
}