#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>
using namespace std;

/*
Class: TreeNode
Purpose: Represents a node in a binary tree.
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

// Mark parents of each node for upward traversal
void markParents(TreeNode* root, unordered_map<TreeNode*, TreeNode*>& parent_track) {
    queue<TreeNode*> q;
    q.push(root);

    while (!q.empty()) {
        TreeNode* curr = q.front();
        q.pop();

        if (curr->left) {
            parent_track[curr->left] = curr;
            q.push(curr->left);
        }
        if (curr->right) {
            parent_track[curr->right] = curr;
            q.push(curr->right);
        }
    }
}

// Returns all nodes at distance K from target
vector<int> distanceK(TreeNode* root, TreeNode* target, int k) {
    unordered_map<TreeNode*, TreeNode*> parent_track;
    markParents(root, parent_track);

    unordered_map<TreeNode*, bool> visited;
    queue<TreeNode*> q;
    q.push(target);
    visited[target] = true;

    int currLevel = 0;
    while (!q.empty()) {
        int size = q.size();
        if (currLevel++ == k) break;

        for (int i = 0; i < size; i++) {
            TreeNode* curr = q.front();
            q.pop();

            if (curr->left && !visited[curr->left]) {
                q.push(curr->left);
                visited[curr->left] = true;
            }
            if (curr->right && !visited[curr->right]) {
                q.push(curr->right);
                visited[curr->right] = true;
            }
            if (parent_track.find(curr) != parent_track.end() && !visited[parent_track[curr]]) {
                q.push(parent_track[curr]);
                visited[parent_track[curr]] = true;
            }
        }
    }

    vector<int> res;
    while (!q.empty()) {
        res.push_back(q.front()->data);
        q.pop();
    }
    return res;
}

int main() {
    /*
          3
         / \
        5   1
       / \  / \
      6  2 0   8
        / \
       7   4
    */

    TreeNode* root = new TreeNode(3);
    root->left = new TreeNode(5);
    root->right = new TreeNode(1);
    root->left->left = new TreeNode(6);
    root->left->right = new TreeNode(2);
    root->right->left = new TreeNode(0);
    root->right->right = new TreeNode(8);
    root->left->right->left = new TreeNode(7);
    root->left->right->right = new TreeNode(4);

    TreeNode* target = root->left; // Node with value 5
    int k = 2;

    vector<int> result = distanceK(root, target, k);

    cout << "Nodes at distance " << k << " from target " << target->data << ": ";
    for (int val : result) {
        cout << val << " ";
    }
    cout << endl;

    return 0;
}

/*
Time Complexity: O(N)
    - Marking parents: visits each node once → O(N)
    - BFS to find distance K: each node visited at most once → O(N)
    Total = O(N)

Space Complexity: O(N)
    - Parent map: stores parent of each node → O(N)
    - Visited map: stores visited nodes → O(N)
    - Queue: stores nodes level-wise → O(N)
*/
