#include <iostream>
#include "LinkedStack.hpp"

int main()
{
	LinkedStack<int> list;
	list.push(15);
	list.push(20);
	std::cout << list.top() << std::endl;
	list.pop();
	std::cout << list.isEmpty() << std::endl;
	std::cout << list.top() << std::endl;
	list.pop();

	list.push(100);
	list.push(101);
	list.push(102);

	LinkedStack<int> newList = list;
	std::cout << newList.top() << std::endl;
	std::cout << newList.getSize() << std::endl;

	return 0;
}