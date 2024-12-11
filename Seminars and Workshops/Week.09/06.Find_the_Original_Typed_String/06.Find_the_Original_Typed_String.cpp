#include <iostream>
#include <vector>

int possibleStringCount(std::string word) {
	int possibleStringsCount = 1;
	char previous = word[0];

	for (int i = 1; i < word.size(); i++) {
		if (word[i] == previous) {
			possibleStringsCount++;
		}
		else {
			previous = word[i];
		}
	}

	return possibleStringsCount;
}

int main() {
	std::string s = "ere";
	std::cout << possibleStringCount(s);
}