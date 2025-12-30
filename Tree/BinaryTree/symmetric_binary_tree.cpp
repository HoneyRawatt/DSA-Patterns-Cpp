#include <iostream>
#include <vector>
using namespace std;

/*
Class: TreeNode
Purpose: Represents a node in a binary tree
*/
class TreeNode {
public:
    int data;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int data) {
        this->data = data;
        left = nullptr;
        right = nullptr;
    }
};

// Helper function to check if two subtrees are mirror images
bool isSymmetricHelper(TreeNode* left, TreeNode* right) {
    // Base case: if either is null, both must be null to be symmetric
    if (!left || !right)
        return left == right;

    // Values must match and subtrees must be mirrors
    if (left->data != right->data)
        return false;

    // Check outer and inner mirror pairs
    return isSymmetricHelper(left->left, right->right) &&
           isSymmetricHelper(left->right, right->left);
}

// Main function to check if a tree is symmetric
bool isSymmetric(TreeNode* root) {
    // An empty tree is symmetric
    return root == nullptr || isSymmetricHelper(root->left, root->right);
}

/*
Time Complexity: O(N)
- Every node is visited once in the recursive comparison.

Space Complexity: O(H)
- Due to recursion stack, where H = height of the tree.
*/

int main() {
    // Example: symmetric tree
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(2);
    root->left->left = new TreeNode(3);
    root->left->right = new TreeNode(4);
    root->right->left = new TreeNode(4);
    root->right->right = new TreeNode(3);

    cout << (isSymmetric(root) ? "Tree is Symmetric" : "Tree is Not Symmetric") << endl;

    return 0;
}
