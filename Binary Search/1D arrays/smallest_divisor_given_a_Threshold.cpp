#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

// Helper function to compute sum of ceilings (arr[i] / div) for all elements
int sumbyd(vector<int> arr, int div,int limit) {
    int sum = 0;
    for (int i = 0; i < arr.size(); i++) {
        // Same as ceil(arr[i] / div)
        sum += (arr[i] + div - 1) / div;
        if(sum>limit) break;
    }
    return sum;
}

// Brute-force: Try every divisor from 1 to max(arr)
int smallestDivisorBrute(vector<int> arr, int limit) {
    int maxVal = *max_element(arr.begin(), arr.end());

    for (int div = 1; div <= maxVal; div++) {
        if (sumbyd(arr, div, limit) <= limit) {
            return div; // First valid divisor found
        }
    }

    return maxVal; // Fallback, though this line should never be reached
}

// Binary search to find the smallest divisor such that sumbyd <= limit
int smallestDivisor(vector<int> arr, int limit) {
    int low = 1;
    int high = *max_element(arr.begin(), arr.end()); // max value in array

    while (low <= high) {
        int mid = low + ((high - low) / 2);
        if (sumbyd(arr, mid,limit) <= limit)
            high = mid - 1; // try smaller divisor
        else
            low = mid + 1;  // try bigger divisor
    }

    return low; // lowest valid divisor
}

// Driver code with example input
int main() {
    vector<int> nums = {1, 2, 5, 9};  // Input array
    int limit = 6;                    // Maximum allowed sum after division

    int result = smallestDivisor(nums, limit);
    cout << "Smallest divisor such that the division sum is <= " << limit << " is: " << result << endl;
    result = smallestDivisorBrute(nums, limit);
    cout << "Smallest divisor (brute) such that division sum <= " << limit << " is: " << result << endl;
    return 0;
}
