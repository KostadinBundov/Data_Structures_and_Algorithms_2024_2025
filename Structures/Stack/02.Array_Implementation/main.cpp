#include <iostream>
#include "ArrayStack.hpp"
#include <stack>

int main()
{

	ArrayStack<int> arrStack;
	arrStack.push(3);
	arrStack.push(5);
	arrStack.push(7);
	std::cout << arrStack.getSize() << std::endl;
	std::cout << arrStack.top() << std::endl;
	arrStack.pop();
	std::cout << arrStack.top() << std::endl;

	ArrayStack<int> newArrStack = arrStack;
	std::cout << newArrStack.getSize() << std::endl;
}