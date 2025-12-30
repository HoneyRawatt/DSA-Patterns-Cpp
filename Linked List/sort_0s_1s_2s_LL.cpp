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

node* sort_ll_0s_1s_2s_brute(node* head) {
    if (head == NULL || head->next == NULL) return head;

    int cnt0 = 0, cnt1 = 0, cnt2 = 0;
    node* temp = head;

    // Count occurrences of 0s, 1s, 2s
    while (temp != NULL) {
        if (temp->data == 0) cnt0++;
        else if (temp->data == 1) cnt1++;
        else cnt2++;
        temp = temp->next;
    }

    // Rewrite the values in order
    temp = head;
    while (cnt0--) {
        temp->data = 0;
        temp = temp->next;
    }
    while (cnt1--) {
        temp->data = 1;
        temp = temp->next;
    }
    while (cnt2--) {
        temp->data = 2;
        temp = temp->next;
    }

    return head;
}

node* sort_ll_0s_1s_2s(node* head) {
    if (head == NULL || head->next == NULL) return head;

    node* zerohead = new node(-1), *zero = zerohead;
    node* onehead = new node(-1), *one = onehead;
    node* twohead = new node(-1), *two = twohead;

    node* temp = head;
    while (temp != NULL) {
        if (temp->data == 0) {
            zero->next = temp;
            zero = zero->next;
        } else if (temp->data == 1) {
            one->next = temp;
            one = one->next;
        } else {
            two->next = temp;
            two = two->next;
        }
        temp = temp->next;
    }

    // Connect three lists
    zero->next = (onehead->next) ? onehead->next : twohead->next;
    one->next = twohead->next;
    two->next = NULL;

    head = zerohead->next;

    // cleanup dummy nodes
    delete zerohead;
    delete onehead;
    delete twohead;

    return head;
}


void printList(node* head) {
    while (head != NULL) {
        cout << head->data << " ";
        head = head->next;
    }
    cout << endl;
}

int main() {
    node* head1 = new node(1, new node(0, new node(2, new node(1, new node(0, new node(2))))));
    node* head2 = new node(1, new node(0, new node(2, new node(1, new node(0, new node(2))))));

    cout << "Original list: ";
    printList(head1);

    head1 = sort_ll_0s_1s_2s_brute(head1);
    cout << "Sorted (Brute):   ";
    printList(head1);

    head2 = sort_ll_0s_1s_2s(head2);
    cout << "Sorted (Optimal): ";
    printList(head2);

    return 0;
}
