#include <iostream>
#include <vector>
#include <queue>
#include <sstream>
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
Function: serialize
Purpose: Convert a binary tree into a string using level-order traversal
*/
string serialize(TreeNode* root) {
    if (!root) return "#,";  // empty tree
    string s = "";
    queue<TreeNode*> q;
    q.push(root);

    while (!q.empty()) {
        TreeNode* curr = q.front();
        q.pop();

        if (curr == nullptr) {
            s.append("#,");
        } else {
            s.append(to_string(curr->val) + ",");
            q.push(curr->left);
            q.push(curr->right);
        }
    }
    return s;
}

/*
Function: deserialize
Purpose: Reconstruct the binary tree from its serialized string
*/
TreeNode* deserialize(string data) {
    if (data.size() == 0) return nullptr;

    stringstream s(data);
    string str;

    getline(s, str, ',');
    if (str == "#") return nullptr;

    TreeNode* root = new TreeNode(stoi(str));
    queue<TreeNode*> q;
    q.push(root);

    while (!q.empty()) {
        TreeNode* node = q.front();
        q.pop();

        // Left child
        if (!getline(s, str, ',')) break;
        if (str == "#") {
            node->left = nullptr;
        } else {
            TreeNode* leftNode = new TreeNode(stoi(str));
            node->left = leftNode;
            q.push(leftNode);
        }

        // Right child
        if (!getline(s, str, ',')) break;
        if (str == "#") {
            node->right = nullptr;
        } else {
            TreeNode* rightNode = new TreeNode(stoi(str));
            node->right = rightNode;
            q.push(rightNode);
        }
    }
    return root;
}

/*
Helper function to print the tree (Inorder traversal)
*/
void inorder(TreeNode* root) {
    if (!root) return;
    inorder(root->left);
    cout << root->val << " ";
    inorder(root->right);
}

/*
Main function for testing
*/
int main() {
    // Create a test binary tree
    /*
              1
             / \
            2   3
               / \
              4   5
    */
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->right->left = new TreeNode(4);
    root->right->right = new TreeNode(5);

    // Serialize the tree
    string data = serialize(root);
    cout << "Serialized Tree: " << data << endl;

    // Deserialize the tree
    TreeNode* newRoot = deserialize(data);
    cout << "Inorder of Deserialized Tree: ";
    inorder(newRoot);
    cout << endl;

    return 0;
}


// Aspect	Complexity	Explanation
// Time	O(N)	Every node is visited once during serialization & deserialization
// Space	O(N)	Queue stores up to all nodes in one level at a time