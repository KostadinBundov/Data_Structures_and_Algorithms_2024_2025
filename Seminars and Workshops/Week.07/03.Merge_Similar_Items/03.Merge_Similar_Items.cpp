#include <iostream>
#include <vector>
#include <map>

std::vector<std::vector<int>> mergeSimilarItems(std::vector<std::vector<int>>& items1, std::vector<std::vector<int>>& items2) {
	std::map<int, int> map;

	for (int i = 0; i < items1.size(); i++) {
		int key = items1[i][0];
		int value = items1[i][1];

		map[key] = value;
	}

	for (int i = 0; i < items2.size(); i++) {
		int key = items2[i][0];
		int value = items2[i][1];

		auto it = map.find(key);

		if (it != map.end()) {
			map[key] += value;
		}
		else {
			map[key] = value;
		}
	}

	std::vector<std::vector<int>> result;

	for (auto& pair : map) {
		result.push_back({ pair.first, pair.second });
	}

	return result;
}

int main() {

}