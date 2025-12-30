#include <iostream>
#include <algorithm>
using namespace std;

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

/*
Function: maxPathSumHelper
Purpose: Recursive helper to compute maximum path sum in binary tree
Returns: Maximum path sum **starting from current node and going down**
Updates: maxi — maximum path sum anywhere in the tree
Time Complexity: O(N) — each node visited once
Space Complexity: O(H) — recursion stack
*/
int maxPathSumHelper(TreeNode* root, int &maxi) {
    if (!root) return 0;

    int leftsum = max(0, maxPathSumHelper(root->left, maxi));   // ignore negative paths
    int rightsum = max(0, maxPathSumHelper(root->right, maxi)); // ignore negative paths

    maxi = max(maxi, leftsum + rightsum + root->data); // path through root

    return root->data + max(leftsum, rightsum); // max path sum starting from root
}

/*
Function: maxPathSum
Purpose: Return the maximum path sum in the tree
*/
int maxPathSum(TreeNode* root) {
    int maxi = INT_MIN;
    maxPathSumHelper(root, maxi);
    return maxi;
}

/* Example usage */
int main() {
    TreeNode* root = new TreeNode(10);
    root->left = new TreeNode(2);
    root->right = new TreeNode(10);
    root->left->left = new TreeNode(20);
    root->left->right = new TreeNode(1);
    root->right->right = new TreeNode(-25);
    root->right->right->left = new TreeNode(3);
    root->right->right->right = new TreeNode(4);

    cout << "Maximum Path Sum: " << maxPathSum(root) << endl;
    return 0;
}
