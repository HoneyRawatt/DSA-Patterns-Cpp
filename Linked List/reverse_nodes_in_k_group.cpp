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

// helper: get k-th node from current node
node* getKnode(node* temp, int k) {
    while (temp != nullptr && k > 1) {
        k--;
        temp = temp->next;
    }
    return temp;
}

// helper: reverse a linked list segment
void reverseList(node* head) {
    node* prev = nullptr;
    node* curr = head;
    while (curr != nullptr) {
        node* nxt = curr->next;
        curr->next = prev;
        prev = curr;
        curr = nxt;
    }
}

// main function: reverse in groups of k
node* K_reverse(node* head, int k) {
    node* temp = head;
    node* prevnode = nullptr;

    while (temp != nullptr) {
        node* kthnode = getKnode(temp, k);
        if (kthnode == nullptr) {
            if (prevnode) prevnode->next = temp;
            break;
        }

        node* nextnode = kthnode->next;
        kthnode->next = nullptr;

        reverseList(temp);

        if (temp == head) {
            head = kthnode;
        } else {
            prevnode->next = kthnode;
        }

        prevnode = temp;
        temp = nextnode;
    }
    return head;
}

// utility: print linked list
void printList(node* head) {
    while (head != nullptr) {
        cout << head->data << " ";
        head = head->next;
    }
    cout << endl;
}

// driver
int main() {
    node* head = new node(1);
    head->next = new node(2);
    head->next->next = new node(3);
    head->next->next->next = new node(4);
    head->next->next->next->next = new node(5);

    cout << "Original list: ";
    printList(head);

    head = K_reverse(head, 2);

    cout << "After reversing in groups of 2: ";
    printList(head);

    return 0;
}
