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
Function: topV
Purpose : Returns the top view of a binary tree.

Approach:
- Use BFS (level-order traversal).
- Track each node's horizontal distance (HD) from root.
- For each HD, only record the **first node** encountered.
- Use map<int,int> to store HD -> node value (sorted by HD automatically).

Time Complexity: O(N log N)
- BFS: O(N)
- Map insertion & traversal: O(log N) per node

Space Complexity: O(N)
- Queue stores nodes for BFS.
- Map stores nodes by HD.
*/
vector<int> topV(TreeNode* root) {
    vector<int> ans;
    if (!root) return ans;

    map<int,int> mp; // HD -> node data
    queue<pair<TreeNode*, int>> q; // node + HD
    q.push({root, 0});

    while (!q.empty()) {
        auto it = q.front(); q.pop();
        TreeNode* node = it.first;
        int line = it.second;

        // Only record the first node encountered at this HD
        if (mp.find(line) == mp.end()) {
            mp[line] = node->data;
        }

        if (node->left) q.push({node->left, line - 1});
        if (node->right) q.push({node->right, line + 1});
    }

    // Extract top view in order from leftmost HD to rightmost HD
    for (auto it : mp) {
        ans.push_back(it.second);
    }

    return ans;
}

/* Example Usage */
int main() {
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->right = new TreeNode(4);
    root->left->right->right = new TreeNode(5);
    root->left->right->right->right = new TreeNode(6);

    vector<int> result = topV(root);
    for (int val : result) cout << val << " ";
    cout << endl; // Expected: 2 1 3 6

    return 0;
}
