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



std::pair<int, int> getNodesCount(TreeNode* root, int& count) {
	if (root == NULL) {
		return { 0, 0 };
	}

	std::pair<int, int> left = getNodesCount(root->left, count);
	std::pair<int, int> right = getNodesCount(root->right, count);

	int sum = left.first + right.first + root->val;
	int size = left.second + right.second + 1;

	if (root->val == sum / size) {
		count++;
	}

	return { sum, size };
}

int averageOfSubtree(TreeNode* root) {
	int count = 0;
	std::pair<int, int> res = getNodesCount(root, count);
	return count;
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

int main() {
	std::vector<int> arr = { 4,8,5,0,1,-1,6 };
	TreeNode* root = convertToTree(arr, 0);
	std::cout << averageOfSubtree(root);
	free(root);
}