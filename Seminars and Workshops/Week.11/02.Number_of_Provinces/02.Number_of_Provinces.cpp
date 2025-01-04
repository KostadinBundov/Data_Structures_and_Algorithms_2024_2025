#include <iostream>
#include <vector>
#include <stack>

bool dfs(std::vector<std::vector<int>>& isConnected, std::vector<bool>& visited, int current) {
    if (visited[current]) {
        return false;
    }

    visited[current] = true;
    for (int i = 0; i < isConnected.size(); i++) {
        if (isConnected[current][i] == 1) {
            dfs(isConnected, visited, i);
        }
    }

    return true;
}

int findCircleNum(std::vector<std::vector<int>>& isConnected) {
	std::vector<std::vector<int>> arr(isConnected.size());

    for (int i = 0; i < isConnected.size(); i++) {
        for (int j = 0; j < isConnected[i].size(); j++) {
			if (i != j && isConnected[i][j] == 1) {
				arr[i].push_back(j);
		    }
        }
    }

	std::vector<bool> visited(arr.size(), false);

    int provincesCount = 0;
    for (int i = 0; i < isConnected.size(); i++) {
        if (dfs(isConnected, visited, i)) {
            provincesCount++;
        }
    }

    return provincesCount;
}

int main() {
	std::vector<std::vector<int>> arr = {
		{1, 1, 0},
		{1, 1, 0},
		{0, 0, 1}
	};

	std::cout << findCircleNum(arr);
}