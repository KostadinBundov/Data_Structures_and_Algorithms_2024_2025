#include <iostream>
#include <vector>

int findJudge(int n, std::vector<std::vector<int>>& trust) {
    if (trust.size() == 0 && n == 1) {
        return 1;
    }

    if (trust.size() == 1) {
        if (trust[0].size() == 1) {
            return trust[0][0];
        }
    }

    std::vector<int> incomming(n, 0);
    std::vector<int> outcomming(n, 0);

    for (int i = 0; i < trust.size(); i++) {
        int person = trust[i][0];
        int trusted = trust[i][1];

        incomming[trusted - 1]++;
        outcomming[person - 1]++;
    }

    for (int i = 0; i < incomming.size(); i++) {
        if (outcomming[i] == 0 && incomming[i] == n - 1) {
            return i + 1;
        }
    }

    return -1;
}

int main() {
	std::vector<std::vector<int>> trusts;
	std::cout << findJudge(1, trusts);
}