#include <iostream>
#include <map>
using namespace std;

class node {
public:
    int val;
    node* next;
    node* random;
    node(int val) {
        this->val = val;
        next = nullptr;
        random = nullptr;
    }
    node(int val, node* next, node* random) {
        this->val = val;
        this->next = next;
        this->random = random; 
    }
};

// Brute force O(n) space
node* copy_LL_brute(node* head) {
    node* temp = head;
    map<node*, node*> mpp;

    while (temp != nullptr) {
        node* newnode = new node(temp->val);
        mpp[temp] = newnode;
        temp = temp->next;
    }

    temp = head;
    while (temp != nullptr) {
        node* copynode = mpp[temp];
        copynode->next = mpp[temp->next];
        copynode->random = mpp[temp->random];
        temp = temp->next;
    }

    return mpp[head];
}

// Optimized O(1) space
node* copy_LL(node* head) {
    if (!head) return nullptr;

    // Step 1: Insert copy nodes after original nodes
    node* temp = head;
    while (temp != nullptr) {
        node* copyNode = new node(temp->val);
        copyNode->next = temp->next;
        temp->next = copyNode;
        temp = temp->next->next;
    }

    // Step 2: Set random pointers
    temp = head;
    while (temp != nullptr) {
        if (temp->random)
            temp->next->random = temp->random->next;
        else
            temp->next->random = nullptr;
        temp = temp->next->next;
    }

    // Step 3: Separate the copied list from original
    temp = head;
    node* copyHead = head->next;
    while (temp != nullptr) {
        node* copyNode = temp->next;
        temp->next = copyNode->next; // restore original
        if (copyNode->next)
            copyNode->next = copyNode->next->next;
        else
            copyNode->next = nullptr;
        temp = temp->next;
    }

    return copyHead;
}

// Helper to print list (shows val and random->val)
void printLL(node* head) {
    while (head) {
        cout << head->val << " -> ";
        if (head->random)
            cout << head->random->val;
        else
            cout << "NULL";
        cout << endl;
        head = head->next;
    }
}

// Example usage
int main() {
    node* head = new node(1);
    head->next = new node(2);
    head->next->next = new node(3);
    head->random = head->next->next;       // 1->3
    head->next->random = head;             // 2->1
    head->next->next->random = head->next; // 3->2

    cout << "Original list:\n";
    printLL(head);

    node* copied = copy_LL(head);
    cout << "\nCopied list:\n";
    printLL(copied);

    return 0;
}
