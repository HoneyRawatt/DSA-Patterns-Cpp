#include<iostream>
using namespace std;

// Helper to compute mid^n and compare with m
int fun(int mid, int n, int m) {
    long long ans = 1;
    for (int i = 1; i <= n; i++) {
        ans *= mid;
        if (ans > m) return 2;   // Too big
    }
    if (ans == m) return 1;       // Exact match
    return 0;                     // Too small
}

int find_nth_root(int n, int m) {
    int low = 1, high = m;

    while (low <= high) {
        int mid = low + (high - low) / 2;
        int result = fun(mid, n, m);

        if (result == 1) return mid;
        else if (result == 0) low = mid + 1;
        else high = mid - 1;
    }

    return -1; // Not a perfect nth root
}

//linearly
int nth_root_linear(int n, int m) {
    for (int x = 1; x <= m; x++) {
        long long power = 1;
        for (int i = 1; i <= n; i++) {
            power *= x;
            if (power > m) break;
        }
        if (power == m) return x;
    }
    return -1;
}
int main() {
    int n = 3, m = 27;
    cout << "The " << n << "th root of " << m << " is: " << find_nth_root(n, m) << endl;
    return 0;
}
