#include <bits/stdc++.h>
using namespace std;

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

/*
==========================
Brute Force Approach
==========================
1. Traverse BST inorder and store all nodes in a vector.
2. Sort the values to get correct inorder sequence.
3. Replace node values with sorted values to fix the BST.

Time Complexity: O(n log n) → due to sorting the inorder array
Space Complexity: O(n) → for storing inorder nodes
*/
class BruteForceSolution {
private:
    void inorder(TreeNode* root, vector<TreeNode*>& nodes) {
        if (!root) return;
        inorder(root->left, nodes);
        nodes.push_back(root);
        inorder(root->right, nodes);
    }

public:
    void recoverTree(TreeNode* root) {
        vector<TreeNode*> nodes;
        inorder(root, nodes);

        // Extract values and sort
        vector<int> values;
        for (auto node : nodes) values.push_back(node->val);
        sort(values.begin(), values.end());

        // Replace node values with sorted values
        for (int i = 0; i < nodes.size(); i++) {
            nodes[i]->val = values[i];
        }
    }
};

/*
==========================
Optimal Approach
==========================
1. Use inorder traversal to detect swapped nodes.
2. Track prev node, and identify two nodes that are out of order.
3. Swap values of the identified nodes.

Time Complexity: O(n) → traverse BST once
Space Complexity: O(h) → recursion stack (h = height of BST)
*/
class OptimalSolution {
private:
    TreeNode* first;
    TreeNode* middle;
    TreeNode* last;
    TreeNode* prev;

    void inorder(TreeNode* root) {
        if (!root) return;

        inorder(root->left);

        if (prev && root->val < prev->val) {
            if (!first) {        // First violation
                first = prev;
                middle = root;
            } else {             // Second violation
                last = root;
            }
        }

        prev = root;

        inorder(root->right);
    }

public:
    void recoverTree(TreeNode* root) {
        first = middle = last = nullptr;
        prev = new TreeNode(INT_MIN);

        inorder(root);

        if (first && last) swap(first->val, last->val);       // Non-adjacent swap
        else if (first && middle) swap(first->val, middle->val); // Adjacent swap
    }
};

// Utility function to print inorder
void printInorder(TreeNode* root) {
    if (!root) return;
    printInorder(root->left);
    cout << root->val << " ";
    printInorder(root->right);
}

int main() {
    // Example: 3 and 1 swapped in BST 1-3-2
    TreeNode* root = new TreeNode(3);
    root->left = new TreeNode(1);
    root->right = new TreeNode(4);
    root->right->left = new TreeNode(2);

    cout << "Original inorder traversal: ";
    printInorder(root);
    cout << endl;

    // Brute force solution
    BruteForceSolution brute;
    brute.recoverTree(root);
    cout << "After brute force recover inorder: ";
    printInorder(root);
    cout << endl;

    // Swap again to test optimal approach
    swap(root->val, root->right->left->val); // Swap 3 and 2

    OptimalSolution opt;
    opt.recoverTree(root);
    cout << "After optimal recover inorder: ";
    printInorder(root);
    cout << endl;

    return 0;
}
