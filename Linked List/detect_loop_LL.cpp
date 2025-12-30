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

// Brute force: use map to mark visited nodes
bool detect_loop_brute(node* head) {
    map<node*, int> mpp;
    node* temp = head;
    while (temp != nullptr) {
        if (mpp.find(temp) != mpp.end()) {
            return true; // loop found
        }
        mpp[temp] = 1;
        temp = temp->next;
    }
    return false; // no loop
}

// Optimal: Floyd's cycle detection (slow & fast pointers)
bool detect_loop(node* head) {
    node* slow = head;
    node* fast = head;
    while (fast != nullptr && fast->next != nullptr) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) return true; // loop found
    }
    return false; // no loop
}

int main() {
    node* head = new node(1);
    head->next = new node(2);
    head->next->next = new node(3);
    head->next->next->next = new node(4);
    head->next->next->next->next = head->next; // create loop

    cout << "Brute: " << (detect_loop_brute(head) ? "Loop found" : "No loop") << endl;
    cout << "Optimal: " << (detect_loop(head) ? "Loop found" : "No loop") << endl;

    return 0;
}
