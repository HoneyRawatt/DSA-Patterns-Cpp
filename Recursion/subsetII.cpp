#include <bits/stdc++.h>
using namespace std;

void findsubsets(int ind, vector<int>& nums, vector<int>& ds, vector<vector<int>>& ans) {
    if (ind == nums.size()) {
        ans.push_back(ds);
        return;
    }

    // Take the element
    ds.push_back(nums[ind]);
    findsubsets(ind + 1, nums, ds, ans);
    ds.pop_back();

    // Skip duplicates
    int nextind = ind + 1;
    while (nextind < nums.size() && nums[nextind] == nums[ind]) nextind++;
    findsubsets(nextind, nums, ds, ans);
}

int main() {
    vector<int> arr = {1, 2, 3, 3};
    vector<int> ds;
    vector<vector<int>> ans;

    sort(arr.begin(), arr.end()); // Important to bring duplicates together
    findsubsets(0, arr, ds, ans);

    // Print all unique subsets
    for (auto& subset : ans) {
        cout << "{ ";
        for (int num : subset)
            cout << num << " ";
        cout << "}" << endl;
    }

    return 0;
}
