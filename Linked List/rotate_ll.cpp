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

// Utility to print the linked list
void printList(node* head) {
    while (head != nullptr) {
        cout << head->data << " ";
        head = head->next;
    }
    cout << endl;
}

// Find the k-th node (1-based indexing)
node* findNthnode(node* temp, int k) {
    int cnt = 1;
    while (temp != nullptr) {
        if (k == cnt) return temp;
        cnt++;
        temp = temp->next;
    }
    return temp;
}

// Rotate list by k positions
node* rotate_k(node* head, int k) {
    if (head == nullptr || head->next == nullptr || k == 0) return head;

    int len = 1;
    node* tail = head;
    while (tail->next != nullptr) {
        len++;
        tail = tail->next;
    }

    if (k % len == 0) return head; // no rotation

    k = k % len;
    tail->next = head; // make it circular

    node* newlastnode = findNthnode(head, len - k);
    head = newlastnode->next;
    newlastnode->next = nullptr; // break the circle

    return head;
}

int main() {
    // Build linked list: 1 -> 2 -> 3 -> 4 -> 5
    node* head = new node(1);
    head->next = new node(2);
    head->next->next = new node(3);
    head->next->next->next = new node(4);
    head->next->next->next->next = new node(5);

    cout << "Original list: ";
    printList(head);

    int k = 2;
    head = rotate_k(head, k);

    cout << "After rotating by " << k << ": ";
    printList(head);

    return 0;
}
