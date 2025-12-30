#include <iostream>
#include <vector>
#include <stack>
#include <climits>
using namespace std;

int longest_rectangle_optimal(const vector<int>& arr) {
    int n = arr.size();
    stack<int> st;
    int maxarea = 0;

    for(int i = 0; i < n; i++) {
        while(!st.empty() && arr[st.top()] > arr[i]) {
            int ele = st.top();
            st.pop();
            int nse = i;
            int pse = st.empty() ? -1 : st.top();
            maxarea = max(maxarea, arr[ele] * (nse - pse - 1));
        }
        st.push(i);
    }

    while(!st.empty()) {
        int ele = st.top();
        st.pop();
        int nse = n;
        int pse = st.empty() ? -1 : st.top();
        maxarea = max(maxarea, arr[ele] * (nse - pse - 1));
    }

    return maxarea;
}

int maximal_rectangle(vector<vector<int>> mat) {
    int n = mat.size();
    if(n == 0) return 0;
    int m = mat[0].size();
    int maxarea = 0;

    vector<vector<int>> psum(n, vector<int>(m, 0));

    // Build prefix sum column-wise
    for(int j = 0; j < m; j++) {
        int sum = 0;
        for(int i = 0; i < n; i++) {
            if(mat[i][j] == 0) sum = 0;
            else sum += 1;
            psum[i][j] = sum;
        }
    }

    // Apply histogram logic row by row
    for(int i = 0; i < n; i++) {
        maxarea = max(maxarea, longest_rectangle_optimal(psum[i]));
    }

    return maxarea;
}

int main() {
    vector<vector<int>> mat = {
        {1, 0, 1, 0, 0},
        {1, 0, 1, 1, 1},
        {1, 1, 1, 1, 1},
        {1, 0, 0, 1, 0}
    };

    cout << maximal_rectangle(mat) << endl; // Expected Output: 6
    return 0;
}
