#include <iostream>
#include <vector>
#include <numeric>  // for accumulate
using namespace std;

int lowerbound(const vector<int>& arr, int n, int x) {
    int low = 0, high = n - 1;
    while (low <= high) {
        int mid = (low + high) / 2;
        if (arr[mid] >= x) high = mid - 1;
        else low = mid + 1;
    }
    return low;
}

int rowWithMax1s(vector<vector<int>>& matrix, int n, int m) {
    int cnt_max = 0;
    int ind = -1;
    for (int i = 0; i < n; i++) {
        int cnt_ones = m - lowerbound(matrix[i], m, 1);
        if (cnt_ones > cnt_max) {  
            ind = i;
            cnt_max = cnt_ones;
        }
    }
    return ind;
}

vector<int> rowAndMaximumOnes(vector<vector<int>>& mat) {
    int n = mat.size(), m = mat[0].size();
    int cnt_max = 0, ind = -1;
    for (int i = 0; i < n; i++) {
        int cnt_ones = accumulate(mat[i].begin(), mat[i].end(), 0);
        if (cnt_ones > cnt_max) {
            cnt_max = cnt_ones;
            ind = i;
        }
    }
    return {ind, cnt_max};
}

int main() {
    vector<vector<int>> mat = {
        {0, 0, 0, 1},
        {0, 1, 1, 1},
        {0, 0, 1, 1},
        {0, 0, 0, 0}
    };

    int n = mat.size(), m = mat[0].size();

    // Use the function depending on assumptions
    int index = rowWithMax1s(mat, n, m); // for sorted rows
    cout << "Row with max 1s (binary search): " << index << endl;

    vector<int> result = rowAndMaximumOnes(mat); // for general case
    cout << "Row with max 1s (accumulate): " << result[0] << " with count = " << result[1] << endl;

    return 0;
}
