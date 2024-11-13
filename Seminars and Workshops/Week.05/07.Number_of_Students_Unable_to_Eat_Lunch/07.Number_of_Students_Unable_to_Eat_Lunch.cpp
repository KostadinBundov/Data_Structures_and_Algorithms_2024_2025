#include <iostream>
#include <vector>
#include <stack>
#include <queue>

void fillStack(std::stack<int>& stack, std::vector<int> elements) {
	for (int i = elements.size() - 1; i >= 0; i--) {
		stack.push(elements[i]);
	}
}

void fillQueue(std::queue<int>& queue, std::vector<int> elements) {
	for (int i = 0; i < elements.size(); i++) {
		queue.push(elements[i]);
	}
}

int countStudents(std::vector<int>& students, std::vector<int>& sandwiches) {
	if (students.size() == 0 || sandwiches.size() == 0) {
		return 0;
	}

	std::stack<int> stack;
	std::queue<int> queue;

	fillQueue(queue, students);
	fillStack(stack, sandwiches);

	int currentCycles = 0;

	while (!stack.empty() && !queue.empty() && currentCycles != stack.size()) {
		if (stack.top() != queue.front()) {
			int student = queue.front();
			queue.pop();
			queue.push(student);

			currentCycles++;
		}
		else {
			stack.pop();
			queue.pop();
			currentCycles = 0;
		}
	}

	return queue.size();
}

int main()
{
	std::vector<int> students = { 1,1,1,0,0,1 };
	std::vector<int> sandwitches = { 1,0,0,0,1,1 };
	std::cout << countStudents(students, sandwitches);
}