#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
//time comp- O(n2) and space comp - O(1)
// Function to perform Selection Sort
void selection_sort(vector<int>& arr) {
    int n = arr.size();
    for(int i = 0; i < n - 1; i++) {
        int mini = i; // Assume current index is minimum

        // Find the index of the minimum element in the unsorted part
        for(int j = i + 1; j < n; j++) {
            if(arr[j] < arr[mini]) {
                mini = j;
            }
        }

        // Swap the found minimum with the current index
        swap(arr[mini], arr[i]);
    }
}

int main() {
    vector<int> arr = {64, 25, 12, 22, 11};

    selection_sort(arr); // Sort the array

    cout << "Sorted array: ";
    for(int num : arr) {
        cout << num << " ";
    }

    return 0;
}
