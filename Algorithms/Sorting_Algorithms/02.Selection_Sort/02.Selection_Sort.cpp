#include <iostream>

template<class T>
void selectionSort(T* arr, size_t size)
{
	for (int i = 0; i < size - 1; i++)
	{
		unsigned minElementIndex = i;

		for (int j = i + 1; j < size; j++)
		{
			if (arr[minElementIndex] > arr[j])
			{
				minElementIndex = j;
			}
		}

		if (minElementIndex != i)
		{
			std::swap(arr[i], arr[minElementIndex]);
		}
	}
}

int main()
{
	int arr[5]{ 5, 4, 3, 2, 1 };

	selectionSort<int>(arr, 5);

	for (int i = 0; i < 5; i++)
	{
		std::cout << arr[i] << " ";
	}

	return 0;
}