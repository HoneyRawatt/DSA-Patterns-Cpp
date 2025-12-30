#include<iostream>
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

node* addtwonumbers(node* head1, node* head2) {
    node* temp1 = head1, * temp2 = head2;
    node* dummynode = new node(-1);
    node* curr = dummynode;
    int carry = 0;
    
    while (temp1 != NULL || temp2 != NULL) {
        int sum = carry;
        if (temp1) sum += temp1->data;
        if (temp2) sum += temp2->data;
        
        node* newnode = new node(sum % 10);
        carry = sum / 10;
        curr->next = newnode;
        curr = curr->next;
        
        if (temp1) temp1 = temp1->next;
        if (temp2) temp2 = temp2->next;
    }
    
    if (carry) {
        node* newnode = new node(carry);
        curr->next = newnode;
    }
    return dummynode->next;
}

// helper function to insert at end
void insert(node*& head, int val) {
    if (!head) {
        head = new node(val);
        return;
    }
    node* temp = head;
    while (temp->next) temp = temp->next;
    temp->next = new node(val);
}

// helper function to print list
void printlist(node* head) {
    while (head) {
        cout << head->data;
        if (head->next) cout << " -> ";
        head = head->next;
    }
    cout << endl;
}

int main() {
    node* head1 = nullptr;
    node* head2 = nullptr;
    
    // Example: number 342 (2->4->3)
    insert(head1, 2);
    insert(head1, 4);
    insert(head1, 3);
    
    // Example: number 465 (5->6->4)
    insert(head2, 5);
    insert(head2, 6);
    insert(head2, 4);
    
    cout << "First number: ";
    printlist(head1);
    cout << "Second number: ";
    printlist(head2);
    
    node* result = addtwonumbers(head1, head2);
    
    cout << "Sum: ";
    printlist(result);  // Expected o
