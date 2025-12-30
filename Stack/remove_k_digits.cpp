#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
using namespace std;

string remove_k_digits(string s, int k) {
    stack<char> st;
    int n = s.length();

    for (int i = 0; i < n; i++) {
        while (!st.empty() && k > 0 && st.top() > s[i]) {
            st.pop();
            k--;
        }
        st.push(s[i]);
    }

    // If still have k left, remove from the end
    while (k > 0 && !st.empty()) {
        st.pop();
        k--;
    }

    // Build the result
    string res;
    while (!st.empty()) {
        res += st.top();
        st.pop();
    }
    reverse(res.begin(), res.end());

    // Remove leading zeros
    while (res.size() > 1 && res[0] == '0') {
        res.erase(res.begin());
    }

    // Handle empty result
    if (res.empty()) return "0";
    return res;
}

int main() {
    string s = "1432219";
    int k = 3;
    cout << remove_k_digits(s, k) << endl; // Expected output: "1219"
    return 0;
}
