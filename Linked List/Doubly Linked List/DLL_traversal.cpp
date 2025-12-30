#include<iostream>
#include<vector>
using namespace std;

class node {
public:
    int data;
    node* prev;
    node* next;
    node(int val, node* next, node* prev) {
        data = val;
        this->prev = prev;
        this->next = next;
    }
    node(int val) {
        data = val;
        next = nullptr;
        prev = nullptr;
    }
};

// Convert array to doubly linked list
node* convertArr(vector<int> arr) {
    node* head = new node(arr[0]);
    node* prev = head;
    for (int i = 1; i < arr.size(); i++) {
        node* temp = new node(arr[i]);
        prev->next = temp;
        temp->prev = prev;
        prev = temp;
    }
    return head;
}

// Delete head node
node* deletehead(node* head) {
    if (head == nullptr) return nullptr;

    node* temp = head;
    head = head->next;

    if (head != nullptr) head->prev = nullptr;
    temp->next = nullptr;

    delete temp;
    return head;
}

// Delete tail node
node* deletetail(node* head) {
    if (head == nullptr) return nullptr;
    if (head->next == nullptr) {
        delete head;
        return nullptr;
    }

    node* tail = head;
    while (tail->next != nullptr) tail = tail->next;

    node* prev = tail->prev;
    prev->next = nullptr;
    tail->prev = nullptr;

    delete tail;
    return head;
}

// Delete given node pointer
node* deltetenode(node* head, node* temp) {
    if (temp == nullptr) return head;

    node* prev = temp->prev;
    node* front = temp->next;

    if (prev == nullptr && front == nullptr) { // only one node
        delete temp;
        return nullptr;
    }
    if (prev == nullptr) { // head
        head = head->next;
        head->prev = nullptr;
        temp->next = nullptr;
        delete temp;
        return head;
    }
    if (front == nullptr) { // tail
        prev->next = nullptr;
        temp->prev = nullptr;
        delete temp;
        return head;
    }

    // middle node
    prev->next = front;
    front->prev = prev;

    temp->next = temp->prev = nullptr;
    delete temp;
    return head;
}

// Delete kth node (1-based index)
node* delete_kth_node(node* head, int k) {
    if (head == nullptr) return nullptr;

    int cnt = 1;
    node* temp = head;
    while (temp != nullptr && cnt < k) {
        temp = temp->next;
        cnt++;
    }

    if (temp == nullptr) return head; // k > length
    return deltetenode(head, temp);
}

// Insert at head
node* insertHead(node* head, int val) {
    node* newNode = new node(val);
    if (head == nullptr) return newNode;

    newNode->next = head;
    head->prev = newNode;
    return newNode;
}

// Insert at tail
node* insertTail(node* head, int val) {
    node* newNode = new node(val);
    if (head == nullptr) return newNode;

    node* tail = head;
    while (tail->next != nullptr) tail = tail->next;

    tail->next = newNode;
    newNode->prev = tail;
    return head;
}

// Insert at kth position (1-based index)
node* insertAtK(node* head, int k, int val) {
    if (k <= 1) return insertHead(head, val);

    int cnt = 1;
    node* temp = head;
    while (temp != nullptr && cnt < k - 1) {
        temp = temp->next;
        cnt++;
    }

    if (temp == nullptr || temp->next == nullptr) {
        return insertTail(head, val);
    }

    node* newNode = new node(val);
    node* front = temp->next;

    temp->next = newNode;
    newNode->prev = temp;
    newNode->next = front;
    front->prev = newNode;

    return head;
}

// Insert before a given node
node* insertBefore(node* head, node* temp, int val) {
    if (temp == nullptr) return head;

    if (temp->prev == nullptr) {
        return insertHead(head, val);
    }

    node* newNode = new node(val);
    node* prev = temp->prev;

    prev->next = newNode;
    newNode->prev = prev;

    newNode->next = temp;
    temp->prev = newNode;

    return head;
}

// Insert after a given node
node* insertAfter(node* head, node* temp, int val) {
    if (temp == nullptr) return head;

    node* newNode = new node(val);
    node* front = temp->next;

    temp->next = newNode;
    newNode->prev = temp;
    newNode->next = front;

    if (front != nullptr) front->prev = newNode;

    return head;
}

// Print list forward
void print(node* head) {
    node* temp = head;
    while (temp != nullptr) {
        cout << temp->data << " ";
        if (temp->next == nullptr) break; // stop at tail
        temp = temp->next;
    }
    cout << endl;
}

// Print list in reverse (from tail)
void printReverse(node* head) {
    if (head == nullptr) return;

    node* tail = head;
    while (tail->next != nullptr) tail = tail->next;

    while (tail != nullptr) {
        cout << tail->data << " ";
        tail = tail->prev;
    }
    cout << endl;
}

node* reverse(node* head) {
    if (head == nullptr || head->next == nullptr) return head;

    node* curr = head;
    node* last = nullptr;

    while (curr != nullptr) {
        last = curr->prev;        // store prev
        curr->prev = curr->next;  // swap
        curr->next = last;
        curr = curr->prev;        // move to next node (which is prev now)
    }

    // last now points to the old head’s prev (i.e., new head)
    if (last != nullptr) {
        head = last->prev;
    }
    return head;
}

int main() {
    vector<int> arr = {12, 2, 3, 4, 6};
    node* head = convertArr(arr);

    cout << "Original list: ";
    print(head);

    head = deletehead(head);
    cout << "After deleting head: ";
    print(head);

    head = deletetail(head);
    cout << "After deleting tail: ";
    print(head);

    head = delete_kth_node(head, 2);
    cout << "After deleting 2nd node: ";
    print(head);

    // --- Now test insertions ---
    head = insertHead(head, 99);
    cout << "After inserting 99 at head: ";
    print(head);

    head = insertTail(head, 77);
    cout << "After inserting 77 at tail: ";
    print(head);

    head = insertAtK(head, 2, 55);
    cout << "After inserting 55 at pos 2: ";
    print(head);

    head = insertBefore(head, head->next, 44); // before 2nd node
    cout << "After inserting 44 before 2nd node: ";
    print(head);

    head = insertAfter(head, head->next, 11); // after 2nd node
    cout << "After inserting 11 after 2nd node: ";
    print(head);

    cout << "List in reverse: ";
    printReverse(head);

    cout << "List in reverse: ";
    Reverse(head);
    

    return 0;
}
