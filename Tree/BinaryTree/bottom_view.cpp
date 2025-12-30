#include <iostream>
#include <vector>
#include <map>
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
Function: bottomv
Purpose : Returns the bottom view of a binary tree.
Approach:
- BFS traversal (level-order)
- Track horizontal distance (HD) for each node
- For bottom view, overwrite the value at each HD whenever a node is encountered
- Map stores HD -> node value, automatically sorted by HD
*/
vector<int> bottomv(TreeNode* root) {
    vector<int> ans;
    if (!root) return ans;

    map<int,int> mp;  // HD -> node data
    queue<pair<TreeNode*, int>> q; // node + HD
    q.push({root, 0});

    while (!q.empty()) {
        auto it = q.front(); q.pop();
        TreeNode* node = it.first;
        int line = it.second;

        // Overwrite value at this HD, so bottommost node remains
        mp[line] = node->data;

        if (node->left) q.push({node->left, line - 1});
        if (node->right) q.push({node->right, line + 1});
    }

    // Extract bottom view from leftmost to rightmost HD
    for (auto it : mp) {
        ans.push_back(it.second);
    }

    return ans;
}

/* Example Usage */
int main() {
    TreeNode* root = new TreeNode(20);
    root->left = new TreeNode(8);
    root->right = new TreeNode(22);
    root->left->left = new TreeNode(5);
    root->left->right = new TreeNode(3);
    root->right->left = new TreeNode(4);
    root->right->right = new TreeNode(25);
    root->left->right->left = new TreeNode(10);
    root->left->right->right = new TreeNode(14);

    vector<int> result = bottomv(root);
    for (int val : result) cout << val << " ";
    cout << endl; // Expected: 5 10 4 14 25

    return 0;
}
