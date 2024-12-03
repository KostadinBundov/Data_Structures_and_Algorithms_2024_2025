#include <iostream>

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};

int rangeSumBST(TreeNode* root, int low, int high) {
    if (!root) {
        return 0;
    }

    if (low <= root->val && root->val <= high) {
        return root->val + rangeSumBST(root->left, low, high) + rangeSumBST(root->right, low, high);
    }
    else {
        return rangeSumBST(root->left, low, high) + rangeSumBST(root->right, low, high);
    }
}

int main() {
    std::cout << "Hello World!\n";
}