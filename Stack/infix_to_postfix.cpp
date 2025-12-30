#include <iostream>
#include <stack>
using namespace std;

// Function to return precedence of operators
int priority(char c) {
    if (c == '^') return 3;
    else if (c == '*' || c == '/') return 2;
    else if (c == '+' || c == '-') return 1;
    else return -1;
}

// Function to convert infix expression to postfix
string infix_to_postfix(string s) {
    stack<char> st;
    string ans;

    for (int i = 0; i < s.length(); i++) {
        char c = s[i];

        // If operand, add to result
        if ((c >= 'A' && c <= 'Z') || 
            (c >= 'a' && c <= 'z') || 
            (c >= '0' && c <= '9')) {
            ans += c;
        }
        // If '(', push to stack
        else if (c == '(') {
            st.push(c);
        }
        // If ')', pop until '('
        else if (c == ')') {
            while (!st.empty() && st.top() != '(') {
                ans += st.top();
                st.pop();
            }
            if (!st.empty()) st.pop(); // pop '('
        }
        // Operator
        else {
            while (!st.empty() && priority(c) <= priority(st.top())) {
                ans += st.top();
                st.pop();
            }
            st.push(c);
        }
    }

    // Pop remaining operators
    while (!st.empty()) {
        ans += st.top();
        st.pop();
    }

    return ans;
}

int main() {
    string expr = "A*(B+C)/D";
    cout << "Infix: " << expr << endl;
    cout << "Postfix: " << infix_to_postfix(expr) << endl;
    return 0;
}
