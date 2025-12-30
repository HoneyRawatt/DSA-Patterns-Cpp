#include <iostream>
#include <stack>
#include <vector>
using namespace std;

// Brute Force: O(n^2)
vector<int> nearest_smaller_ele_brute(vector<int>& arr) {
    int n = arr.size();
    vector<int> res(n, -1);

    for (int i = 0; i < n; i++) {
        for (int j = i - 1; j >= 0; j--) {  // check towards left
            if (arr[j] < arr[i]) {
                res[i] = arr[j];
                break;
            }
        }
    }
    return res;
}

// Optimized: O(n) using stack
vector<int> nearest_smaller_ele(vector<int>& arr) {
    int n = arr.size();
    stack<int> st;
    vector<int> res(n, -1);

    for (int i = 0; i < n; i++) {
        while (!st.empty() && st.top() >= arr[i]) st.pop();
        if (!st.empty()) res[i] = st.top();   // nearest smaller element
        st.push(arr[i]);
    }
    return res;
}

int main() {
    vector<int> arr = {4, 5, 2, 8, 9, 3};

    vector<int> res = nearest_smaller_ele_brute(arr);
    cout << "Brute: ";
    for (auto it : res) cout << it << " ";
    cout << endl;

    res = nearest_smaller_ele(arr);
    cout << "Optimal: ";
    for (auto it : res) cout << it << " ";
    cout << endl;
}
