#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

/*
 * Function to find the maximum score from k cards 
 * by picking from either start or end of the array.
 */
int maxScore(vector<int>& cardPoints, int k) {
    int lsum = 0, rsum = 0, maxsum = 0;
    int n = cardPoints.size();

    // Step 1: Pick all k cards from the left
    for (int i = 0; i < k; i++) {
        lsum += cardPoints[i];
    }
    maxsum = lsum;

    // Step 2: Try taking some from the right end
    // and remove equal number from left
    int rind = n - 1;
    for (int i = k - 1; i >= 0; i--) {
        lsum -= cardPoints[i];          // remove one from left
        rsum += cardPoints[rind--];     // add one from right
        maxsum = max(maxsum, lsum + rsum);
    }

    return maxsum;
}

// ------------------- MAIN FUNCTION -------------------
int main() {
    vector<int> cardPoints = {1, 2, 3, 4, 5, 6, 1};
    int k = 3;

    int result = maxScore(cardPoints, k);
    cout << "Maximum score by picking " << k << " cards: " << result << endl;

    return 0;
}
