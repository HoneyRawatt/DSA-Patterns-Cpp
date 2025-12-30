#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
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

// Helper: convert array to linked list
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

// Brute-force: put all elements in array, sort, then convert to list
node* merge_k_sorted_ll_brute(vector<node*> lists) {
    vector<int> arr;
    for (int i = 0; i < lists.size(); i++) {
        node* temp = lists[i];
        while (temp != nullptr) {
            arr.push_back(temp->data);
            temp = temp->next;
        }
    }
    sort(arr.begin(), arr.end());
    return convertArrToList(arr);
}

// Merge two sorted lists
node* merge_two_sorted_ll(node* head1, node* head2) {
    node* t1 = head1;
    node* t2 = head2;

    node* dnode = new node(-1);
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

// Better: merge lists one by one using merge_two_sorted_ll
node* merge_k_sorted_ll_better(vector<node*> lists) {
    if (lists.empty()) return nullptr;
    node* head = lists[0];
    for (int i = 1; i < lists.size(); i++) {
        head = merge_two_sorted_ll(head, lists[i]);
    }
    return head;
}

// Optimal: using min-heap
node* merge_k_sorted_ll(vector<node*> lists) {
    priority_queue<
    pair<int, node*>,               // type of elements
    vector<pair<int, node*>>,       // underlying container
    greater<pair<int, node*>>       // comparator
> pq;


    for (int i = 0; i < lists.size(); i++) {
        if (lists[i]) pq.push({lists[i]->data, lists[i]});
    }

    node* dummynode = new node(-1);
    node* temp = dummynode;

    while (!pq.empty()) {
        auto it = pq.top();
        pq.pop();
        if (it.second->next) pq.push({it.second->next->data, it.second->next});
        temp->next = it.second;
        temp = temp->next;
    }

    return dummynode->next;
}

// Helper: print list
void printList(node* head) {
    while (head) {
        cout << head->data << " ";
        head = head->next;
    }
    cout << endl;
}

// Helper: insert at end
node* insertEnd(node* head, int val) {
    if (!head) return new node(val);
    node* temp = head;
    while (temp->next) temp = temp->next;
    temp->next = new node(val);
    return head;
}

int main() {
    vector<node*> lists(3, nullptr);

    // List 1: 1 -> 4 -> 7
    lists[0] = insertEnd(lists[0], 1);
    lists[0] = insertEnd(lists[0], 4);
    lists[0] = insertEnd(lists[0], 7);

    // List 2: 2 -> 5 -> 8
    lists[1] = insertEnd(lists[1], 2);
    lists[1] = insertEnd(lists[1], 5);
    lists[1] = insertEnd(lists[1], 8);

    // List 3: 3 -> 6 -> 9
    lists[2] = insertEnd(lists[2], 3);
    lists[2] = insertEnd(lists[2], 6);
    lists[2] = insertEnd(lists[2], 9);

    cout << "Brute Force Merge: ";
    node* merged_brute = merge_k_sorted_ll_brute(lists);
    printList(merged_brute);

    cout << "Better Merge: ";
    node* merged_better = merge_k_sorted_ll_better(lists);
    printList(merged_better);

    cout << "Optimal Merge (Heap): ";
    node* merged_optimal = merge_k_sorted_ll(lists);
    printList(merged_optimal);

    return 0;
}
