#include <iostream>
#include <vector>
#include <algorithm>

void fillMap(std::string& str, std::vector<std::pair<char, int>>& map) {
	for (int i = 0; i < str.size(); i++) {
		auto it = std::find_if(map.begin(), map.end(), [c = str[i]](const std::pair<char, int>& p) {return p.first == c; });

		if (it == map.end()) {
			map.push_back({ str[i], 1});
		}
		else {
			(*it).second += 1;
		}
	}

	std::sort(map.begin(), map.end(), [](std::pair<char, int>& a, std::pair<char, int>& b) {return a.second > b.second; });
}

int minimumPushes(std::string word) {
	std::vector<std::pair<char, int>> map;
	fillMap(word, map);

	unsigned pushesCount = 0;

	for (int i = 0; i < map.size(); i++) {
		if (i < 8) {
			pushesCount += map[i].second;
		}
		else if (i < 16) {
			pushesCount += map[i].second * 2;
		}
		else if (i < 24) {
			pushesCount += map[i].second * 3;

		}
		else {
			pushesCount += map[i].second * 4;
		}
	}

	return pushesCount;
}

// no need to use pairs as it's known that there are 26 letters in total
int minimumPushesSimpleVersion(std::string word) {
	std::vector<int> map(26, 0);

	for (int i = 0; i < word.size(); i++) {
		map[word[i] - 'a']++;
	}

	std::sort(map.begin(), map.end(), [](int a, int b) {return a > b; });

	unsigned pushesCount = 0;

	for (int i = 0; i < map.size(); i++) {
		if (i < 8) {
			pushesCount += map[i];
		}
		else if (i < 16) {
			pushesCount += map[i] * 2;
		}
		else if (i < 24) {
			pushesCount += map[i] * 3;

		}
		else {
			pushesCount += map[i] * 4;
		}
	}

	return pushesCount;
}

int main() {
	std::string word = "abcde";
	std::string word2 = "aabbccddeeffgghhiiiiii";

	std::cout << minimumPushesSimpleVersion(word) << std::endl;
	std::cout << minimumPushesSimpleVersion(word2) << std::endl;
}