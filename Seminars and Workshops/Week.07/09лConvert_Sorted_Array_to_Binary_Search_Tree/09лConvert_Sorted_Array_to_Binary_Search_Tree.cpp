#include <iostream>
#include <vector>

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};

TreeNode* wrapper(std::vector<int> nums, int left, int right) {
    if (left > right) {
        return nullptr;
    }

    int mid = (left + right) / 2;

    TreeNode* root = new TreeNode(nums[mid]);
    root->left = wrapper(nums, left, mid - 1);
    root->right = wrapper(nums, mid + 1, right);

    return root;
}

TreeNode* sortedArrayToBST(std::vector<int>& nums) {
    return wrapper(nums, 0, nums.size() - 1);
}

int main() {

}