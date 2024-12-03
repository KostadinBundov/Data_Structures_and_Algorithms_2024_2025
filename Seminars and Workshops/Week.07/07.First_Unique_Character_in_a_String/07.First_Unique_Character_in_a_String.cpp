#include <iostream>
#include <map>

int firstUniqChar(std::string s) {
    std::map<char, unsigned> map;

    for (auto symbol : s) {
        if (!map.count(symbol)) {
            map[symbol] = 1;
        }
        else {
            map[symbol] += 1;
        }
    }

    for (int i = 0; i < s.length(); i++) {
        if (map[s[i]] == 1) {
            return i;
        }
    }

    return -1;
}

int main() {
	std::string s = "loveleetcode";

	std::cout << firstUniqChar(s);
}