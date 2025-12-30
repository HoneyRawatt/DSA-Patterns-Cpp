#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class node {
public:
    int val;
    node* next;
    node* child;
    node(int val) {
        this->val = val;
        next = nullptr;
        child = nullptr;
    }
    node(int val, node* next, node* child) {
        this->val = val;
        this->next = next;
        this->child = child; 
    }
};

// Brute force sorting by array
node* sort_LL_brute(node* head) {
    vector<int> arr;
    node* temp = head;
    while (temp != nullptr) {
        arr.push_back(temp->val);
        temp = temp->next;
    }
    sort(arr.begin(), arr.end());
    int i = 0;
    temp = head;
    while (temp != nullptr) {
        temp->val = arr[i++];
        temp = temp->next;
    }
    return head;
}

// Merge two sorted linked lists
node* merge(node* head1, node* head2) {
    node* t1 = head1;
    node* t2 = head2;

    node* dummy = new node(-1);
    node* temp = dummy;

    while (t1 && t2) {
        if (t1->val < t2->val) {
            temp->next = t1;
            temp = t1;
            t1 = t1->next;
        } else {
            temp->next = t2;
            temp = t2;
            t2 = t2->next;
        }
    }

    if (t1) temp->next = t1;
    else temp->next = t2;

    return dummy->next;
}

// Find middle of linked list
node* findmiddle(node* head) {
    node* slow = head;
    node* fast = head;
    while (fast->next != nullptr && fast->next->next != nullptr) {
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow;
}

// Merge sort on linked list
node* merge_sort(node* head) {
    if (head == nullptr || head->next == nullptr) return head;

    node* middle = findmiddle(head);
    node* righthead = middle->next;
    middle->next = nullptr; // split list

    node* lefthead = merge_sort(head);
    righthead = merge_sort(righthead);

    return merge(lefthead, righthead);
}

// Utility: print linked list
void printLL(node* head) {
    while (head) {
        cout << head->val << " ";
        head = head->next;
    }
    cout << endl;
}

// Main function to test
int main() {
    node* head = new node(4);
    head->next = new node(2);
    head->next->next = new node(1);
    head->next->next->next = new node(3);

    cout << "Original list: ";
    printLL(head);

    head = merge_sort(head);

    cout << "Sorted list: ";
    printLL(head);

    return 0;
}
