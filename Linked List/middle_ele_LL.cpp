#include <iostream>
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

// Brute force: count length, then go to middle
node* middle_brute(node* head) {
    if (head == nullptr) return nullptr;

    int cnt = 0;
    node* temp = head;
    while (temp != nullptr) {
        cnt++;
        temp = temp->next;
    }

    int mid = cnt / 2; // for 0-based index middle
    temp = head;
    while (mid--) {
        temp = temp->next;
    }
    return temp;
}

// Optimal: slow–fast pointer method
node* middle(node* head) {
    if (head == nullptr) return nullptr;

    node* slow = head;
    node* fast = head;
    while (fast != nullptr && fast->next != nullptr) {
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow;
}

int main() {
    node* head = new node(1, new node(2, new node(3, new node(4, new node(5)))));
    
    node* mid1 = middle_brute(head);
    cout << "Middle (brute): " << mid1->data << endl;

    node* mid2 = middle(head);
    cout << "Middle (optimal): " << mid2->data << endl;

    return 0;
}
