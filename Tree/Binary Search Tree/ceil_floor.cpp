#include <iostream>
using namespace std;

/*
Class: TreeNode
Purpose: Represents a node in a binary search tree
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
Function: ceil_bst
Purpose: Finds the smallest value in BST that is >= key
*/
int ceil_bst(TreeNode* root, int key) {
    int ceil = -1;
    while (root) {
        if (root->val == key) {
            ceil = root->val;
            return ceil;
        }
        if (key > root->val) {
            root = root->right;
        } else {
            ceil = root->val;   // ✅ fixed: use .val, not .data
            root = root->left;
        }
    }
    return ceil;
}

/*
Function: floor_bst
Purpose: Finds the largest value in BST that is <= key
*/
int floor_bst(TreeNode* root, int key) {
    int floor = -1;
    while (root) {
        if (root->val == key) {
            floor = root->val;
            return floor;
        }
        if (key > root->val) {
            floor = root->val;  // ✅ fixed: use .val, not .data
            root = root->right;
        } else {
            root = root->left;
        }
    }
    return floor;
}

/*
Helper to insert node in BST
*/
TreeNode* insertBST(TreeNode* root, int val) {
    if (!root) return new TreeNode(val);
    if (val < root->val)
        root->left = insertBST(root->left, val);
    else
        root->right = insertBST(root->right, val);
    return root;
}

/*
Main function to test Ceil and Floor
*/
int main() {
    /*
              8
             / \
            4   12
           / \  / \
          2  6 10 14
    */
    TreeNode* root = nullptr;
    vector<int> vals = {8, 4, 12, 2, 6, 10, 14};
    for (int v : vals) root = insertBST(root, v);

    int key = 5;
    cout << "Key: " << key << endl;
    cout << "Ceil: " << ceil_bst(root, key) << endl;
    cout << "Floor: " << floor_bst(root, key) << endl;

    return 0;
}

/*
----------------------------------------------
🕒 Time Complexity: O(H) ≈ O(log N) for balanced BST
💾 Space Complexity: O(1)
----------------------------------------------
💡 Approach Summary:
- Traverse BST starting from root.
- For Ceil: move left if node->val > key, right if smaller.
- For Floor: move right if node->val < key, left if greater.
----------------------------------------------
*/
