#include <iostream>
#include <vector>
#include <stack>
#include <climits>
using namespace std;

vector<int> findNextSmaller(const vector<int>& arr) {
    int n = arr.size();
    vector<int> nse(n);
    stack<int> st;
    for(int i = n - 1; i >= 0; i--) {
        while(!st.empty() && arr[st.top()] >= arr[i]) st.pop();
        nse[i] = st.empty() ? n : st.top();
        st.push(i);
    }
    return nse;
}

vector<int> findPrevSmaller(const vector<int>& arr) {
    int n = arr.size();
    vector<int> pse(n);
    stack<int> st;
    for(int i = 0; i < n; i++) {
        while(!st.empty() && arr[st.top()] > arr[i]) st.pop();
        pse[i] = st.empty() ? -1 : st.top();
        st.push(i);
    }
    return pse;
}

int longest_rectangle_brute(const vector<int>& arr) {
    vector<int> nse = findNextSmaller(arr);
    vector<int> pse = findPrevSmaller(arr);
    int maxi = 0;
    for(int i = 0; i < arr.size(); i++) {
        maxi = max(maxi, arr[i] * (nse[i] - pse[i] - 1));
    }
    return maxi;
}

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

int main() {
    vector<int> heights = {2, 1, 5, 6, 2, 3};
    cout << "Brute: " << longest_rectangle_brute(heights) << endl;
    cout << "Optimal: " << longest_rectangle_optimal(heights) << endl;
    return 0;
}
