#include <iostream>
#include <vector>
#include <climits>
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
class BSTIterator {
    stack<TreeNode*> st;

public:
    // Constructor: initialize stack with all left children
    BSTIterator(TreeNode* root) {
        pushAll(root);
    }

    // Returns true if there is a next smallest element
    bool hasNext() {
        return !st.empty();
    }

    // Returns the next smallest element
    int next() {
        TreeNode* tmpNode = st.top();
        st.pop();
        // Push all left children of the right subtree
        pushAll(tmpNode->right);
        return tmpNode->val;
    }

private:
    // Push all left children of a subtree
    void pushAll(TreeNode* node) {
        while (node != nullptr) {
            st.push(node);
            node = node->left;
        }
    }
};
