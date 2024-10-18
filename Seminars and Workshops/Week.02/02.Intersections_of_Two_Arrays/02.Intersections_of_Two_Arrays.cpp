#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
    sort(nums1.begin(), nums1.end());
    sort(nums2.begin(), nums2.end());

    vector<int> result;

    for (int i = 0; i < nums1.size(); i++) {
        auto it = find(nums2.begin(), nums2.end(), nums1[i]);

        if (it != nums2.end() && count(result.begin(), result.end(), *it) == 0) {
            result.push_back(*it);
        }
    }

    return result;
}

void printArr(const vector<int>& arr) {
    for (int i = 0; i < arr.size(); i++) {
        cout << arr[i] << " ";
    }

    cout << endl;
}

int main() {
    vector<int> firstArr = { 2, 4, 2, 2 };
    vector<int> secondArr = { 5, 6, 2, 1, 4 };

    vector<int> intersectionArr = intersection(firstArr, secondArr);
    printArr(intersectionArr);
}