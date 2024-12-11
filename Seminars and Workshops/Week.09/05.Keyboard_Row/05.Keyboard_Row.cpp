#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>

bool checkIfWordInRow(std::string word, std::unordered_set<char> row) {
    for (const auto& charecter : word) {
        if (row.find(charecter) == row.end()) {
            return false;
        }
    }

    return true;
}


std::vector<std::string> findWords(std::vector<std::string>& words) {
    std::string firstRowAsStirng = "qwertyuiop";
    std::string secondRowAsStirng = "asdfghjkl";
    std::string thirdRowAsStirng = "zxcvbnm";

    std::unordered_set<char> firstRow(firstRowAsStirng.begin(), firstRowAsStirng.end());
    std::unordered_set<char> secondRow(secondRowAsStirng.begin(), secondRowAsStirng.end());
    std::unordered_set<char> thirdRow(thirdRowAsStirng.begin(), thirdRowAsStirng.end());

    std::vector<std::string> result;

    for (auto word : words) {
        std::string copy = word;
        std::transform(word.begin(), word.end(), word.begin(), ::tolower);

        if (checkIfWordInRow(word, firstRow) || checkIfWordInRow(word, secondRow) || checkIfWordInRow(word, thirdRow)) {
            result.push_back(copy);
        } 
    }

    return result;
}

int main() {
    std::vector<std::string> arr = { "a","b" };
    std::vector<std::string> result = findWords(arr);

    for (auto var : result) {
        std::cout << var << " ";
    }
}