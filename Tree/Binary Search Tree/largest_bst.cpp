#include <bits/stdc++.h>
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
    TreeNode(int value) {
        val = value;
        left = right = nullptr;
    }
};

/* --------------------------------------------------------
   ✅ BRUTE FORCE APPROACH
   --------------------------------------------------------
   For each node:
   - Check if its subtree is a valid BST (using min/max bounds)
   - If valid, calculate its size
   - Otherwise, check left & right subtrees
   --------------------------------------------------------
   Time:  O(N^2)
   Space: O(H)
-------------------------------------------------------- */

// Helper function: checks if a subtree is a valid BST
bool isValidBST(TreeNode* root, long minval, long maxval) {
    if (!root) return true;
    if (root->val <= minval || root->val >= maxval) return false;
    return isValidBST(root->left, minval, root->val) &&
           isValidBST(root->right, root->val, maxval);
}

// Count nodes in a subtree
int countNodes(TreeNode* root) {
    if (!root) return 0;
    return 1 + countNodes(root->left) + countNodes(root->right);
}

// Main brute-force logic
int largestBSTBrute(TreeNode* root) {
    if (!root) return 0;

    // If current subtree is a valid BST → return its size
    if (isValidBST(root, LONG_MIN, LONG_MAX))
        return countNodes(root);

    // Otherwise, check left and right subtrees
    return max(largestBSTBrute(root->left), largestBSTBrute(root->right));
}

/* --------------------------------------------------------
   ✅ OPTIMAL APPROACH (Single traversal)
   --------------------------------------------------------
   Using postorder traversal, return info for each subtree:
   - minnode, maxnode, and size of largest BST
   If subtree is valid BST, combine info.
   --------------------------------------------------------
   Time:  O(N)
   Space: O(H)
-------------------------------------------------------- */

class NodeValue {
public:
    int minnode;
    int maxnode;
    int maxsize;

    NodeValue(int minnode, int maxnode, int maxsize) {
        this->minnode = minnode;
        this->maxnode = maxnode;
        this->maxsize = maxsize;
    }
};

NodeValue largestBSTSubtree(TreeNode* root) {
    // Base case: empty tree is a valid BST of size 0
    if (!root) return NodeValue(INT_MAX, INT_MIN, 0);

    // Recursively get info from left and right subtrees
    auto left = largestBSTSubtree(root->left);
    auto right = largestBSTSubtree(root->right);

    // Check if current tree is a BST
    if (left.maxnode < root->val && root->val < right.minnode) {
        // It’s a valid BST → return updated info
        return NodeValue(
            min(root->val, left.minnode),
            max(root->val, right.maxnode),
            left.maxsize + right.maxsize + 1
        );
    }

    // Otherwise, return invalid BST markers
    return NodeValue(INT_MIN, INT_MAX, max(left.maxsize, right.maxsize));
}

int largestBST(TreeNode* root) {
    return largestBSTSubtree(root).maxsize;
}

/* --------------------------------------------------------
   🧪 MAIN FUNCTION FOR TESTING
-------------------------------------------------------- */
int main() {
    /*
              10
             /  \
            5    15
           / \     \
          1   8     7
       → Largest BST is subtree [5,1,8] of size = 3
    */
    TreeNode* root = new TreeNode(10);
    root->left = new TreeNode(5);
    root->right = new TreeNode(15);
    root->left->left = new TreeNode(1);
    root->left->right = new TreeNode(8);
    root->right->right = new TreeNode(7);

    cout << "Brute Force Largest BST Size: " << largestBSTBrute(root) << endl;
    cout << "Optimal Largest BST Size: " << largestBST(root) << endl;

    return 0;
}

/*
------------------------------------------------------------
💡 Explanation of Both Approaches
------------------------------------------------------------

1️⃣ Brute Force Approach:
- For every node:
   → Check if it forms a valid BST using min/max rules.
   → If yes, count its nodes.
   → Else, move to left/right subtree.
- Time = O(N^2) (each node can recheck all descendants)
- Space = O(H)

2️⃣ Optimal Approach:
- Perform a single postorder traversal.
- For each node, gather info:
   → Left subtree’s min, max, size
   → Right subtree’s min, max, size
- If valid BST, combine and return updated info.
- Else, return invalid markers and keep the max size seen.
- Time = O(N)
- Space = O(H)

------------------------------------------------------------
*/
