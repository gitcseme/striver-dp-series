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

int findMaxDepth(TreeNode *node) {
    if (node == NULL) return 0;

    int lh = findMaxDepth(node->left);
    int rh = findMaxDepth(node->right);

    return 1 + max(lh, rh);
}

int main() {
    TreeNode *root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    
    root->right->left = new TreeNode(4);
    root->right->left->left = new TreeNode(5);
    root->right->right = new TreeNode(6);

    int maxDepth = findMaxDepth(root);

    cout << "max depth: " << maxDepth << "\n";

    return 0;
}