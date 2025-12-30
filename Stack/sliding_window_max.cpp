#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>
using namespace std;

// ✅ Optimal O(n) version using deque
vector<int> sliding_window_max(vector<int> arr, int k) {
    deque<int> dq;           // stores indices
    vector<int> ls;          // result array

    int n = arr.size();

    for (int i = 0; i < n; i++) {
        // Remove indices that are out of this window
        if (!dq.empty() && dq.front() <= i - k)
            dq.pop_front();

        // Maintain decreasing order in deque
        while (!dq.empty() && arr[dq.back()] <= arr[i])
            dq.pop_back();

        dq.push_back(i);

        // Starting from index k-1, push max for each window
        if (i >= k - 1)
            ls.push_back(arr[dq.front()]);
    }

    return ls;
}

// ✅ Brute-force O(n*k) version
vector<int> sliding_window_max_brute(vector<int> arr, int k) {
    vector<int> ls;
    int n = arr.size();

    for (int i = 0; i <= n - k; i++) {
        int maxi = arr[i];
        for (int j = i; j < i + k; j++)
            maxi = max(maxi, arr[j]);
        ls.push_back(maxi);
    }

    return ls;
}

int main() {
    vector<int> arr = {1, 3, -1, -3, 5, 3, 6, 7};
    int k = 3;

    vector<int> res1 = sliding_window_max(arr, k);
    vector<int> res2 = sliding_window_max_brute(arr, k);

    cout << "Optimal: ";
    for (int x : res1) cout << x << " ";
    cout << "\nBrute: ";
    for (int x : res2) cout << x << " ";
    cout << endl;

    return 0;
}
