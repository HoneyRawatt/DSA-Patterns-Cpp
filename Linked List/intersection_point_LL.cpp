#include <iostream>
#include <unordered_set>
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

// Brute Force: O(n+m) time, O(n) space
node* intersection_point_brute(node* head1, node* head2) {
    unordered_set<node*> st;
    node* temp = head1;
    while (temp != nullptr) {
        st.insert(temp);
        temp = temp->next;
    }
    temp = head2;
    while (temp != nullptr) {
        if (st.find(temp) != st.end()) return temp;
        temp = temp->next;
    }
    return nullptr;
}

// Helper for better approach
node* collisionPoint(node* t1, node* t2, int d) {
    while (d--) {
        if (t2 == nullptr) return nullptr;
        t2 = t2->next;
    }
    while (t1 != nullptr && t2 != nullptr && t1 != t2) {
        t1 = t1->next;
        t2 = t2->next;
    }
    return t1;
}

// Better Approach: O(n+m) time, O(1) space
node* intersection_point_better(node* head1, node* head2) {
    node *t1 = head1, *t2 = head2;
    int n1 = 0, n2 = 0;
    while (t1 != nullptr) {
        n1++;
        t1 = t1->next;
    }
    while (t2 != nullptr) {
        n2++;
        t2 = t2->next;
    }
    if (n1 < n2) return collisionPoint(head1, head2, n2 - n1);
    else return collisionPoint(head2, head1, n1 - n2);
}

// Optimal Approach: Two pointer O(n+m) time, O(1) space
node* intersection_point(node* head1, node* head2) {
    if (head1 == nullptr || head2 == nullptr) return nullptr;
    node *t1 = head1, *t2 = head2;
    while (t1 != t2) {
        t1 = (t1 == nullptr) ? head2 : t1->next;
        t2 = (t2 == nullptr) ? head1 : t2->next;
    } 
    return t1; // either intersection node or nullptr
}
