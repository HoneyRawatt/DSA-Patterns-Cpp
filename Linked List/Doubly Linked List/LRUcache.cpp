#include <iostream>
#include <map>
using namespace std;

class Node {
public:
    int key, val;
    Node* next;
    Node* prev;

    Node(int key, int val) {
        this->key = key;
        this->val = val;
        next = nullptr;
        prev = nullptr;
    }
};

class LRUCache {
public:
    map<int, Node*> mpp;
    int capacity;
    Node* head;
    Node* tail;

    // ✅ Constructor
    LRUCache(int capacity) {
        this->capacity = capacity;
        mpp.clear();
        head = new Node(-1, -1);
        tail = new Node(-1, -1);
        head->next = tail;
        tail->prev = head;
    }

    // ✅ Delete node from linked list
    void DeleteNode(Node* node) {
        Node* prevnode = node->prev;
        Node* afternode = node->next;
        prevnode->next = afternode;
        afternode->prev = prevnode;
    }

    // ✅ Insert node right after head
    void InsertHead(Node* node) {
        Node* currafterhead = head->next;
        head->next = node;
        node->next = currafterhead;
        currafterhead->prev = node;
        node->prev = head;
    }

    // ✅ Get value (and move to front)
    int get(int key) {
        if (mpp.find(key) == mpp.end())
            return -1;

        Node* node = mpp[key];
        int value = node->val;
        DeleteNode(node);
        InsertHead(node);
        return value;
    }

    // ✅ Put key-value
    void put(int key, int value) {
        if (mpp.find(key) != mpp.end()) {
            // Key already exists → update value and move to front
            Node* node = mpp[key];
            node->val = value;
            DeleteNode(node);
            InsertHead(node);
        } else {
            // Key doesn’t exist → check capacity
            if (mpp.size() == capacity) {
                Node* last = tail->prev;
                mpp.erase(last->key);
                DeleteNode(last);
            }
            Node* node = new Node(key, value);
            mpp[key] = node;
            InsertHead(node);
        }
    }
};

int main() {
    LRUCache cache(2);

    cache.put(1, 10);
    cache.put(2, 20);
    cout << cache.get(1) << endl; // 10
    cache.put(3, 30);             // evicts key 2
    cout << cache.get(2) << endl; // -1
    cache.put(4, 40);             // evicts key 1
    cout << cache.get(1) << endl; // -1
    cout << cache.get(3) << endl; // 30
    cout << cache.get(4) << endl; // 40

    return 0;
}
