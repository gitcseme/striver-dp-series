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

int maxi = 0;

int findHeight(TreeNode *root) {
    if (root == NULL) return 0;

    int lh = findHeight(root->left);
    int rh = findHeight(root->right);

    maxi = max(maxi, lh+rh);

    return 1 + max(lh, rh);
}

int main() {
    TreeNode *root = new TreeNode(1);
    root->left = new TreeNode(2);

    root->right = new TreeNode(3);
    root->right->left = new TreeNode(4);
    root->right->left->left = new TreeNode(5);
    root->right->left->left->left = new TreeNode(9);

    root->right->right = new TreeNode(6);
    root->right->right->right = new TreeNode(7);
    root->right->right->right->right = new TreeNode(8);

    int height = findHeight(root);
    cout << "Height: " << height << "\nDiameter: " << maxi << "\n";

    return 0;
}