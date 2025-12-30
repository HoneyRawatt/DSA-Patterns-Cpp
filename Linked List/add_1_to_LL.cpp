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

// Reverse linked list (iterative)
node* reverse(node* head) {
    node* prev = nullptr;
    node* curr = head;
    node* front = nullptr;
    while (curr != nullptr) {
        front = curr->next;
        curr->next = prev;
        prev = curr;
        curr = front;
    }
    return prev;
}

// ---------------- Iterative method to add 1 ----------------
node* add_1_iterative(node* head) {
    head = reverse(head);
    node* temp = head;
    int carry = 1;

    while (temp != NULL) {
        temp->data += carry;
        if (temp->data < 10) {
            carry = 0;
            break;
        } else {
            temp->data = 0;
            carry = 1;
        }
        if (temp->next == NULL) break;
        temp = temp->next;
    }

    if (carry == 1) {
        node*newnode = new node(1);
        head=reverse(head);
        newnode->next=head;
        return newnode;
    }

    head = reverse(head);
    return head;
}

// ---------------- Recursive helper ----------------
int helper_add(node* temp) {
    if (temp == NULL) return 1;

    int carry = helper_add(temp->next);
    temp->data += carry;
    if (temp->data < 10) return 0;

    temp->data = 0;
    return 1;
}

// ---------------- Recursive method to add 1 ----------------
node* add_1_recursive(node* head) {
    int carry = helper_add(head);
    if (carry == 1) {
        node* newnode = new node(1, head);
        return newnode;
    }
    return head;
}

// Utility to print linked list
void printList(node* head) {
    while (head != nullptr) {
        cout << head->data << " ";
        head = head->next;
    }
    cout << endl;
}

// ---------------- Main Function ----------------
int main() {
    node* head1 = new node(1, new node(2, new node(9,new node(9,new node(9)))));
    cout << "Original number: ";
    printList(head1);

    node* addedIter = add_1_iterative(head1);
    cout << "After adding 1 (iterative): ";
    printList(addedIter);

    node* head2 = new node(1, new node(2, new node(9,new node(9,new node(9)))));
    node* addedRec = add_1_recursive(head2);
    cout << "After adding 1 (recursive): ";
    printList(addedRec);
    return 0;
}
