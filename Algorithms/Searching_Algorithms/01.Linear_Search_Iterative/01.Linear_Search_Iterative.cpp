#include <iostream>

template<class T>
int linearSearch(const T* arr, size_t size, const T& searched)
{
	for (int i = 0; i < size; i++)
	{
		if (arr[i] == searched)
		{
			return i;
		}
	}

	return -1;
}

template<class Iterator, class T>
Iterator linearSearch(Iterator begin, Iterator end, const T& searched)
{
	for (Iterator i = begin; i != end; i++)
	{
		if (*i == searched)
		{
			return i;
		}
	}

	return end;
}

int main()
{
	int arr[7]{ 1, 2, 3, 4, 5, 6, 7 };

	std::cout << linearSearch<int>(arr, 7, 5) << std::endl;
	std::cout << linearSearch<int*, int>(arr, arr + 7, 5);
}