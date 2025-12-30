#include <iostream>
#include <stack>
using namespace std;

string postfix_to_infix(string &s) {
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
            string t1 = st.top(); st.pop(); // right operand
            string t2 = st.top(); st.pop(); // left operand
            string res = "(" + t2 + c + t1 + ")";
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
    string infix = postfix_to_infix(postfix);
    cout << "Postfix: " << postfix << endl;
    cout << "Infix: " << infix << endl;

    return 0;
}
