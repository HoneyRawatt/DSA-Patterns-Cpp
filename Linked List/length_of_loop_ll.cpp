#include <iostream>
#include <map>
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

int length_loop_brute(node*head){
    map<node*,int>mpp;
    node*temp=head;
    int timer=1;
    while(temp!=nullptr){
        if(mpp.find(temp)!=mpp.end()){
            int value=mpp[temp];
            return (timer-value);
        }
        mpp[temp]=timer;
        timer++;
        temp=temp->next;
    }
    return 0;
}

int findlength(node*slow,node*fast){
    int cnt=1;
    fast=fast->next;
    while(fast!=slow){
        cnt++;
        fast=fast->next;
    }
    return cnt;
}
int length_loop(node* head) {
    node* slow = head;
    node* fast = head;
    while (fast != nullptr && fast->next != nullptr) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) return findlength(slow,fast); // loop found
    }
    return 0; // no loop
} 

// ---------------- Test ----------------
int main() {
    node* head = new node(1);
    head->next = new node(2);
    head->next->next = new node(3);
    head->next->next->next = new node(4);
    head->next->next->next->next = head->next; // loop (2->3->4->2)

    cout << "Brute force loop length: " << length_loop_brute(head) << endl;
    cout << "Floyd loop length: " << length_loop(head) << endl;

    return 0;
}