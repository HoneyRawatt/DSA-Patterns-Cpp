#include <iostream>
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
Function: check()
Purpose : Checks whether two binary trees (p and q) are identical.
          Two trees are considered identical if:
            1. They have the same structure.
            2. Their corresponding node values are equal.

Approach:
    - Base case: If both nodes are NULL → trees are same so far.
    - If only one node is NULL → trees differ.
    - Recursively compare left and right subtrees.

Time Complexity:  O(N)
    → Each node in both trees is visited once.

Space Complexity: O(H)
    → Recursion stack, where H is height of the tree
      Worst: O(N) for skewed tree, Best: O(log N) for balanced tree.
*/
bool check(TreeNode* p, TreeNode* q) {
    if (p == nullptr || q == nullptr)
        return p == q; // both null = true, only one null = false

    return (p->data == q->data) &&
           check(p->left, q->left) &&
           check(p->right, q->right);
}

/*
Example usage
*/
int main() {
    // Tree 1
    TreeNode* p = new TreeNode(1);
    p->left = new TreeNode(2);
    p->right = new TreeNode(3);

    // Tree 2
    TreeNode* q = new TreeNode(1);
    q->left = new TreeNode(2);
    q->right = new TreeNode(3);

    cout << (check(p, q) ? "Both trees are identical" : "Trees are not identical") << endl;

    // Modify q to make it different
    q->right->data = 4;
    cout << (check(p, q) ? "Both trees are identical" : "Trees are not identical") << endl;

    return 0;
}
