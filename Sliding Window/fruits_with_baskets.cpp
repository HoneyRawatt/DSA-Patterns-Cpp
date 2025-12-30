#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <set>
using namespace std;

// ---------------- BRUTE FORCE ----------------
// Time: O(n^2), Space: O(1) ignoring set size
// Try every subarray and check if it has at most 2 types
int totalFruits_brute(vector<int>& arr) {
    int maxlen = 0;
    for (int i = 0; i < arr.size(); i++) {
        set<int> st;
        for (int j = i; j < arr.size(); j++) {
            st.insert(arr[j]);
            if (st.size() <= 2) {
                maxlen = max(maxlen, j - i + 1);
            } else break;
        }
    }
    return maxlen;
}

// ---------------- BETTER ----------------
// Time: O(2n), Space: O(n) for hashmap
// Sliding window with map to count fruits
int totalFruit_better(vector<int>& fruits) {
    int l = 0, r = 0, maxlen = 0;
    unordered_map<int, int> mpp;

    while (r < fruits.size()) {
        mpp[fruits[r]]++;

        // Shrink window if more than 2 types
        if (mpp.size() > 2) {
            while (mpp.size() > 2) {
                mpp[fruits[l]]--;
                if (mpp[fruits[l]] == 0) mpp.erase(fruits[l]);
                l++;
            }
        }

        // Update max length
        if (mpp.size() <= 2) {
            maxlen = max(maxlen, r - l + 1);
        }
        r++;
    }

    return maxlen;
}

// ---------------- OPTIMAL ----------------
// Time: O(n), Space: O(n)
// Same as better but cleaner window shrink
int totalFruit_optimal(vector<int>& fruits) {
    int l = 0, r = 0, maxlen = 0;
    unordered_map<int, int> mpp;

    while (r < fruits.size()) {
        mpp[fruits[r]]++;

        // Shrink window when more than 2 types
        if (mpp.size() > 2) {
            mpp[fruits[l]]--;
            if (mpp[fruits[l]] == 0) mpp.erase(fruits[l]);
            l++;
        }

        if(mpp.size()<=2){
        // Update maxlen
        maxlen = max(maxlen, r - l + 1);
        }
        r++;
    }

    return maxlen;
}

// ---------------- MAIN FUNCTION ----------------
int main() {
    vector<int> fruits = {1, 2, 1, 2, 3, 2, 2, 1};

    cout << "Brute Force: " << totalFruits_brute(fruits) << endl;
    cout << "Better (Sliding Window): " << totalFruit_better(fruits) << endl;
    cout << "Optimal (Cleaned Sliding Window): " << totalFruit_optimal(fruits) << endl;

    return 0;
}
