#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
    sort(nums1.begin(), nums1.end());
    sort(nums2.begin(), nums2.end());

    int index1 = 0;
    int index2 = 0;

    vector<int> result;

    for (int i = 0; i < nums1.size(); i++)
    {
        auto it = find(nums2.begin(), nums2.end(), nums1[i]);

        if (it != nums2.end() && count(result.begin(), result.end(), *it))
        {
            result.push_back(*it);
        }
    }

    return result;
}

int main()
{

}