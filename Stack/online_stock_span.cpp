#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
using namespace std;

// Brute Force Version
class StockSpannerBrute {
public:
    vector<int> arr;
    StockSpannerBrute() {}

    int next(int price) {
        int cnt = 1;
        arr.push_back(price);
        for (int i = arr.size() - 2; i >= 0; i--) {
            if (arr[i] <= price)
                cnt++;
            else
                break;
        }
        return cnt;
    }
};

// Optimized Version using Stack
class StockSpanner {
public:
    stack<pair<int, int>> st; // {price, index}
    int ind;

    StockSpanner() {
        ind = -1;
        while (!st.empty()) st.pop();
    }

    int next(int price) {
        ind++;

        while (!st.empty() && st.top().first <= price)
            st.pop();

        int prevGreaterIndex = st.empty() ? -1 : st.top().second;
        int ans = ind - prevGreaterIndex;

        st.push({price, ind});
        return ans;
    }
};

int main() {
    StockSpanner s;

    vector<int> prices = {100, 80, 60, 70, 60, 75, 85};

    for (int p : prices) {
        cout << s.next(p) << " ";
    }

    return 0;
}
