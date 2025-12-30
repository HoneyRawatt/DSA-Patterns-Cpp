#include<iostream>
#include<vector>
using namespace std;

int sqrt_(int n) {
    if (n == 0 || n == 1) return n;

    int low = 1, high = n;
    int ans = 1;

    while (low <= high) {
        int mid = low + (high - low) / 2;
        long long square = 1LL * mid * mid;

        if (square == n) return mid;
        else if (square < n) {
            ans = mid;         // possible answer, but try to go higher
            low = mid + 1;
        } else {
            high = mid - 1;    // mid*mid too big, go smaller
        }
    }

    return ans; // high
}

int main() {
    int n = 25;
    cout << "Floor of square root of " << n << " is " << sqrt_(n) << endl;

    return 0;
}
