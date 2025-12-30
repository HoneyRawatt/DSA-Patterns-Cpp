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

node* remove_duplicate_from_Sorted_DLL(node* head) {
    node* temp = head;
    while (temp != nullptr && temp->next != nullptr) {
        node* nextnode = temp->next;
        while (nextnode != nullptr && nextnode->data == temp->data) {
            node* dupli = nextnode;
            nextnode = nextnode->next;
            delete dupli;  // use delete instead of free
        }
        temp->next = nextnode;
        if (nextnode) nextnode->prev = temp;
        temp = temp->next;
    }
    return head;
}

// Helper to print DLL
void printDLL(node* head) {
    while(head != nullptr) {
        cout << head->data << " ";
        head = head->next;
    }
    cout << endl;
}

// Main function
int main() {
    node* head = new node(1);
    head->next = new node(2); head->next->prev = head;
    head->next->next = new node(2); head->next->next->prev = head->next;
    head->next->next->next = new node(3); head->next->next->next->prev = head->next->next;
    head->next->next->next->next = new node(3); head->next->next->next->next->prev = head->next->next->next;

    cout << "Original DLL: ";
    printDLL(head);

    head = remove_duplicate_from_Sorted_DLL(head);

    cout << "After removing duplicates: ";
    printDLL(head);

    return 0;
}
