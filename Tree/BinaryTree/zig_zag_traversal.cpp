#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
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
Function: zigzagLevelOrder()
Purpose : Perform Zigzag (Spiral) Level Order Traversal of a binary tree.

Approach:
    - Use a queue for standard level order traversal.
    - Use a flag `leftToRight` to determine the direction for each level.
    - For left-to-right levels: insert elements normally.
    - For right-to-left levels: insert elements in reverse order using indexing trick.

Time Complexity:  O(N)
    → Each node is processed exactly once.

Space Complexity: O(N)
    → For queue + result storage.
*/
vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
    vector<vector<int>> res;
    if (root == nullptr) return res;

    queue<TreeNode*> nodeQueue;
    nodeQueue.push(root);
    bool leftToRight = true;

    while (!nodeQueue.empty()) {
        int size = nodeQueue.size();
        vector<int> row(size);

        for (int i = 0; i < size; i++) {
            TreeNode* node = nodeQueue.front();
            nodeQueue.pop();

            // Determine position to fill value
            int indx = (leftToRight) ? i : (size - 1 - i);
            row[indx] = node->data;

            // Push children into queue
            if (node->left) nodeQueue.push(node->left);
            if (node->right) nodeQueue.push(node->right);
        }

        // Flip traversal direction for next level
        leftToRight = !leftToRight;
        res.push_back(row);
    }

    return res;
}

/*
Example usage
*/
int main() {
    // Build sample binary tree
    /*
            1
           / \
          2   3
         / \   \
        4   5   6
    */
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(5);
    root->right->right = new TreeNode(6);

    // Perform Zigzag Level Order
    vector<vector<int>> result = zigzagLevelOrder(root);

    cout << "Zigzag Level Order Traversal:" << endl;
    for (auto &level : result) {
        for (int val : level)
            cout << val << " ";
        cout << endl;
    }

    return 0;
}
