#include <iostream>
#include <vector>
#include <algorithm>
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

// helper: insert node at end
node* insertEnd(node* head, int val) {
    if (head == nullptr) return new node(val);
    node* temp = head;
    while (temp->next != nullptr) temp = temp->next;
    temp->next = new node(val);
    return head;
}

// helper: print linked list
void printList(node* head) {
    while (head != nullptr) {
        cout << head->data << " ";
        head = head->next;
    }
    cout << endl;
}

// helper: convert array to linked list
node* convertArrToList(vector<int>& arr) {
    if (arr.empty()) return nullptr;
    node* head = new node(arr[0]);
    node* temp = head;
    for (int i = 1; i < arr.size(); i++) {
        temp->next = new node(arr[i]);
        temp = temp->next;
    }
    return head;
}

// brute force merge: add all elements into array, sort, build new list
node* merge_two_sorted_ll_brute(node* head1, node* head2) {
    vector<int> arr;

    // push list1 elements
    node* t1 = head1;
    while (t1 != nullptr) {
        arr.push_back(t1->data);
        t1 = t1->next;
    }

    // push list2 elements
    node* t2 = head2;
    while (t2 != nullptr) {
        arr.push_back(t2->data);
        t2 = t2->next;
    }

    // sort array
    sort(arr.begin(), arr.end());

    // convert to new linked list
    return convertArrToList(arr);
}

node* merge_two_sorted_ll(node* head1, node* head2) {
    node* t1 = head1;
    node* t2 = head2;

    node* dnode = new node(-1); // dummy node
    node* temp = dnode;

    while (t1 && t2) {
        if (t1->data < t2->data) {
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

    return dnode->next;
}

int main() {
    node* head1 = nullptr;
    node* head2 = nullptr;

    // List 1: 1 -> 3 -> 5
    head1 = insertEnd(head1, 1);
    head1 = insertEnd(head1, 3);
    head1 = insertEnd(head1, 5);

    // List 2: 2 -> 4 -> 6
    head2 = insertEnd(head2, 2);
    head2 = insertEnd(head2, 4);
    head2 = insertEnd(head2, 6);

    cout << "List 1: ";
    printList(head1);
    cout << "List 2: ";
    printList(head2);

    node* merged = merge_two_sorted_ll_brute(head1, head2);

    cout << "Merged List (Brute Force): ";
    printList(merged);

    merged = merge_two_sorted_ll(head1, head2);

    cout << "Merged List: ";
    printList(merged);

    return 0;
}
