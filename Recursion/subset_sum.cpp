#include <bits/stdc++.h>
using namespace std;

void subset_sum(int ind, int sum, vector<int>& arr, vector<int>& ans) {
    if (ind == arr.size()) {
        ans.push_back(sum);
        return;
    }
    // pick the element
    subset_sum(ind + 1, sum + arr[ind], arr, ans);

    // do not pick the element
    subset_sum(ind + 1, sum, arr, ans);
}

int main() {
    vector<int> arr = {3, 1, 4};
    vector<int> ans;

    subset_sum(0, 0, arr, ans);
    sort(ans.begin(), ans.end());

    for (auto& v : ans) {
        cout << v << " ";
    }

    return 0;
}
