#include <iostream>
#include <stack>
using namespace std;

string pre2post(string s) {
    stack<string> st;
    int n = s.length();

    // traverse from right to left
    for (int i = n - 1; i >= 0; i--) {
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
                cout << "Invalid prefix expression\n";
                return "";
            }
            string op1 = st.top(); st.pop(); // first operand
            string op2 = st.top(); st.pop(); // second operand
            string res = op1 + op2 + c;      // combine as postfix
            st.push(res);
        }
    }

    if (st.size() != 1) {
        cout << "Invalid prefix expression\n";
        return "";
    }

    return st.top();
}

int main() {
    string prefix = "*+AB-CD"; // example: (A+B)*(C-D)
    string postfix = pre2post(prefix);
    cout << "Prefix: " << prefix << endl;
    cout << "Postfix: " << postfix << endl;

    return 0;
}
