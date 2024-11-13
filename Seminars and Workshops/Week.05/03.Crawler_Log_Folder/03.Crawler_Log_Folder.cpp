#include <iostream>
#include <vector>
#include <stack>

int minOperations(std::vector<std::string>& logs) {
	std::stack<std::string> path;
	path.push("main");

	for (auto log : logs) {
		if (!log.compare("../")) {
			if (path.size() != 1) {
				path.pop();
			}
		}
		else if (!log.compare("./")) {
			continue;
		}
		else {
			path.push(log);
		}
	}

	return path.size() - 1;
}

int main() {
	std::vector<std::string> args = { "./","../","./" };
	std::cout << minOperations(args);
}