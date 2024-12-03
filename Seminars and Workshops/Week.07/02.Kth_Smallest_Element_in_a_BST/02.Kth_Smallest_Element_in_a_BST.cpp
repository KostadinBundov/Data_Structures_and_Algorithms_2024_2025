#include <iostream>

struct TreeNode {
	int val;
	TreeNode* left;
	TreeNode* right;

	TreeNode() : val(0), left(nullptr), right(nullptr) {}
	TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
	TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};

int kthSmallest(TreeNode* root, int& k) {
	if (!root) {
		return 0;
	}

    int currVal = kthSmallest(root->left, k);

	if (k == 0) {
		return currVal;
	}

	k -= 1;
	if (k == 0) {
		return root->val;
	}

    return kthSmallest(root->right, k);
}

int main() {

}