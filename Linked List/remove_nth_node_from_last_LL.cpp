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

// Brute Force Method: Count length, then remove (cnt - n)th node
node* remove_nth_node_brute(node* head, int n) {
    int cnt = 0;
    node* temp = head;
    while (temp != NULL) {
        cnt++;
        temp = temp->next;
    }

    // If head itself is to be removed
    if (cnt == n) {
        node* newhead = head->next;
        delete head;
        return newhead;
    }

    int res = cnt - n;
    temp = head;
    while (temp->next) {
        res--;
        if (res == 0) break;
        temp = temp->next;
    }

    node* deletenode = temp->next;
    temp->next = temp->next->next; // update link first
    delete deletenode;

    return head;
}

// Optimal Method: Two pointer approach
node* remove_nth_node(node* head, int n) {
    node* dummy = new node(-1, head); // dummy before head
    node* fast = dummy;
    node* slow = dummy;

    // Move fast n steps ahead
    for (int i = 0; i < n; i++) {
        fast = fast->next;
    }

    // Move until fast reaches last node
    while (fast->next != nullptr) {
        slow = slow->next;
        fast = fast->next;
    }

    // slow->next is the node to delete
    node* deletenode = slow->next;
    slow->next = slow->next->next;
    delete deletenode;

    node* newhead = dummy->next;
    delete dummy; // cleanup
    return newhead;
}

// Utility: Print list
void printList(node* head) {
    while (head != NULL) {
        cout << head->data << " ";
        head = head->next;
    }
    cout << endl;
}

int main() {
    // Create sample list
    node* head1 = new node(1, new node(2, new node(3, new node(4, new node(5)))));
    node* head2 = new node(1, new node(2, new node(3, new node(4, new node(5)))));

    cout << "Original list (for brute): ";
    printList(head1);
    head1 = remove_nth_node_brute(head1, 2); // remove 2nd node from end
    cout << "After brute removal: ";
    printList(head1);

    cout << "Original list (for optimal): ";
    printList(head2);
    head2 = remove_nth_node(head2, 2); // remove 2nd node from end
    cout << "After optimal removal: ";
    printList(head2);

    return 0;
}
