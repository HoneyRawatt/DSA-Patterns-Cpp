#include <iostream>
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

/*
Helper function to insert a value into BST
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
Function: kthsmallest
Purpose: Find the kth smallest element in BST using Morris Inorder Traversal
Approach: 
  - Uses Morris traversal to traverse BST inorder without recursion or stack.
  - Counts nodes visited in inorder sequence.
  - When count == k, return the node.
Time Complexity: O(n) in worst case (each node visited at most twice)
Space Complexity: O(1) (no recursion or stack used)
*/
TreeNode* kthsmallest(TreeNode* root, int k) {
    int cnt = 0;
    TreeNode* curr = root;

    while (curr != nullptr) {
        if (curr->left == nullptr) {
            cnt++;
            if (cnt == k) return curr;
            curr = curr->right;
        } else {
            TreeNode* prev = curr->left;
            while (prev->right && prev->right != curr)
                prev = prev->right;

            if (prev->right == nullptr) {
                // Create thread
                prev->right = curr;
                curr = curr->left;
            } else {
                // Thread exists — remove it
                prev->right = nullptr;
                cnt++;
                if (cnt == k) return curr;
                curr = curr->right;
            }
        }
    }
    return nullptr; // kth element doesn't exist
}

/*
Function: kthLargest
Purpose: Find the kth largest element in BST using Morris Reverse Inorder Traversal
Approach: 
  - Uses Morris traversal in reverse inorder (Right → Node → Left) to traverse in descending order.
  - Counts nodes visited.
  - When count == k, return the node.
Time Complexity: O(n) in worst case
Space Complexity: O(1)
*/
TreeNode* kthLargest(TreeNode* root, int k) {
    int cnt = 0;
    TreeNode* curr = root;

    while (curr != nullptr) {
        if (curr->right == nullptr) {
            cnt++;
            if (cnt == k) return curr;
            curr = curr->left;
        } else {
            TreeNode* next = curr->right;
            while (next->left && next->left != curr)
                next = next->left;

            if (next->left == nullptr) {
                // Create thread
                next->left = curr;
                curr = curr->right;
            } else {
                // Thread exists — remove it
                next->left = nullptr;
                cnt++;
                if (cnt == k) return curr;
                curr = curr->left;
            }
        }
    }
    return nullptr; // kth largest doesn't exist
}

int main() {
    // Create BST
    TreeNode* root = nullptr;
    root = insertBST(root, 5);
    root = insertBST(root, 3);
    root = insertBST(root, 6);
    root = insertBST(root, 2);
    root = insertBST(root, 4);
    root = insertBST(root, 1);

    int k_small = 3;
    TreeNode* kthSmallestNode = kthsmallest(root, k_small);
    if (kthSmallestNode)
        cout << k_small << "th smallest element is: " << kthSmallestNode->val << endl;
    else
        cout << "Less than " << k_small << " nodes in the tree.\n";

    int k_large = 2;
    TreeNode* kthLargestNode = kthLargest(root, k_large);
    if (kthLargestNode)
        cout << k_large << "th largest element is: " << kthLargestNode->val << endl;
    else
        cout << "Less than " << k_large << " nodes in the tree.\n";

    return 0;
}
