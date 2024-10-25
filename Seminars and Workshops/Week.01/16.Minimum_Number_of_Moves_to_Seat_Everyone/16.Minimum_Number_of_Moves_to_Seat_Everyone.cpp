#include <iostream>
#include <vector>
#include <algorithm>

int minMovesToSeat(std::vector<int>& seats, std::vector<int>& students) {
    std::sort(seats.begin(), seats.end());
    std::sort(students.begin(), students.end());

    int totalMoves = 0;

    for (int i = 0; i < seats.size(); i++) {
        totalMoves += abs(seats[i] - students[i]);
    }

    return totalMoves;
}

int main()
{
    std::vector<int> seats = { 3, 1, 5 };
    std::vector<int> students = { 2, 7, 4 };
    std::cout << minMovesToSeat(seats, students);
}