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

TreeNode* mergeTrees(TreeNode* root1, TreeNode* root2) {
	if (!root1) {
		return root2;
	}

	if (!root2) {
		return root1;
	}

	root1->val += root2->val;

	root1->left = mergeTrees(root1->left, root2->left);
	root1->right = mergeTrees(root1->right, root2->right);

	return root1;
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
	if (index >= arr.size() || arr[index] == -1) {
		return nullptr;
	}

	TreeNode* root = new TreeNode(arr[index]);
	root->left = convertToTree(arr, 2 * index + 1);
	root->right = convertToTree(arr, 2 * index + 2);

	return root;
}

void print(TreeNode* root) {
	if (!root) {
		return;
	}

	std::cout << root->val << " ";
	print(root->left);
	print(root->right);
}

int main() {
	std::vector<int> arr1 = { 1,3,2,5 };
	std::vector<int> arr2 = { 2,1,3,-1,4,-1,7 };
	TreeNode* root1 = convertToTree(arr1, 0);
	TreeNode* root2 = convertToTree(arr2, 0);
	root1 = mergeTrees(root1, root2);
	print(root1);
}