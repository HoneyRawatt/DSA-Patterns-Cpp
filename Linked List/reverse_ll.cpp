#include<iostream>
#include<stack>
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

// Brute Force (using stack)
node* reverse_brute(node* head) {
    if (!head) return head;

    stack<int> st;
    node* temp = head;

    // push all values into stack
    while (temp != NULL) {
        st.push(temp->data);
        temp = temp->next;
    }

    // assign back values in reverse order
    temp = head;
    while (temp != NULL) {
        temp->data = st.top();
        st.pop();
        temp = temp->next;
    }

    return head;
}

// Iterative (reversing links)
node* reverse(node* head) {
    node* prev = nullptr;
    node* curr = head;
    node* front = nullptr;

    while (curr != nullptr) {
        front = curr->next;  // save next
        curr->next = prev;   // reverse link
        prev = curr;         // move prev
        curr = front;        // move forward
    }

    return prev; // new head
}

// Recursive method
node* reverse_recursion(node* head) {
    if (head == NULL || head->next == NULL) return head;

    node* newhead = reverse_recursion(head->next);
    node* front = head->next;
    front->next = head;
    head->next = nullptr;
    return newhead;
}

// Utility: print list
void printList(node* head) {
    while (head != NULL) {
        cout << head->data << " ";
        head = head->next;
    }
    cout << endl;
}

// Main function to test
int main() {
    node* head = new node(1, new node(2, new node(3, new node(4, new node(5)))));

    cout << "Original list: ";
    printList(head);

    // Brute force
    head = reverse_brute(head);
    cout << "Reversed (Brute force): ";
    printList(head);

    // Iterative
    head = reverse(head);
    cout << "Reversed (Iterative): ";
    printList(head);

    // Recursive
    head = reverse_recursion(head);
    cout << "Reversed (Recursive): ";
    printList(head);

    return 0;
}
