#include <iostream>
#include <vector>
#include <stack>
#include <climits>
using namespace std;

/* 
========================
1️⃣ Brute-force Method
========================
Time Complexity: O(n^2)
- Two nested loops over the array.
- For each subarray, we update current min/max in O(1).
- Total comparisons ~ n*(n+1)/2 ≈ O(n^2)

Space Complexity: O(1)
- No extra space used except variables for min/max.
*/
int sum_of_subarr_range_brute(vector<int> arr){
    int sum = 0;
    int n = arr.size();
    for(int i = 0; i < n; i++){
        int largest = arr[i];
        int smallest = arr[i];
        for(int j = i; j < n; j++){
            largest = max(largest, arr[j]); // Update current maximum
            smallest = min(smallest, arr[j]); // Update current minimum
            sum += (largest - smallest); // Add the range to sum
        }
    }
    return sum;
}

/* 
========================
2️⃣ Optimized Method
========================
Idea: Use monotonic stacks to calculate contribution of each element 
as minimum or maximum in all subarrays it participates in.
Time Complexity: O(n)
- Each element is pushed and popped at most once from the stack → ~2n operations
Space Complexity: O(n)
- Stacks and helper arrays for PSE/NSE or PGE/NGE
*/

/* ----- Minimums Helpers ----- */
vector<int> findNextSmaller(const vector<int>& arr) {
    int n = arr.size();
    vector<int> nse(n);
    stack<int> st;
    for(int i = n-1; i >= 0; i--){
        while(!st.empty() && arr[st.top()] >= arr[i]) st.pop();
        nse[i] = st.empty() ? n : st.top();
        st.push(i);
    }
    return nse;
}

vector<int> findPrevSmaller(const vector<int>& arr) {
    int n = arr.size();
    vector<int> pse(n);
    stack<int> st;
    for(int i = 0; i < n; i++){
        while(!st.empty() && arr[st.top()] > arr[i]) st.pop();
        pse[i] = st.empty() ? -1 : st.top();
        st.push(i);
    }
    return pse;
}

int sumSubarrayMinimums(const vector<int>& arr){
    int n = arr.size();
    vector<int> nse = findNextSmaller(arr);
    vector<int> pse = findPrevSmaller(arr);
    long long total = 0;
    const int mod = 1e9+7;

    for(int i = 0; i < n; i++){
        long long left = i - pse[i];
        long long right = nse[i] - i;
        total = (total + (left * right % mod) * arr[i] % mod) % mod;
    }
    return (int)total;
}

/* ----- Maximums Helpers ----- */
vector<int> findNextGreater(const vector<int>& arr) {
    int n = arr.size();
    vector<int> nge(n);
    stack<int> st;
    for(int i = n-1; i >= 0; i--){
        while(!st.empty() && arr[st.top()] <= arr[i]) st.pop();
        nge[i] = st.empty() ? n : st.top();
        st.push(i);
    }
    return nge;
}

vector<int> findPrevGreater(const vector<int>& arr) {
    int n = arr.size();
    vector<int> pge(n);
    stack<int> st;
    for(int i = 0; i < n; i++){
        while(!st.empty() && arr[st.top()] < arr[i]) st.pop();
        pge[i] = st.empty() ? -1 : st.top();
        st.push(i);
    }
    return pge;
}

int sumSubarrayMaximums(const vector<int>& arr){
    int n = arr.size();
    vector<int> nge = findNextGreater(arr);
    vector<int> pge = findPrevGreater(arr);
    long long total = 0;
    const int mod = 1e9+7;

    for(int i = 0; i < n; i++){
        long long left = i - pge[i];
        long long right = nge[i] - i;
        total = (total + (left * right % mod) * arr[i] % mod) % mod;
    }
    return (int)total;
}

/* ----- Sum of Subarray Ranges ----- */
int sumOfSubarrayRanges(const vector<int>& arr){
    // Contribution of each element as maximum minus minimum
    int maxSum = sumSubarrayMaximums(arr);
    int minSum = sumSubarrayMinimums(arr);
    const int mod = 1e9+7;
    long long ans = ((long long)maxSum - minSum + mod) % mod; // Ensure non-negative
    return (int)ans;
}

/* ----- Main ----- */
int main(){
    vector<int> arr = {3, 1, 2, 4};

    cout << "Brute-force sum of subarray ranges: " 
         << sum_of_subarr_range_brute(arr) << endl; // O(n^2)

    cout << "Optimized sum of subarray ranges: " 
         << sumOfSubarrayRanges(arr) << endl; // O(n) ~ 10n operations

    return 0;
}
