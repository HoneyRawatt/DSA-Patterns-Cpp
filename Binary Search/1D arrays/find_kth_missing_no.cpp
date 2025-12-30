,#include <iostream>
#include <vector>
using namespace std;

 // Linear Scan to find the Kth missing positive number
int findKthPositive_Linear(vector<int>& arr, int k) {
   for(int i=0;i<arr.size();i++){
    if(arr[i]<=k) k++;
    else break;
   }
   return k;
}
// Binary Search to find the Kth missing positive number
int findKthPositive_Binary(vector<int>& arr, int k) {
    int low = 0, high = arr.size() - 1;

    while (low <= high) {
        int mid = low + (high - low) / 2;
        int missing = arr[mid] - (mid + 1);  // Missing numbers before index mid

        if (missing < k)
            low = mid + 1;
        else
            high = mid - 1;
    }

    return high + k + 1;
}
int main() {
    vector<int> arr = {2, 3, 4, 7, 11};
    int k = 5;

    int result = findKthPositive_Binary(arr, k);
    cout << "Binary Search: " << k << "th missing number is: " << result << endl;

    result = findKthPositive_Linear(arr, k);
    cout << "Linear Search: " << k << "th missing number is: " << result << endl;

    return 0;
}