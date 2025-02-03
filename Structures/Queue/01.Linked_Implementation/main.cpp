#include <iostream>
#include "LinkedQueue.hpp"

int main()
{
	LinkedQueue<int> q;

	q.push(1);
	q.push(2);
	q.push(3);
	q.push(4);
	q.push(5);

	std::cout << q.front() << std::endl;
	q.pop();
	std::cout << q.front() << std::endl;
	q.pop();
	std::cout << q.front() << std::endl;
	q.pop();
	std::cout << q.front() << std::endl;
	q.pop();
	std::cout << q.front() << std::endl;
	q.pop();

	std::cout << q.isEmpty() << std::endl;

	q.push(1);
	q.push(2);
	q.push(3);
	q.push(4);
	q.push(5);

	LinkedQueue<int> q2(q);
	std::cout << q.front() << std::endl;
	q.pop();
	std::cout << q.front() << std::endl;
	q.pop();
	std::cout << q.front() << std::endl;
	q.pop();
	std::cout << q.front() << std::endl;
	q.pop();
	std::cout << q.front() << std::endl;
	q.pop();
}