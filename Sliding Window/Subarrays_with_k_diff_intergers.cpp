#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

// --------------------------------------------
// Count subarrays with at most k distinct integers
// Time: O(n), Space: O(k)
// Remember:
// - Sliding window
// - Expand r, shrink l when distinct count > k
// - Add (r - l + 1) subarrays for each r
int noofsubarrays(vector<int>& nums, int k) {
    int l = 0, r = 0, cnt = 0;
    unordered_map<int, int> mpp;

    while (r < nums.size()) {
        mpp[nums[r]]++;

        // Shrink window if more than k distinct
        while (mpp.size() > k) {
            mpp[nums[l]]--;
            if (mpp[nums[l]] == 0) mpp.erase(nums[l]);
            l++;
        }

        cnt += (r - l + 1); // valid subarrays ending at r
        r++;
    }
    return cnt;
}

// --------------------------------------------
// Optimal: Exactly k distinct = atMost(k) - atMost(k-1)
// Time: O(n), Space: O(k)
int subarraysWithKDistinct_optimal(vector<int>& nums, int k) {
    return noofsubarrays(nums, k) - noofsubarrays(nums, k - 1);
}

// --------------------------------------------
// Brute Force: Try all subarrays
// Time: O(n^2), Space: O(k)
// Remember: break inner loop if > k distinct
int subarraysWithKDistinct_brute(vector<int>& nums, int k) {
    int cnt = 0;
    for (int i = 0; i < nums.size(); i++) {
        unordered_map<int, int> mpp;
        for (int j = i; j < nums.size(); j++) {
            mpp[nums[j]]++;
            if (mpp.size() == k) cnt++;
            else if (mpp.size() > k) break;
        }
    }
    return cnt;
}

// --------------------------------------------
// Main for testing
int main() {
    vector<int> nums = {1, 2, 1, 2, 3};
    int k = 2;

    cout << "Brute Force: " << subarraysWithKDistinct_brute(nums, k) << endl;
    cout << "Optimal:     " << subarraysWithKDistinct_optimal(nums, k) << endl;

    return 0;
}
