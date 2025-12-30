#include <iostream>
#include <stack>
#include <algorithm>
using namespace std;

// precedence
int priority(char c) {
    if (c == '^') return 3;
    else if (c == '*' || c == '/') return 2;
    else if (c == '+' || c == '-') return 1;
    else return -1;
}

// infix to postfix
string infix_to_postfix(string s) {
    stack<char> st;
    string ans;

    for (int i = 0; i < s.length(); i++) {
        char c = s[i];

        // operand
        if ((c >= 'A' && c <= 'Z') ||
            (c >= 'a' && c <= 'z') ||
            (c >= '0' && c <= '9')) {
            ans += c;
        }
        // left bracket
        else if (c == '(') {
            st.push(c);
        }
        // right bracket
        else if (c == ')') {
            while (!st.empty() && st.top() != '(') {
                ans += st.top();
                st.pop();
            }
            if (!st.empty()) st.pop();
        }
        // operator
        else {
            while (!st.empty() && priority(c) <= priority(st.top())) {
                ans += st.top();
                st.pop();
            }
            st.push(c);
        }
    }

    // pop remaining
    while (!st.empty()) {
        ans += st.top();
        st.pop();
    }

    return ans;
}

// infix to prefix
string infix_to_prefix(string s) {
    // 1. reverse
    reverse(s.begin(), s.end());

    // 2. swap brackets
    for (int i = 0; i < s.length(); i++) {
        if (s[i] == '(') s[i] = ')';
        else if (s[i] == ')') s[i] = '(';
    }

    // 3. get postfix of modified string
    string postfix = infix_to_postfix(s);

    // 4. reverse postfix → prefix
    reverse(postfix.begin(), postfix.end());
    return postfix;
}

// demo
int main() {
    string expr = "(A-B/C)*(A/K-L)";
    cout << "Infix: " << expr << endl;
    cout << "Prefix: " << infix_to_prefix(expr) << endl;
    return 0;
}
