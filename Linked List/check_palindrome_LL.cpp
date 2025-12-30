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


bool check_palindrome_brute(node*head){
    stack<int>st;
    node*temp=head;
    while(temp!=nullptr){
        st.push(temp->data);
        temp=temp->next;
    }
    temp=head;
    while(temp!=nullptr){
        if(temp->data!=st.top()) return false; 
        st.pop();
        temp=temp->next;
    }
    return true;
}

bool check_palindrome(node*head){
    node*slow=head,*fast=head;
    while(fast->next!=nullptr && fast->next->next!=nullptr){
        slow=slow->next;
        fast=fast->next->next;
    }
    node*newhead=reverse(slow->next);
    node*first=head,*second=newhead;
    while(second!=nullptr){
        if(first->data!=second->data){
            reverse(newhead);
            return false;
        }
        second=second->next;
        first=first->next;
    }
    reverse(newhead);
    return true;
}

// Utility: print list
void printList(node* head) {
    while (head != nullptr) {
        cout << head->data << " ";
        head = head->next;
    }
    cout << endl;
}

int main() {
    node* head = new node(1, new node(2, new node(3, new node(2, new node(1)))));

    cout << "Original list: ";
    printList(head);

    cout << "Is palindrome (brute)? " << (check_palindrome_brute(head) ? "Yes" : "No") << endl;
    cout << "Is palindrome (optimal)? " << (check_palindrome(head) ? "Yes" : "No") << endl;

    return 0;
}
