#include <iostream>

struct TreeNode {
	int val;
	TreeNode* left;
	TreeNode* right;

	TreeNode() : val(0), left(nullptr), right(nullptr) {}
	TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
	TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};

TreeNode* insertIntoBSTRec(TreeNode* root, int val) {
    if (!root) {
        return new TreeNode(val);
    }

    if (val < root->val) {
        root->left = insertIntoBSTRec(root->left, val);
    }
    else {
        root->right = insertIntoBSTRec(root->right, val);
    }

    return root;
}

TreeNode* insertIntoBST(TreeNode* root, int val) {
    if (!root) {
        return new TreeNode(val);
    }

    TreeNode* curr = root;

    while (true) {
        if (val < curr->val) {
            if (curr->left == nullptr) {
                curr->left = new TreeNode(val);
                break;
            }
            else {
                curr = curr->left;
            }
        }
        else {
            if (curr->right == nullptr) {
                curr->right = new TreeNode(val);
                break;
            }
            else {
                curr = curr->right;
            }
        }
    }

    return root;
}

int main() {

}