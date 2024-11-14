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

void getLeafs(TreeNode* root, std::vector<int>& leafs) {
	if (!root) {
		return;
	}

	if (!root->left && !root->right) {
		leafs.push_back(root->val);
	}
	
	getLeafs(root->left, leafs);
	getLeafs(root->right, leafs);
}

bool leafSimilar(TreeNode* root1, TreeNode* root2) {
	std::vector<int> leafs1;
	std::vector<int> leafs2;

	getLeafs(root1, leafs1);
	getLeafs(root2, leafs2);


	return leafs1 == leafs2;
}

int main() {

}