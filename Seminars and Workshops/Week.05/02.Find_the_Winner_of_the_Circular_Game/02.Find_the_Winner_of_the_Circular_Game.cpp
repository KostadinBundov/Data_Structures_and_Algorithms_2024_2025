#include <iostream>
#include <queue>

int findTheWinner(int n, int k) {
	std::queue<int> players;

	for (int i = 1; i <= n; i++) {
		players.push(i);
	}

	while (players.size() != 1) {
		for (int i = 1; i < k; i++) {
			players.push(players.front());
			players.pop();
		}

		players.pop();
	}

	return players.front();
}

int main() {

}