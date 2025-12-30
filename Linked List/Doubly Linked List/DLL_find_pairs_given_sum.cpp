#include <iostream>
#include <vector>
using namespace std;

class node {
public:
    int data;
    node* prev;
    node* next;
    node(int val) {
        data = val;
        next = nullptr;
        prev = nullptr;
    }
};

// Brute-force approach
vector<pair<int,int>> find_pairs_with_given_sum_brute(node* head, int sum) {
    node* temp1 = head;
    vector<pair<int,int>> res;
    while(temp1 != nullptr) {
        node* temp2 = temp1->next;
        while(temp2 != nullptr && temp1->data + temp2->data <= sum) {
            if(temp1->data + temp2->data == sum) {
                res.push_back({temp1->data, temp2->data});
            }
            temp2 = temp2->next;
        }
        temp1 = temp1->next;
    }
    return res;
}

// Helper to find tail
node* findtail(node* head) {
    node* temp = head;
    while(temp->next != nullptr) temp = temp->next;
    return temp;
}

// Optimal approach using two pointers
vector<pair<int,int>> find_pairs_with_given_sum(node* head, int sum) {
    node* left = head;
    node* right = findtail(head);
    vector<pair<int,int>> res;

    while(left != nullptr && right != nullptr && left != right && left->prev != right) {
        int s = left->data + right->data;
        if(s < sum) left = left->next;
        else if(s > sum) right = right->prev;
        else {
            res.push_back({left->data, right->data});
            left = left->next;
            right = right->prev;
        }
    }
    return res;
}

// Helper function to print vector of pairs
void printPairs(const vector<pair<int,int>>& pairs) {
    for(auto p : pairs) {
        cout << "(" << p.first << "," << p.second << ") ";
    }
    cout << endl;
}

int main() {
    // Create a sorted doubly linked list: 1 <-> 2 <-> 3 <-> 4 <-> 5
    node* head = new node(1);
    head->next = new node(2); head->next->prev = head;
    head->next->next = new node(3); head->next->next->prev = head->next;
    head->next->next->next = new node(4); head->next->next->next->prev = head->next->next;
    head->next->next->next->next = new node(5); head->next->next->next->next->prev = head->next->next->next;

    int sum = 5;

    cout << "Brute-force pairs with sum " << sum << ": ";
    vector<pair<int,int>> brutePairs = find_pairs_with_given_sum_brute(head, sum);
    printPairs(brutePairs);

    cout << "Optimal pairs with sum " << sum << ": ";
    vector<pair<int,int>> optimalPairs = find_pairs_with_given_sum(head, sum);
    printPairs(optimalPairs);

    return 0;
}
