#include <iostream>
#include <stack>
#include <vector>
using namespace std;

// Brute Force: O(n^2)
vector<int> next_greater_ele_brute(vector<int>& arr) {
    int n = arr.size();
    vector<int> res(n, -1); // initialize with -1

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < i + n; j++) {
            int idx = j % n; // circular index
            if (arr[idx] > arr[i]) {
                res[i] = arr[idx];
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

    // traverse 2n times (circular)
    for (int i = 2 * n - 1; i >= 0; i--) {
        int idx = i % n;
        while (!st.empty() && st.top() <= arr[idx]) {
            st.pop();
        }
        if (i < n) { // record answer only in the first n iterations
            if (!st.empty()) res[idx] = st.top();
        }
        st.push(arr[idx]);
    }
    return res;
}

int main() {
    vector<int> arr = {1, 2, 1};

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
