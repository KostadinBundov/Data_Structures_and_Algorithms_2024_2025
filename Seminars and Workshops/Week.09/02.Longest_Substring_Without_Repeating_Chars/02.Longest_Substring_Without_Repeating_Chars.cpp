#include <iostream>
#include <vector>
#include <unordered_set>
#include <algorithm>

int lengthOfLongestSubstring(std::string s) {
	std::unordered_set<char> substr;
	size_t maxLength = 0;
	int beginCharacterIndex = 0;
	int index = 0;

	while (index < s.size()) {
		if (substr.find(s[index]) == substr.end()) {
			substr.insert(s[index++]);
		}
		else {
			if (maxLength < substr.size()) {
				maxLength = substr.size();
			}

			substr.erase(s[beginCharacterIndex]);
			beginCharacterIndex++;
		}
	}

	return std::max(substr.size(), maxLength);
}

int main() {
	std::string a = "pwwkew";
	std::cout << lengthOfLongestSubstring(a);
}