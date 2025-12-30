#include <iostream>
#include <stack>
using namespace std;

// Brute force approach (extra space with pair)
class min_stack_brute {
    stack<pair<int,int>> st;

public:
    void push(int val) {
        if (st.empty()) st.push({val, val});
        else st.push({val, min(val, st.top().second)});
    }

    void pop() {
        if (!st.empty()) st.pop();
    }

    int top() {
        if (st.empty()) {
            cout << "Stack empty\n";
            return -1;
        }
        return st.top().first;
    }

    int getmin() {
        if (st.empty()) {
            cout << "Stack empty\n";
            return -1;
        }
        return st.top().second;
    }
};

// Optimized approach (O(1) space for min)
class min_stack {
    stack<int> st;
    int mini;

public:
    void push(int val) {
        if (st.empty()) {
            mini = val;
            st.push(val);
        } else {
            if (val >= mini) {
                st.push(val);
            } else {
                // Encode value
                st.push(2 * val - mini);
                mini = val;
            }
        }
    }

    void pop() {
        if (st.empty()) return;

        int x = st.top();
        st.pop();
        if (x < mini) {
            // Decode previous minimum
            mini = 2 * mini - x;
        }
    }

    int top() {
        if (st.empty()) {
            cout << "Stack empty\n";
            return -1;
        }

        int x = st.top();
        if (x >= mini) return x;
        return mini; // encoded value means current minimum
    }

    int getmin() {
        if (st.empty()) {
            cout << "Stack empty\n";
            return -1;
        }
        return mini;
    }
};

int main() {
    min_stack s;
    s.push(5);
    s.push(3);
    s.push(7);
    cout << "Min: " << s.getmin() << endl; // 3
    s.pop();
    cout << "Top: " << s.top() << endl;    // 3
    cout << "Min: " << s.getmin() << endl; // 3
    s.pop();
    cout << "Min: " << s.getmin() << endl; // 5

    return 0;
}
