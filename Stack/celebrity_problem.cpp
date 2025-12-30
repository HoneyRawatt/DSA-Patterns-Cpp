#include <iostream>
#include <vector>
using namespace std;

// ✅ Brute Force Approach — O(n²)
int celebrity_brute(vector<vector<int>> mat) {
    int n = mat.size();
    vector<int> knowme(n, 0), iknow(n, 0);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (mat[i][j] == 1) {
                knowme[j]++;  // j is known by i
                iknow[i]++;   // i knows j
            }
        }
    }

    for (int i = 0; i < n; i++) {
        if (knowme[i] == n - 1 && iknow[i] == 0)
            return i; // Found celebrity
    }

    return -1;
}

// ✅ Optimal Approach — O(n)
int celebrity(vector<vector<int>> mat) {
    int n = mat.size();
    int top = 0, down = n - 1;

    // Find potential celebrity
    while (top < down) {
        if (mat[top][down] == 1)
            top++;  // top knows down → top not celebrity
        else
            down--; // top doesn't know down → down not celebrity
    }

    int candidate = top;

    // Verify candidate
    for (int i = 0; i < n; i++) {
        if (i == candidate) continue;
        // celebrity knows no one and everyone knows celebrity
        if (mat[candidate][i] == 1 || mat[i][candidate] == 0)
            return -1;
    }

    return candidate;
}

int main() {
    vector<vector<int>> mat = {
        {0, 1, 1},
        {0, 0, 1},
        {0, 0, 0}
    };

    cout << "Brute Force Celebrity: " << celebrity_brute(mat) << endl;
    cout << "Optimal Celebrity: " << celebrity(mat) << endl;
    return 0;
}
