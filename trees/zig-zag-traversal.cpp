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

vector<vector<int>> zVec;

void traverse(TreeNode *root, int level) {
    if (root == NULL) return;

    if (zVec.size() <= level) {
        zVec.push_back({});
    }

    zVec[level].push_back(root->value);
    traverse(root->left, level+1);
    traverse(root->right, level+1);
}

int main() {
    TreeNode *root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(5);

    root->right = new TreeNode(3);
    root->right->right = new TreeNode(6);

    traverse(root, 0);

    // Print the result in zig-zag fashion
    int pos = 0;
    for (vector<int> v : zVec) {
        int len = v.size();
        int i = pos == 0 ? 0 : len-1;
        while ((pos == 0 && i < len) || (pos == 1 && i >= 0))
        {
            cout << v[i] << " ";
            i = pos == 0 ? i+1 : i-1;
        }
        
        pos = (pos+1) % 2;
        cout << "\n";
    }

    return 0;
}