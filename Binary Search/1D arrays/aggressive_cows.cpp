#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

// 🧠 Helper function to check if we can place all cows with at least `dist` minimum distance between them
bool canWePlace(vector<int>& arr, int dist, int cows) {
    int countCows = 1;         // Place first cow at the first stall
    int lastPlaced = arr[0];   // Last cow was placed at index 0

    for (int i = 1; i < arr.size(); i++) {
        if (arr[i] - lastPlaced >= dist) {
            countCows++;
            lastPlaced = arr[i];
        }
    }

    return countCows >= cows;
}

// Brute-force: Try all distances from 1 to max possible
int aggressiveCowsBrute(vector<int>& arr, int cows) {
    sort(arr.begin(), arr.end());

    int maxDist = arr.back() - arr[0];
    int ans = 0;

    for (int dist = 1; dist <= maxDist; dist++) {
        if (canWePlace(arr, dist, cows)) {
            ans = dist; // Update answer if placement is possible
        } else {
            break; // Further distances will also fail
        }
    }

    return ans;
}

// 🧠 Main function to find the largest minimum distance
int aggressive_cows(vector<int>& arr, int cows) {
    sort(arr.begin(), arr.end()); // Sort stall positions

    int low = 1;
    int high = arr.back() - arr[0]; // Max possible distance
    int ans = 0;

    while (low <= high) {
        int mid = low + (high - low) / 2;

        if (canWePlace(arr, mid, cows)) {
            ans = mid;       // Store current possible answer
            low = mid + 1;   // Try for a bigger distance
        } else {
            high = mid - 1;  // Try for a smaller distance
        }
    }

    return ans; //high
}

int main() {
    vector<int> stalls = {1, 2, 8, 4, 9};
    int cows = 3;

    int result = aggressive_cows(stalls, cows);
    cout << "Maximum minimum distance to place all cows: " << result << endl;
    result = aggressiveCowsBrute(stalls, cows);
    cout << "Maximum minimum distance (brute) to place all cows: " << result << endl;

    return 0;
}
