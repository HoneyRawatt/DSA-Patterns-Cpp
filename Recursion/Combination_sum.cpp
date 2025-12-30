#include <bits/stdc++.h>
using namespace std;

void find_combo(int ind, int arr[], int n, int target, vector<vector<int>> &ans, vector<int> &ds) {
    if (ind == n) {
        if (target == 0) {
            ans.push_back(ds);
        }
        return;
    }

    // Pick the element if it's <= target
    if (arr[ind] <= target) {
        ds.push_back(arr[ind]);
        find_combo(ind, arr, n, target - arr[ind], ans, ds);  // same index because repetition allowed
        ds.pop_back();
    }

    // Skip the element
    find_combo(ind + 1, arr, n, target, ans, ds);
}

int main() {
    int arr[] = {5, 3, 4, 1};
    int n = sizeof(arr) / sizeof(arr[0]);
    int target = 4;

    vector<int> ds;
    vector<vector<int>> ans;

    find_combo(0, arr, n, target, ans, ds);

    // Print all combinations
    for (auto &v : ans) {
        for (int num : v)
            cout << num << " ";
        cout << endl;
    }

    return 0;
}
