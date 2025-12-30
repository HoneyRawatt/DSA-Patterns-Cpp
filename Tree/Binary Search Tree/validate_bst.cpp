#include <iostream>
#include <climits> // for LONG_MIN, LONG_MAX
using namespace std;

/*
Class: TreeNode
Purpose: Represents a node in a binary search tree (BST)
*/
class TreeNode {
public:
    int val;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int val) {
        this->val = val;
        left = nullptr;
        right = nullptr;
    }
};

// Helper function: checks if a subtree is a valid BST within given min/max bounds
bool isValidBST(TreeNode* root, long minval, long maxval) {
    if (!root) return true;

    if (root->val <= minval || root->val >= maxval)
        return false;

    return isValidBST(root->left, minval, root->val) &&
           isValidBST(root->right, root->val, maxval);
}

// Main function: starts with full range of possible values
bool isValidBST(TreeNode* root) {
    return isValidBST(root, LONG_MIN, LONG_MAX);
}

// Example usage
int main() {
    TreeNode* root = new TreeNode(2);
    root->left = new TreeNode(1);
    root->right = new TreeNode(3);

    if (isvalidbst(root))
        cout << "Valid BST\n";
    else
        cout << "Not a valid BST\n";

    return 0;
}

// 🧠 Explanation

// Each node must satisfy:
// minval < node->val < maxval

// For left subtree:

// maxval becomes the current node’s value.

// For right subtree:

// minval becomes the current node’s value.

// ⚙️ Complexity

// Time Complexity: O(n) — each node visited once.

// Space Complexity: O(h) — recursion stack, where h is tree height (O(log n) for balanced BST).