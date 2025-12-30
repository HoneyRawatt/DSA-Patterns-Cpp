#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>
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

/*
Function: isLeaf()
Purpose: Checks if a node is a leaf node
Time Complexity: O(1)
Space Complexity: O(1)
*/
bool isLeaf(TreeNode* temp) {
    return (temp->left == nullptr && temp->right == nullptr);
}

/*
Function: addLeftBoundary()
Purpose: Adds all left boundary nodes (excluding leaves)
Time Complexity: O(H)  — where H is the height of the tree
Space Complexity: O(1)
*/
void addLeftBoundary(TreeNode* root, vector<int>& res) {
    TreeNode* curr = root->left;
    while (curr) {
        if (!isLeaf(curr)) res.push_back(curr->data);
        if (curr->left) curr = curr->left;
        else curr = curr->right;
    }
}

/*
Function: addRightBoundary()
Purpose: Adds all right boundary nodes (excluding leaves) in reverse order (bottom-up)
Time Complexity: O(H)
Space Complexity: O(H) — uses temporary vector to reverse order
*/
void addRightBoundary(TreeNode* root, vector<int>& res) {
    TreeNode* curr = root->right;
    vector<int> temp;
    while (curr) {
        if (!isLeaf(curr)) temp.push_back(curr->data);
        if (curr->right) curr = curr->right;
        else curr = curr->left;
    }
    // Add in reverse order
    for (int i = temp.size() - 1; i >= 0; i--) {
        res.push_back(temp[i]);
    }
}

/*
Function: addLeaves()
Purpose: Adds all leaf nodes (from left to right)
Time Complexity: O(N) — visits all nodes once
Space Complexity: O(H) — recursion stack
*/
void addLeaves(TreeNode* root, vector<int>& res) {
    if (isLeaf(root)) {
        res.push_back(root->data);
        return;
    }
    if (root->left) addLeaves(root->left, res);
    if (root->right) addLeaves(root->right, res);
}

/*
Function: printBoundary()
Purpose: Performs the boundary traversal of a binary tree
Boundary order = Root + Left Boundary + Leaves + Right Boundary (in reverse)
Time Complexity: O(N) — every node is visited once
Space Complexity: O(H) — recursion stack + auxiliary vectors
*/
vector<int> printBoundary(TreeNode* root) {
    vector<int> res;
    if (!root) return res;

    if (!isLeaf(root)) res.push_back(root->data); // Root node

    addLeftBoundary(root, res);  // Left boundary
    addLeaves(root, res);        // All leaves
    addRightBoundary(root, res); // Right boundary (in reverse)

    return res;
}

/*
Driver Code: Build a sample tree and print boundary traversal
Time Complexity: O(N)
Space Complexity: O(H)
*/
int main() {
    /*
              1
            /   \
           2     3
          / \   / \
         4   5 6   7
            / \
           8   9
    */

    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(5);
    root->left->right->left = new TreeNode(8);
    root->left->right->right = new TreeNode(9);
    root->right->left = new TreeNode(6);
    root->right->right = new TreeNode(7);

    vector<int> result = printBoundary(root);

    cout << "Boundary Traversal: ";
    for (int val : result) cout << val << " ";
    cout << endl;

    return 0;
}
