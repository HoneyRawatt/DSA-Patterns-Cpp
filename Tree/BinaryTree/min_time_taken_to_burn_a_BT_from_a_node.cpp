#include <iostream>
#include <queue>
#include <map>
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
    TreeNode(int val) {
        this->val = val;
        left = nullptr;
        right = nullptr;
    }
};

/*
Approach: BFS + Parent Mapping
1. Traverse tree with BFS and map each node to its parent.
2. Start BFS from target node, visiting left, right, and parent nodes.
3. Count levels of BFS as time to burn the tree.
Time Complexity: O(N) - each node visited once
Space Complexity: O(N) - for parent map + queue + visited map
*/

// Step 1: Map each node to its parent and find target node
TreeNode* bfsToMapParents(TreeNode* root, map<TreeNode*, TreeNode*>& parentMap, int start) {
    queue<TreeNode*> q;
    q.push(root);
    TreeNode* targetNode = nullptr;

    while (!q.empty()) {
        TreeNode* node = q.front(); q.pop();
        if (node->val == start) targetNode = node;

        if (node->left) {
            parentMap[node->left] = node;
            q.push(node->left);
        }
        if (node->right) {
            parentMap[node->right] = node;
            q.push(node->right);
        }
    }
    return targetNode;
}

// Step 2: BFS from target to calculate min time to burn tree
int findMinDistance(map<TreeNode*, TreeNode*>& parentMap, TreeNode* target) {
    queue<TreeNode*> q;
    map<TreeNode*, bool> visited;
    q.push(target);
    visited[target] = true;

    int time = 0;

    while (!q.empty()) {
        int size = q.size();
        bool flag = false;

        for (int i = 0; i < size; i++) {
            TreeNode* node = q.front(); q.pop();

            if (node->left && !visited[node->left]) {
                flag = true;
                visited[node->left] = true;
                q.push(node->left);
            }
            if (node->right && !visited[node->right]) {
                flag = true;
                visited[node->right] = true;
                q.push(node->right);
            }
            if (parentMap[node] && !visited[parentMap[node]]) {
                flag = true;
                visited[parentMap[node]] = true;
                q.push(parentMap[node]);
            }
        }

        if (flag) time++; // Only increase time if we spread fire to new nodes
    }

    return time;
}

// Main function for BFS approach
int timeToBurnTree(TreeNode* root, int start) {
    map<TreeNode*, TreeNode*> parentMap;
    TreeNode* target = bfsToMapParents(root, parentMap, start);
    return findMinDistance(parentMap, target);
}



/*
Approach: DFS Recursive
1. Recursively calculate height of left and right subtrees.
2. If current node is target, mark it with -1 and propagate distance upwards.
3. Update the answer using opposite subtree height + distance to target.
Time Complexity: O(N) - each node visited once
Space Complexity: O(H) - recursive stack, H = height of tree
*/
class Solution {
public:
    int ans = 0;

    int solve(TreeNode* node, int start){
        if (!node) return 0;

        int l = solve(node->left, start);
        int r = solve(node->right, start);

        // If this is the target node
        if (node->val == start) {
            ans = max(ans, max(l, r));
            return -1; // mark target
        }
        // If target is in left subtree
        else if (l < 0) {
            ans = max(ans, abs(l) + r); 
            return l - 1; // propagate distance
        } 
        // If target is in right subtree
        else if (r < 0) {
            ans = max(ans, abs(r) + l);
            return r - 1; // propagate distance
        }
        return 1 + max(l, r); // normal height calculation
    }

    int amountOfTime(TreeNode* root, int start) {
        solve(root, start);
        return ans;
    }
};