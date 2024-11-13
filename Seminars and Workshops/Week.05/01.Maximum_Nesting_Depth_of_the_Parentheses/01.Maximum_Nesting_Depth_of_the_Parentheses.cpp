#include <iostream>
#include <stack>

int maxDepth(std::string s) {
    std::stack<char> brackets;
    int maxCount = 0;

    for (char ch : s) {
        switch (ch) {
        case '(':
            brackets.push(ch);
            break;

        case ')':
            if (maxCount < brackets.size()) {
                maxCount = brackets.size();
            }

            brackets.pop();

            break;
        default:
            break;
        }
    }

    return maxCount;
}

int main() {
    std::cout << "Hello World!\n";
}