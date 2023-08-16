#include <bits/stdc++.h>
using namespace std;

class TreeNode {
public:
    TreeNode(int v) {
        value = v;
        left = right = NULL;
    }

    TreeNode(int v, TreeNode *leftNode, TreeNode *rightNode) {
        value = v;
        left = leftNode;
        right = rightNode;
    }

    int value;
    TreeNode *left, *right;
};

int max_sum = 0;

int findMaxSum(TreeNode *root) {
    if (root == NULL) return 0;

    int mxLs = max(0, findMaxSum(root->left)); // ignore negative by comparing with 0.
    int mxRs = max(0, findMaxSum(root->right));
    
    max_sum = max(max_sum, root->value + mxLs + mxRs); // calculate max-sum from current node.
    
    return root->value + max(mxLs, mxRs);
}

int main() {
    TreeNode *root = new TreeNode(-10);
    root->left = new TreeNode(9);
    root->right = new TreeNode(20); 

    root->right->left = new TreeNode(15);
    root->right->right = new TreeNode(7);

    findMaxSum(root);
    cout << "Maximum path sum: " << max_sum << "\n";

    return 0;
}
