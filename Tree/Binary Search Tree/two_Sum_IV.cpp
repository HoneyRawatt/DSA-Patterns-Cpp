#include <iostream>
#include <vector>
#include <stack>
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
        left = right = nullptr;
    }
};

// BST Iterator class supporting normal and reverse in-order traversal
class BSTIterator {
    stack<TreeNode*> st;
    bool reverse; // false = normal inorder, true = reverse inorder

public:
    BSTIterator(TreeNode* root, bool isReverse) {
        reverse = isReverse;
        pushAll(root);
    }

    bool hasNext() {
        return !st.empty();
    }

    int next() {
        TreeNode* tmp = st.top();
        st.pop();

        if (!reverse)
            pushAll(tmp->right); // normal inorder: push right subtree
        else
            pushAll(tmp->left);  // reverse inorder: push left subtree

        return tmp->val;
    }

private:
    void pushAll(TreeNode* node) {
        while (node != nullptr) {
            st.push(node);
            if (reverse)
                node = node->right; // reverse inorder
            else
                node = node->left;  // normal inorder
        }
    }
};

// Function to check if there exists a pair with sum k in BST
bool findTarget(TreeNode* root, int k) {
    if (!root) return false;

    BSTIterator leftIter(root, false);  // normal inorder
    BSTIterator rightIter(root, true);  // reverse inorder

    int i = leftIter.next();
    int j = rightIter.next();

    while (i < j) {
        if (i + j == k) return true;
        else if (i + j < k) i = leftIter.next();
        else j = rightIter.next();
    }
    return false;
}

// Helper function: inorder traversal to store BST elements in sorted order
void inorderTraversal(TreeNode* root, vector<int>& nums) {
    if (!root) return;
    inorderTraversal(root->left, nums);
    nums.push_back(root->val);
    inorderTraversal(root->right, nums);
}

// Brute-force approach: use vector + two pointers
bool findTargetBrute(TreeNode* root, int k) {
    vector<int> nums;
    inorderTraversal(root, nums); // O(n) time, O(n) space

    int left = 0;
    int right = nums.size() - 1;

    while (left < right) { // O(n) time
        int sum = nums[left] + nums[right];
        if (sum == k) return true;
        else if (sum < k) left++;
        else right--;
    }

    return false;
}
// Main function for testing
int main() {
    /*
           5
          / \
         3   8
        / \   \
       2   4   9
    */
    TreeNode* root = new TreeNode(5);
    root->left = new TreeNode(3);
    root->right = new TreeNode(8);
    root->left->left = new TreeNode(2);
    root->left->right = new TreeNode(4);
    root->right->right = new TreeNode(9);

    int k = 7;
    if (findTarget(root, k))
        cout << "Pair found for sum " << k << endl;
    else
        cout << "No pair found for sum " << k << endl;

    return 0;
}
