#include <iostream>
#include <vector>
#include <unordered_set>



bool buddyStrings(std::string s, std::string goal) {
	if (s.size() != goal.size()) {
		return false;
	}

	if (s == goal) {
		std::unordered_set<char> set(s.begin(), s.end());
		return set.size() < s.size();
	}

	std::vector<int> indeces;

	for (int i = 0; i < s.size(); i++) {
		if (s[i] != goal[i]) {
			indeces.push_back(i);
		}
	}

	if (indeces.size() == 2) {
		int firstIndex = indeces[0];
		int secondIndex = indeces[1];

		return s[firstIndex] == goal[secondIndex] && s[secondIndex] == goal[firstIndex];
	}

	return false;
}

int main() {

}