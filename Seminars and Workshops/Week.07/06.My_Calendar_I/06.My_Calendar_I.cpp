#include <iostream>
#include <map>

bool book(int startTime, int endTime) {
	std::map<int, int> map;

    for (const auto& event : map) {
        int currStart = event.first;
        int currEnd = event.second;

        if (startTime < currEnd && endTime > currStart) {
            return false;
        }
    }

    map[startTime] = endTime;
    return true;
}

int main() {

}