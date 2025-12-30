#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// ---------------- BRUTE FORCE ----------------
// Time: O(n^2)
// For each subarray, count number of zeros and check if ≤ k
int longestOnes_brute(vector<int> &nums, int k) {
    int n = nums.size();
    int maxlen = 0;

    for (int i = 0; i < n; i++) {
        int zeros = 0;
        for (int j = i; j < n; j++) {
            if (nums[j] == 0) zeros++;

            if (zeros <= k) {
                int len = j - i + 1;
                maxlen = max(maxlen, len);
            } else break;
        }
    }
    return maxlen;
}

// ---------------- BETTER: Sliding Window ----------------
// Time: O(2n)
// Shrink window from left when zeros exceed k
int longestOnes_better(vector<int> &nums, int k) {
    int maxlen = 0, l = 0, r = 0, zeros = 0;

    while (r < nums.size()) {
        if (nums[r] == 0) zeros++;

        while (zeros > k) {
            if (nums[l] == 0) zeros--;
            l++;
        }

        // At this point, zeros in window <= k
        int len = r - l + 1;
        maxlen = max(maxlen, len);
        r++;
    }
    return maxlen;
}

// ---------------- OPTIMAL: Cleaner Version ----------------
// Time: O(n)
// Same logic, just more concise
int longestOnes_optimal(vector<int> &nums, int k) {
    int n = nums.size();
    int l = 0, r = 0, maxlen = 0, zeros = 0;

    while (r < n) {
        if (nums[r] == 0) zeros++;

        if (zeros > k) {
            if (nums[l] == 0) zeros--;
            l++;
        }

        if(zeros<=k){
        int len = r - l + 1;
        maxlen = max(maxlen, len);
        }
        r++;
    }

    return maxlen;
}

// ---------------- MAIN FUNCTION ----------------
int main() {
    vector<int> nums = {1, 1, 0, 0, 1, 1, 1, 0, 1};
    int k = 2;

    cout << "Brute force: " << longestOnes_brute(nums, k) << endl;
    cout << "Better (sliding window): " << longestOnes_better(nums, k) << endl;
    cout << "Optimal (clean): " << longestOnes_optimal(nums, k) << endl;

    return 0;
}
