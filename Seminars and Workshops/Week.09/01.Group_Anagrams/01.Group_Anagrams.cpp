#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

std::vector<std::vector<std::string>> groupAnagrams(std::vector<std::string>& strs) {
	std::unordered_map<std::string, std::vector<std::string>> map;

	for (auto str : strs) {
		std::string copyStr = str;
		std::sort(copyStr.begin(), copyStr.end());
		map[copyStr].push_back(str);
	}

	std::vector<std::vector<std::string>> anagrams;

	for (auto& pair : map) {
		anagrams.push_back(pair.second);
	}

	return anagrams;
}

int main() {
	std::vector<std::string> arr = { "eat","tea","tan","ate","nat","bat" };
	auto anagrams = groupAnagrams(arr);

	for (auto& curr : anagrams) {
		std::cout << '[';

		for (auto& anagram : curr) {
			std::cout << anagram << " ";
		}

		std::cout << ']' << std::endl;
	}
}