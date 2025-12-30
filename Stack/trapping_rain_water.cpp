#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int trapping_rain_water_2n(vector<int>& arr) {
    int n = arr.size();
    if (n == 0) return 0;

    vector<int> suffixmax(n);
    suffixmax[n-1] = arr[n-1];
    for (int i = n-2; i >= 0; i--) {
        suffixmax[i] = max(suffixmax[i+1], arr[i]);
    }

    int total = 0, leftmax = 0;
    for (int i = 0; i < n; i++) {
        leftmax = max(leftmax, arr[i]);
        total += min(leftmax, suffixmax[i]) - arr[i];
    }

    return total;
}

// Optimal: Two-pointer approach O(n)
int trapping_rain_water(vector<int>& arr) {
    int n = arr.size();
    if (n == 0) return 0;

    int l = 0, r = n - 1;
    int lmax = 0, rmax = 0;
    int total = 0;

    while (l <= r) {
        if (arr[l] <= arr[r]) {
            if (arr[l] >= lmax)
                lmax = arr[l];
            else
                total += lmax - arr[l];
            l++;
        } else {
            if (arr[r] >= rmax)
                rmax = arr[r];
            else
                total += rmax - arr[r];
            r--;
        }
    }
    return total;
}

int main() {
    vector<int> arr = {0,1,0,2,1,0,1,3,2,1,2,1};

    cout << "Brute Force: " << trapping_rain_water_brute(arr) << endl;
    cout << "Optimal: " << trapping_rain_water(arr) << endl;

    return 0;
}
