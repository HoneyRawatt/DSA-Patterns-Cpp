#include<iostream>
#include<vector>
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

node* convertarrtoll(vector<int> arr) {
    if (arr.empty()) return nullptr;
    node* head = new node(arr[0]);
    node* mover = head;
    for (int i = 1; i < arr.size(); i++) {
        mover->next = new node(arr[i]);
        mover = mover->next;
    }
    return head;
}

void display(node* head) {
    if (head == nullptr) {
        cout << "linked list is empty" << endl;
        return;
    }
    node* current = head;
    while (current != nullptr) {
        cout << current->data << " ";
        current = current->next;
    }
    cout << endl;
}

int lengthofll(node* head) {
    int cnt = 0;
    node* temp = head;
    while (temp != nullptr) {
        cnt++;
        temp = temp->next;
    }
    return cnt;
}

bool Checkifpersent(node* head, int val) {
    node* temp = head;
    while (temp != nullptr) {
        if (temp->data == val) return true;
        temp = temp->next;
    }
    return false;
}

node* deletehead(node* head) {
    if (head == nullptr) return head;
    node* temp = head;
    head = head->next;
    delete temp;
    return head;
}

node* deletelast(node* head) {
    if (head == nullptr || head->next == nullptr) {
        delete head;
        return nullptr;
    }
    node* temp = head;
    while (temp->next->next != nullptr) {
        temp = temp->next;
    }
    delete temp->next;
    temp->next = nullptr;
    return head;
}

node* deleteKth(node* head, int k) {
    if (head == nullptr) return head;
    if (k == 1) return deletehead(head);

    int cnt = 0;
    node* temp = head;
    node* prev = nullptr;

    while (temp != nullptr) {
        cnt++;
        if (cnt == k) {
            if (prev != nullptr) {
                prev->next = temp->next;
                delete temp;
            }
            break;
        }
        prev = temp;
        temp = temp->next;
    }
    return head;
}

node* deleteByValue(node* head, int val) {
    if (head == nullptr) return head;
    if (head->data == val) return deletehead(head);

    node* temp = head;
    node* prev = nullptr;

    while (temp != nullptr) {
        if (temp->data == val) {
            if (prev != nullptr) {
                prev->next = temp->next;
                delete temp;
            }
            break;
        }
        prev = temp;
        temp = temp->next;
    }
    return head;
}

node* inserthead(node* head, int val) {
    return new node(val, head);
}

node* inserttail(node* head, int val) {
    if (head == NULL) return new node(val);

    node* temp = head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    node* newnode = new node(val);
    temp->next = newnode;
    return head;
}

node* insertposition(node* head, int val, int pos) {
    if (head == NULL) {
        if (pos == 1) return new node(val);
        else return head;
    }
    if (pos == 1) return new node(val, head);

    int cnt = 1;
    node* temp = head;
    while (temp != NULL) {
        if (cnt == pos - 1) {
            node* x = new node(val, temp->next);
            temp->next = x;
            break;
        }
        cnt++;
        temp = temp->next;
    }
    return head;
}

node* insertbeforeval(node* head, int el, int val) {
    if (head == NULL) return head;
    if (head->data == val) return new node(el, head);

    node* temp = head;
    while (temp->next != NULL) {
        if (temp->next->data == val) {
            node* x = new node(el, temp->next);
            temp->next = x;
            break;
        }
        temp = temp->next;
    }
    return head;
}

int main() {
    vector<int> arr = {2, 5, 0, 7};
    node* head = convertarrtoll(arr);

    cout << "Linked List created from array: ";
    display(head);

    cout << "Length of LL: " << lengthofll(head) << endl;
    cout << "Check if element is present: " 
         << (Checkifpersent(head, 5) ? "YES" : "NO") << endl;

    head = deleteKth(head, 3);
    cout << "After deleting 3rd node: ";
    display(head);

    head = deleteByValue(head, 7);
    cout << "After deleting node with value 7: ";
    display(head);

    head = inserthead(head, 10);
    cout << "After inserting 10 at head: ";
    display(head);

    head = inserttail(head, 99);
    cout << "After inserting 99 at tail: ";
    display(head);

    head = insertposition(head, 77, 3);
    cout << "After inserting 77 at position 3: ";
    display(head);

    head = insertbeforeval(head, 88, 5);
    cout << "After inserting 88 before 5: ";
    display(head);

    return 0;
}
