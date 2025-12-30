#include <iostream>
#include <stack>
using namespace std;

string post2pre(string s) {
    stack<string> st;

    for (int i = 0; i < s.length(); i++) {
        char c = s[i];

        // Operand
        if ((c >= 'A' && c <= 'Z') || 
            (c >= 'a' && c <= 'z') || 
            (c >= '0' && c <= '9')) {
            st.push(string(1, c));
        } 
        // Operator
        else {
            if (st.size() < 2) {
                cout << "Invalid postfix expression\n";
                return "";
            }
            string op1 = st.top(); st.pop(); // first operand (right)
            string op2 = st.top(); st.pop(); // second operand (left)
            string res = c + op2 + op1;      // operator + left + right
            st.push(res);
        }
    }

    if (st.size() != 1) {
        cout << "Invalid postfix expression\n";
        return "";
    }

    return st.top();
}

int main() {
    string postfix = "AB+C*"; // example: (A+B)*C
    string prefix = post2pre(postfix);
    cout << "Postfix: " << postfix << endl;
    cout << "Prefix: " << prefix << endl;
    return 0;
}
