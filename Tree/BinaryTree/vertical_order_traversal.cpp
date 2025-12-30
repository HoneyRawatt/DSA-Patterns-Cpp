#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <set>
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
Function: verticalTraversal()
Purpose : Perform a vertical order traversal of the binary tree.

Approach:
1️⃣ Use BFS (level order traversal) while tracking each node's position:
    - Horizontal distance (x)
    - Level/depth (y)

2️⃣ Use a nested map structure:
    map<int, map<int, multiset<int>>> nodes;
    - First `int` → x coordinate (vertical column)
    - Second `int` → y coordinate (depth level)
    - `multiset<int>` → multiple nodes at same (x, y), stored in sorted order

3️⃣ Traverse tree using a queue of {node, {x, y}}.

4️⃣ Finally, combine all values from leftmost x to rightmost x.

Time Complexity:  
- O(N log N):  
  - Each insertion into the `map` and `multiset` costs O(log N)
  - N nodes processed.

Space Complexity:  
- O(N):  
  - For storing map, queue, and traversal output.
*/
vector<vector<int>> verticalTraversal(TreeNode* root) {
    // Base case
    if (!root) return {};

    // map<x, map<y, multiset<values>>>
    map<int, map<int, multiset<int>>> nodes;

    // Queue for BFS: stores {node, {x, y}}
    queue<pair<TreeNode*, pair<int, int>>> todo;
    todo.push({root, {0, 0}});

    while (!todo.empty()) {
        auto p = todo.front();
        todo.pop();

        TreeNode* node = p.first;
        int x = p.second.first;   // horizontal distance
        int y = p.second.second;  // depth

        nodes[x][y].insert(node->data);

        // Left child: x - 1, y + 1
        if (node->left)
            todo.push({node->left, {x - 1, y + 1}});
        // Right child: x + 1, y + 1
        if (node->right)
            todo.push({node->right, {x + 1, y + 1}});
    }

    // Collect results from the map
    vector<vector<int>> ans;
    for (auto& xPair : nodes) {
        vector<int> col;
        for (auto& yPair : xPair.second) {
            col.insert(col.end(), yPair.second.begin(), yPair.second.end());
        }
        ans.push_back(col);
    }

    return ans;
}

/*
Driver Code: Demonstrates the vertical traversal
*/
int main() {
    /*
            3
           / \
          9   20
              / \
             15  7
    */
    TreeNode* root = new TreeNode(3);
    root->left = new TreeNode(9);
    root->right = new TreeNode(20);
    root->right->left = new TreeNode(15);
    root->right->right = new TreeNode(7);

    vector<vector<int>> result = verticalTraversal(root);

    cout << "Vertical Order Traversal:\n";
    for (auto& col : result) {
        for (int val : col)
            cout << val << " ";
        cout << endl;
    }

    return 0;
}
