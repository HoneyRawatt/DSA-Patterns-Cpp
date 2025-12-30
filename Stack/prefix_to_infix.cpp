#include <iostream>
#include <stack>
using namespace std;

string prefix_to_infix(string &s) {
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
            string res = "(" + op1 + c + op2 + ")";
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
    string prefix = "*+AB-C"; // example: (A+B)*(C-?)
    string infix = prefix_to_infix(prefix);
    cout << "Prefix: " << prefix << endl;
    cout << "Infix: " << infix << endl;

    return 0;
}
