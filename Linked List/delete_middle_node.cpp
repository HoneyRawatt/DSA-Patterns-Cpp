#include <iostream>
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

// ---------- Brute Force ----------
node* delete_middle_brute(node* head) {
    if (head == nullptr || head->next == nullptr) return nullptr;

    int cnt = 0;
    node* temp = head;
    while (temp != nullptr) {
        cnt++;
        temp = temp->next;
    }

    int mid = cnt / 2;
    temp = head;
    while (temp != nullptr) {
        mid--;
        if (mid == 0) {
            node* middle = temp->next;
            temp->next = temp->next->next;
            delete middle;
            break;
        }
        temp = temp->next;   
    }
    return head;
}

// ---------- Optimized ----------
node* delete_middle(node* head) {
    if (head == nullptr || head->next == nullptr) return nullptr;

    node* slow = head;
    node* fast = head;
    fast = fast->next->next;
    while (fast != nullptr && fast->next != nullptr) {
        slow = slow->next;
        fast = fast->next->next;
    }
    node* middle = slow->next;
    slow->next = slow->next->next;
    delete middle;
    return head;
}

// ---------- Helper ----------
void printList(node* head) {
    while (head != nullptr) {
        cout << head->data << " ";
        head = head->next;
    }
    cout << endl;
}

int main() {
    // Create linked list: 1 -> 2 -> 3 -> 4 -> 5
    node* head1 = new node(1, new node(2, new node(3, new node(4, new node(5)))));
    node* head2 = new node(1, new node(2, new node(3, new node(4, new node(5)))));

    cout << "Original List: ";
    printList(head1);

    head1 = delete_middle_brute(head1);
    cout << "After delete_middle_brute: ";
    printList(head1);

    head2 = delete_middle(head2);
    cout << "After delete_middle (optimized): ";
    printList(head2);

    return 0;
}
