#include <bits/stdc++.h>
using namespace std;

/**
 * Height (Left subtree) ~ Height (Right subtree) <= 1
*/

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

// Returns -1 if it is not balanced or the height instead
int findHeight(TreeNode *node) {
    if (node == NULL) return 0;

    int lh = findHeight(node->left);
    int rh = findHeight(node->right);

    if (lh == -1 || rh == -1) return -1;
    if (abs(lh - rh) > 1) return -1;

    return 1 + max(lh, rh);
}

int main() {
    TreeNode *root = new TreeNode(1);
    root->left = new TreeNode(2);

    root->right = new TreeNode(3);
    root->right->left = new TreeNode(4);
    root->right->right = new TreeNode(5);
    root->right->right->right = new TreeNode(6);

    int height = findHeight(root);
    cout << height << "\n";

    return 0;
}