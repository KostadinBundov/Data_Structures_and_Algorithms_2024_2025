#include <iostream>

template<class T>
void bubbleSort(T* arr, size_t size)
{
	unsigned end = size - 1;

	for (int i = 0; i < size; i++)
	{
		unsigned lastSwappedIndex = i;

		for (int j = 0; j < end; j++)
		{
			if (arr[j] > arr[j + 1])
			{
				std::swap(arr[j], arr[j + 1]);
				lastSwappedIndex = j;
			}
		}

		end = lastSwappedIndex;

		if (lastSwappedIndex == i)
		{
			return;
		}
	}
}

int main()
{
	int arr[5]{5, 4, 3, 2, 1};

	bubbleSort<int>(arr, 5);

	for (int i = 0; i < 5; i++)
	{
		std::cout << arr[i] << " ";
	}

	return 0;
}
