#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <set>
using namespace std;

// ---------------- BRUTE FORCE ----------------
// Time: O(n^2), Space: O(1) ignoring set size
int longest_substr_brute(vector<int>& arr, int k) {
    int maxlen = 0;
    for (int i = 0; i < arr.size(); i++) {
        set<int> st;
        for (int j = i; j < arr.size(); j++) {
            st.insert(arr[j]);
            if (st.size() <= k) {
                maxlen = max(maxlen, j - i + 1);
            } else break;
        }
    }
    return maxlen;
}

// ---------------- BETTER ----------------
// Time: O(2n), Space: O(n)
int longest_substr_better(vector<int>& arr, int k) {
    int l = 0, r = 0, maxlen = 0;
    unordered_map<int, int> mpp;

    while (r < arr.size()) {
        mpp[arr[r]]++;

        while (mpp.size() > k) {
            mpp[arr[l]]--;
            if (mpp[arr[l]] == 0) mpp.erase(arr[l]);
            l++;
        }
        if(mpp.size()<=k) maxlen = max(maxlen, r - l + 1);
        r++;
    }

    return maxlen;
}

// ---------------- OPTIMAL ----------------
// Time: O(n), Space: O(n)
int longest_substr_optimal(vector<int>& arr, int k) {
    int l = 0, r = 0, maxlen = 0;
    unordered_map<int, int> mpp;

    while (r < arr.size()) {
        mpp[arr[r]]++;

        if (mpp.size() > k) {
            mpp[arr[l]]--;
            if (mpp[arr[l]] == 0) mpp.erase(arr[l]);
            l++;
        }

        if(mpp.size()<=k) maxlen = max(maxlen, r - l + 1);
        r++;
    }

    return maxlen;
}

// ---------------- MAIN ----------------
int main() {
    vector<int> arr = {1, 2, 1, 2, 3};
    int k = 2;

    cout << "Brute Force: " << longest_substr_brute(arr, k) << endl;
    cout << "Better: " << longest_substr_better(arr, k) << endl;
    cout << "Optimal: " << longest_substr_optimal(arr, k) << endl;

    return 0;
}
