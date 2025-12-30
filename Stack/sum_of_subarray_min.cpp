#include <iostream>
#include <vector>
#include <stack>
#include <climits>
using namespace std;

int sumOfSubarrayMinimumsBrute(const vector<int>& arr) {
    int n = arr.size();
    long long total = 0;
    const int mod = 1e9 + 7;

    for (int i = 0; i < n; i++) {
        int mini = INT_MAX;
        for (int j = i; j < n; j++) {
            mini = min(mini, arr[j]);  // track running min
            total = (total + mini) % mod;
        }
    }
    return (int)total;
}
vector<int> findNSE(const vector<int>& arr) {
    int n = arr.size();
    vector<int> nse(n);
    stack<int> st;

    for (int i = n - 1; i >= 0; i--) {
        while (!st.empty() && arr[st.top()] >= arr[i])
            st.pop();
        nse[i] = st.empty() ? n : st.top();
        st.push(i);
    }
    return nse;
}

vector<int> findPSE(const vector<int>& arr) {
    int n = arr.size();
    vector<int> pse(n);
    stack<int> st;

    for (int i = 0; i < n; i++) {
        while (!st.empty() && arr[st.top()] > arr[i])
            st.pop();
        pse[i] = st.empty() ? -1 : st.top();
        st.push(i);
    }
    return pse;
}

int sumOfSubarrayMinimums(const vector<int>& arr) {
    int n = arr.size();
    vector<int> nse = findNSE(arr);
    vector<int> pse = findPSE(arr);
    long long total = 0;
    const int mod = 1e9 + 7;

    for (int i = 0; i < n; i++) {
        long long left = i - pse[i];
        long long right = nse[i] - i;
        total = (total + (left * right % mod) * arr[i] % mod) % mod;
    }
    return (int)total;
}

int main() {
    vector<int> arr = {3, 1, 2, 4};
    
    cout << "Brute Force Result: " << sumOfSubarrayMinimumsBrute(arr) << endl;
    cout << "Optimized Result: " << sumOfSubarrayMinimums(arr) << endl;
    return 0;
}
