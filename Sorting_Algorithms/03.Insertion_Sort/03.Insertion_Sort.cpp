#include <iostream>

template<class T>
void insertionSort(T* arr, size_t size)
{
	for (int i = 1; i < size; i++)
	{
		T currentElement = arr[i];
		unsigned currentIndex = i;

		while (currentIndex > 0 && currentElement < arr[currentIndex - 1])
		{
			arr[currentIndex] = arr[currentIndex - 1];
			currentIndex--;
		}

		arr[currentIndex] = currentElement;
	}
}

int main()
{
	int arr[5]{ 5, 4, 3, 2, 1 };

	insertionSort<int>(arr, 5);

	for (int i = 0; i < 5; i++)
	{
		std::cout << arr[i] << " ";
	}

	return 0;
}