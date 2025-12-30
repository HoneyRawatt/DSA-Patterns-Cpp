#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;

/*
Class: TreeNode
Purpose: Represents a node in a binary tree.
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
Function: changeTree()
Purpose : Modifies the given binary tree so that it satisfies the
          Children Sum Property (CSP):
          → For every node, node->data = sum of (left->data + right->data)
*/
void changeTree(TreeNode* root) {
    if (!root) return;

    // Step 1: Calculate sum of children
    int child = 0;
    if (root->left) child += root->left->data;
    if (root->right) child += root->right->data;

    // Step 2: If children sum >= node value, update node
    // Otherwise, push node's value to children
    if (child >= root->data)
        root->data = child;
    else {
        if (root->left) root->left->data = root->data;
        if (root->right) root->right->data = root->data;
    }

    // Step 3: Recurse on left and right children
    changeTree(root->left);
    changeTree(root->right);

    // Step 4: Update current node with final children sum
    int tot = 0;
    if (root->left) tot += root->left->data;
    if (root->right) tot += root->right->data;

    if (root->left || root->right)
        root->data = tot;
}

/*
Helper: printLevelOrder()
Purpose: Prints tree in level order (BFS traversal)
*/
void printLevelOrder(TreeNode* root) {
    if (!root) return;

    queue<TreeNode*> q;
    q.push(root);

    while (!q.empty()) {
        int n = q.size();
        while (n--) {
            TreeNode* node = q.front();
            q.pop();
            cout << node->data << " ";
            if (node->left) q.push(node->left);
            if (node->right) q.push(node->right);
        }
        cout << endl;
    }
}

/*
Main Function:
1. Builds the following binary tree:
            50
           /  \
         7     2
        / \   / \
       3  5  1  30
2. Prints before and after applying Children Sum Property
*/
int main() {
    // Building sample tree
    TreeNode* root = new TreeNode(50);
    root->left = new TreeNode(7);
    root->right = new TreeNode(2);
    root->left->left = new TreeNode(3);
    root->left->right = new TreeNode(5);
    root->right->left = new TreeNode(1);
    root->right->right = new TreeNode(30);

    cout << "Before changeTree() - Level Order Traversal:\n";
    printLevelOrder(root);

    // Apply Children Sum Property
    changeTree(root);

    cout << "\nAfter changeTree() - Level Order Traversal:\n";
    printLevelOrder(root);

    return 0;
}

/*
Time Complexity:  O(N)
    → Each node is visited once.
Space Complexity: O(H)
    → Recursive stack space, where H = height of tree.
*/
