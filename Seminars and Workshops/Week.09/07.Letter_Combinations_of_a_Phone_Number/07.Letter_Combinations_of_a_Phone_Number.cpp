#include <iostream>
#include <vector>
#include <unordered_map>

void generateCombinations(const std::string& digits, int index, std::string& dummy, std::unordered_map<char, std::vector<char>>& map, std::vector<std::string>& combs) {
	if (index >= digits.length()) {
		combs.push_back(dummy);
		return;
	}

	char digit = digits[index];
	std::vector<char> buttonLetters = map[digit];

	for (int i = 0; i < buttonLetters.size(); i++) {
		dummy.push_back(buttonLetters[i]);
		generateCombinations(digits, index + 1, dummy, map, combs);
		dummy.pop_back();
	}
}

std::vector<std::string> letterCombinations(std::string digits) {
	std::unordered_map<char, std::vector<char>> phone = {
		{'2', {'a', 'b', 'c'}},
		{'3', {'d', 'e', 'f'}},
		{'4', {'g', 'h', 'i'}},
		{'5', {'j', 'k', 'l'}},
		{'6', {'m', 'n', 'o'}},
		{'7', {'p', 'q', 'r', 's'}},
		{'8', {'t', 'u', 'v'}},
		{'9', {'w', 'x', 'y', 'z'}}
	};

	std::vector<std::string> possibleResultMessages;
	std::string dummy;

	if (digits.size() == 0) {
		return possibleResultMessages;
	}

	generateCombinations(digits, 0, dummy, phone, possibleResultMessages);

	return possibleResultMessages;
}

int main() {
	std::string input = "23";

	std::vector<std::string> res = letterCombinations(input);

	for (auto word : res) {
		std::cout << word << std::endl;
	}
}