#include <iostream>
#include <string>
using namespace std;

class Node {
public:
    string data;
    Node* next;
    Node* back;

    Node() : data(""), next(nullptr), back(nullptr) {}
    Node(string x) : data(x), next(nullptr), back(nullptr) {}
    Node(string x, Node* nextNode, Node* backNode) : data(x), next(nextNode), back(backNode) {}
};

class Browser {
    Node* currentpage;

public:
    Browser(string homepage) {
        currentpage = new Node(homepage);
    }

    void visit(string url) {
        Node* newnode = new Node(url);
        currentpage->next = newnode;
        newnode->back = currentpage;
        currentpage = newnode;
    }

    string back(int steps) {
        while (steps && currentpage->back) {
            currentpage = currentpage->back;
            steps--;
        }
        return currentpage->data;
    }

    string forward(int steps) {
        while (steps && currentpage->next) {
            currentpage = currentpage->next;
            steps--;
        }
        return currentpage->data;
    }
};

// Example usage
int main() {
    Browser browser("leetcode.com");

    browser.visit("google.com");
    browser.visit("facebook.com");
    browser.visit("youtube.com");

    cout << browser.back(1) << endl;     // facebook.com
    cout << browser.back(1) << endl;     // google.com
    cout << browser.forward(1) << endl;  // facebook.com

    browser.visit("linkedin.com");
    cout << browser.forward(2) << endl;  // linkedin.com
    cout << browser.back(2) << endl;     // google.com
    cout << browser.back(7) << endl;     // leetcode.com

    return 0;
}
