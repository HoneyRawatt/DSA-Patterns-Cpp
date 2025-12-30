#include <iostream>
using namespace std;

class node {
public:
    int data;
    node* prev;
    node* next;
    node(int val) {
        data = val;
        next = nullptr;
        prev = nullptr;
    }
};

// Your function with minor fix: use temp->data instead of temp->val
node* Delete_all_occurence_of_key(node* head, int key) {
    node* temp = head;
    while (temp != nullptr) {
        if (temp->data == key) {
            node* nextnode = temp->next;
            node* prevnode = temp->prev;

            if (prevnode) prevnode->next = nextnode;
            if (nextnode) nextnode->prev = prevnode;

            if (temp == head) head = nextnode;

            delete temp;
            temp = nextnode;
        } else {
            temp = temp->next;
        }
    }
    return head;
}

// Function to print the list
void printList(node* head) {
    node* temp = head;
    while (temp != nullptr) {
        cout << temp->data << " ";
        temp = temp->next;
    }
    cout << endl;
}

int main() {
    // Creating doubly linked list: 1 <-> 2 <-> 3 <-> 2 <-> 4
    node* head = new node(1);
    head->next = new node(2); head->next->prev = head;
    head->next->next = new node(3); head->next->next->prev = head->next;
    head->next->next->next = new node(2); head->next->next->next->prev = head->next->next;
    head->next->next->next->next = new node(4); head->next->next->next->next->prev = head->next->next->next;

    cout << "Original list: ";
    printList(head);

    int key = 2;
    head = Delete_all_occurence_of_key(head, key);

    cout << "List after deleting all occurrences of " << key << ": ";
    printList(head);

    return 0;
}
