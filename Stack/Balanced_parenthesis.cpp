#include <iostream>
#include <stack>
using namespace std;

bool balanced_parenthesis(string s) {
    stack<char> st;
    for (int i = 0; i < s.length(); i++) {
        if (s[i] == '(' || s[i] == '{' || s[i] == '[') {
            st.push(s[i]);
        } else {
            if (st.empty()) return false;
            char ch = st.top();
            st.pop(); 
            if ((s[i] == ')' && ch != '(') ||
                (s[i] == '}' && ch != '{') ||
                (s[i] == ']' && ch != '[')) {
                return false;
            }
        }
    }
    return st.empty(); 
}

int main() {
    string s1 = "{[()]}";
    string s2 = "{[(])}";
    string s3 = "((()))";
    string s4 = "([)]";

    cout << s1 << " -> " << (balanced_parenthesis(s1) ? "Balanced" : "Not Balanced") << endl;
    cout << s2 << " -> " << (balanced_parenthesis(s2) ? "Balanced" : "Not Balanced") << endl;
    cout << s3 << " -> " << (balanced_parenthesis(s3) ? "Balanced" : "Not Balanced") << endl;
    cout << s4 << " -> " << (balanced_parenthesis(s4) ? "Balanced" : "Not Balanced") << endl;

    return 0;
}
