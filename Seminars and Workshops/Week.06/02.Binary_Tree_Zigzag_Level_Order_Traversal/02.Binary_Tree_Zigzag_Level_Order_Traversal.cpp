#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

struct TreeNode {
	int val;
	TreeNode* left;
	TreeNode* right;
	TreeNode() : val(0), left(nullptr), right(nullptr) {}
	TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
	TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};

std::vector<std::vector<int>> zigzagLevelOrder(TreeNode* root) {
	std::vector<std::vector<int>> result;
	if (!root) {
		return result;
	}

	std::queue<TreeNode*> queue;
	queue.push(root);
	bool level = true;

	while (!queue.empty()) {
		int ElementsOnLevel = queue.size();
		std::vector<int> elements(queue.size());

		int currIndex = 0;
		for (int i = 0; i < ElementsOnLevel; i++) {
			TreeNode* curr = queue.front();
			queue.pop();

			if (level) {
				elements[i] = curr->val;
			}
			else {
				elements[ElementsOnLevel - i - 1] = curr->val;
			}

			if (curr->left) {
				queue.push(curr->left);
			}
			if (curr->right) {
				queue.push(curr->right);
			}
		}

		result.push_back(elements);
		level = !level;
	}

	return result;
}

int main() {
	
}
