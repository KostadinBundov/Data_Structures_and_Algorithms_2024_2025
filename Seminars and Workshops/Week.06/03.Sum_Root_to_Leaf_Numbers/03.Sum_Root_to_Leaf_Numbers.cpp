#include <iostream>
#include <vector>
#include <queue>

struct TreeNode {
	int val;
	TreeNode* left;
	TreeNode* right;
	TreeNode() : val(0), left(nullptr), right(nullptr) {}
	TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
	TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};

int sumNumbers(TreeNode* root, int currentNumber = 0) {
	if (!root) {
		return 0;
	}

	(currentNumber *= 10) += root->val;

	if (!root->left && !root->right) {
		return currentNumber;
	}

	int leftSum = sumNumbers(root->left, currentNumber);
	int rightSum = sumNumbers(root->right, currentNumber);

	return leftSum + rightSum;
}

void free(TreeNode* root) {
	if (!root) {
		return;
	}

	free(root->left);
	free(root->right);
	delete root;
}

TreeNode* convertToTree(const std::vector<int>& arr, int index) {
	if (index >= arr.size()) {
		return nullptr;
	}

	TreeNode* root = new TreeNode(arr[index]);
	root->left = convertToTree(arr, 2 * index + 1);
	root->right = convertToTree(arr, 2 * index + 2);

	return root;
}

int main() {
	std::vector<int> arr = { 4,9,0,5,1 };
	TreeNode* root = convertToTree(arr, 0);
	std::cout << sumNumbers(root);
	free(root);
}