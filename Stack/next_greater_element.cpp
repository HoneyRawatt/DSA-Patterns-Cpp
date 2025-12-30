#include <iostream>
#include <stack>
#include <vector>
using namespace std;

// Brute Force: O(n^2)
vector<int> next_greater_ele_brute(vector<int>& arr) {
    int n = arr.size();
    vector<int> res(n, -1); // initialize with -1
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (arr[j] > arr[i]) {
                res[i] = arr[j];
                break;
            }
        }
    }
    return res;
}

// Optimized: O(n) using stack
vector<int> next_greater_ele(vector<int>& arr) {
    int n = arr.size();
    stack<int> st;
    vector<int> res(n, -1);

    for (int i = n - 1; i >= 0; i--) {
        while (!st.empty() && st.top() <= arr[i]) {
            st.pop();
        }
        if (!st.empty()) res[i] = st.top();
        st.push(arr[i]);
    }
    return res;
}

int main() {
    vector<int> arr = {4, 5, 2, 25};
    vector<int> res1 = next_greater_ele_brute(arr);
    vector<int> res2 = next_greater_ele(arr);

    cout << "Brute force result: ";
    for (int x : res1) cout << x << " ";
    cout << endl;

    cout << "Optimized result: ";
    for (int x : res2) cout << x << " ";
    cout << endl;

    return 0;
}
