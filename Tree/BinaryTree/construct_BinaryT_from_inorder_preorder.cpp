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
Helper function: Builds the tree recursively
preorder   : preorder traversal array
prestart, preend : current range in preorder array
inorder    : inorder traversal array
instart, inend  : current range in inorder array
mpp        : map from node value to its index in inorder array
Returns    : pointer to the root of subtree
Time       : O(N)
Space      : O(N) for recursion stack + O(N) for map
*/
TreeNode* buildTreeHelper(vector<int>& preorder, int prestart, int preend,
                          vector<int>& inorder, int instart, int inend,
                          map<int, int>& mpp) {
    if (prestart > preend || instart > inend) return nullptr;

    TreeNode* root = new TreeNode(preorder[prestart]);

    int inroot = mpp[root->val];       // index of root in inorder
    int numleft = inroot - instart;    // number of nodes in left subtree

    // build left and right subtrees recursively
    root->left = buildTreeHelper(preorder, prestart + 1, prestart + numleft,
                                 inorder, instart, inroot - 1, mpp);
    root->right = buildTreeHelper(preorder, prestart + numleft + 1, preend,
                                  inorder, inroot + 1, inend, mpp);

    return root;
}

/*
Function: buildTree
Purpose : Main function to build tree from preorder and inorder arrays
Time    : O(N)
Space   : O(N) (recursion stack + map)
*/
TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
    map<int, int> mpp;
    for (int i = 0; i < inorder.size(); i++) {
        mpp[inorder[i]] = i;   // store index of each value in inorder
    }
    return buildTreeHelper(preorder, 0, preorder.size() - 1,
                           inorder, 0, inorder.size() - 1, mpp);
}

// Optional: Inorder print to verify tree
void printInorder(TreeNode* root) {
    if (!root) return;
    printInorder(root->left);
    cout << root->val << " ";
    printInorder(root->right);
}

/* Main function to test */
int main() {
    vector<int> preorder = {3, 9, 20, 15, 7};
    vector<int> inorder = {9, 3, 15, 20, 7};

    TreeNode* root = buildTree(preorder, inorder);

    cout << "Inorder traversal of constructed tree: ";
    printInorder(root); // should match original inorder array
    cout << endl;

    return 0;
}
