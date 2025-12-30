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

// Convert array to linked list (child pointers only)
node* convertArrtoLL(vector<int>& arr) {
    if (arr.size() == 0) return nullptr;
    node* head = new node(arr[0]);
    node* temp = head;
    for (int i = 1; i < arr.size(); i++) {
        node* newnode = new node(arr[i]);
        temp->child = newnode;
        temp = temp->child;
    }
    return head;
}

// Brute force flattening
node* flatten_brute(node* head) {
    vector<int> arr;
    node* temp = head;
    while (temp != nullptr) {
        node* t2 = temp;
        while (t2 != nullptr) {
            arr.push_back(t2->val);
            t2 = t2->child;
        }
        temp = temp->next;
    }
    sort(arr.begin(), arr.end());
    head = convertArrtoLL(arr);
    return head;
}

// Merge two sorted linked lists (child pointers only)
node* merge2LL(node* list1, node* list2) {
    node* dummynode = new node(-1);
    node* res = dummynode;
    while (list1 != nullptr && list2 != nullptr) {
        if (list1->val < list2->val) {
            res->child = list1;
            res = list1;
            list1 = list1->child;
        } else {
            res->child = list2;
            res = list2;
            list2 = list2->child;
        }
        res->next = nullptr;
    }
    if (list1) res->child = list1;
    else res->child = list2;
    return dummynode->child;
}

// Optimal recursive flatten
node* flatten(node* head) {
    if (head == nullptr || head->next == nullptr) return head;
    node* mergehead = flatten(head->next);
    return merge2LL(head, mergehead);
}

// Print linked list (child direction)
void printLL(node* head) {
    while (head != nullptr) {
        cout << head->val << " ";
        head = head->child;
    }
    cout << endl;
}

int main() {
    // Create multilevel linked list:
    // head -> 5 -> 10 -> 19 -> 28
    // each having child list
    node* head = new node(5);
    head->next = new node(10);
    head->next->next = new node(19);
    head->next->next->next = new node(28);

    // attach child lists
    head->child = new node(7);
    head->child->child = new node(8);
    head->child->child->child = new node(30);

    head->next->child = new node(20);

    head->next->next->child = new node(22);
    head->next->next->child->child = new node(50);

    head->next->next->next->child = new node(35);
    head->next->next->next->child->child = new node(40);
    head->next->next->next->child->child->child = new node(45);

    cout << "Flattened Linked List (Optimal):\n";
    node* flatHead = flatten(head);
    printLL(flatHead);

    return 0;
}
