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

bool isSameTree(TreeNode* p, TreeNode* q) {
    if (p == NULL && q == NULL) return true;
    if (p == NULL || q == NULL) return false;
    if (p->value != q->value) return false;
    
    return isSameTree(p->left, q->left) && isSameTree(p->right, q->right);
}

int main() {
    TreeNode *root1 = new TreeNode(1);
    root1->left = new TreeNode(2);
    root1->right = new TreeNode(3);
    root1->right->left = new TreeNode(4);
    root1->right->right = new TreeNode(5);

    TreeNode *root2 = new TreeNode(1);
    root2->left = new TreeNode(2);
    root2->right = new TreeNode(3);
    root2->right->left = new TreeNode(4);
    root2->right->right = new TreeNode(5);

    bool result = isSameTree(root1, root2);
    cout << "Is identical: " << result << "\n";

    return 0;
}