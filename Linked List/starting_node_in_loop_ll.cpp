#include <iostream>
#include <map>
using namespace std;

class node {
public:
    int data;
    node* next;
    node(int val) {
        data = val;
        next = nullptr;
    }
    node(int val, node* next) {
        data = val;
        this->next = next; 
    }
};

// Brute force using map
node* starting_node_loop_brute(node* head) {
    map<node*, int> mpp;  
    node* temp = head;
    while (temp != nullptr) {
        if (mpp.find(temp) != mpp.end()) 
            return temp;   // loop start
        mpp[temp] = 1;
        temp = temp->next;
    }
    return nullptr;  // no loop
}

// Optimized (Floyd’s Cycle detection)
node* starting_node_loop(node* head) {
    node* slow = head;
    node* fast = head;
    while (fast != nullptr && fast->next != nullptr) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) {   // loop detected
            slow = head;
            while (slow != fast) {
                slow = slow->next;
                fast = fast->next;
            }
            return slow; // start of loop
        }
    }
    return nullptr; // no loop
}

int main() {
    // Create nodes
    node* head = new node(1);
    head->next = new node(2);
    head->next->next = new node(3);
    head->next->next->next = new node(4);
    head->next->next->next->next = new node(5);

    // Create a loop: connect node 5 -> node 3
    head->next->next->next->next->next = head->next->next;

    // Test brute force
    node* loopStartBrute = starting_node_loop_brute(head);
    if (loopStartBrute) 
        cout << "Brute: Loop starts at node with value " << loopStartBrute->data << endl;
    else 
        cout << "Brute: No loop found" << endl;

    // Test optimized
    node* loopStartOpt = starting_node_loop(head);
    if (loopStartOpt) 
        cout << "Optimized: Loop starts at node with value " << loopStartOpt->data << endl;
    else 
        cout << "Optimized: No loop found" << endl;

    return 0;
}
