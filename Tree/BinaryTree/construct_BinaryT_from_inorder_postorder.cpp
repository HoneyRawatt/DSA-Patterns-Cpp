#include <iostream>
#include <vector>
#include <map>
using namespace std;

/*
Class: TreeNode
Purpose: Represents a node in a binary tree
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

/*
Helper function to recursively build the binary tree
from inorder and postorder traversals.
*/
TreeNode* BuildTreeHelper(vector<int>& inorder, int is, int ie,
                          vector<int>& postorder, int ps, int pe,
                          map<int, int>& mpp) {
    if (ps > pe || is > ie) return nullptr;

    // The last element in postorder is the root
    TreeNode* root = new TreeNode(postorder[pe]);

    // Find root index in inorder traversal
    int inRoot = mpp[postorder[pe]];

    // Count nodes in left subtree
    int numLeft = inRoot - is;

    // Build left and right subtrees recursively
    root->left = BuildTreeHelper(inorder, is, inRoot - 1,
                                 postorder, ps, ps + numLeft - 1, mpp);

    root->right = BuildTreeHelper(inorder, inRoot + 1, ie,
                                  postorder, ps + numLeft, pe - 1, mpp);

    return root;
}

/*
Function: BuildTree
Purpose : Sets up map and calls recursive helper
*/
TreeNode* BuildTree(vector<int>& inorder, vector<int>& postorder) {
    if (inorder.size() != postorder.size()) return nullptr;

    map<int, int> mpp;
    for (int i = 0; i < inorder.size(); i++) mpp[inorder[i]] = i;

    return BuildTreeHelper(inorder, 0, inorder.size() - 1,
                           postorder, 0, postorder.size() - 1, mpp);
}

/*
Utility function to print preorder traversal of the tree
to verify the structure
*/
void printPreorder(TreeNode* root) {
    if (!root) return;
    cout << root->val << " ";
    printPreorder(root->left);
    printPreorder(root->right);
}

/*
Main function to test BuildTree()
*/
int main() {
    vector<int> inorder = {9, 3, 15, 20, 7};
    vector<int> postorder = {9, 15, 7, 20, 3};

    TreeNode* root = BuildTree(inorder, postorder);

    cout << "Preorder traversal of constructed tree: ";
    printPreorder(root);
    cout << endl;

    return 0;
}

/*
Expected Output:
Preorder traversal of constructed tree: 3 9 20 15 7

Time Complexity  : O(N)
Space Complexity : O(N)
*/
