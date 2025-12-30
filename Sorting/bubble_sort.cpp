#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
//Worst Case Time Complexity: O(n²)
// (when the array is in reverse order)

// Best Case Time Complexity: O(n)
// (when the array is already sorted — due to early stopping)

// Space Complexity: O(1)
// (in-place sorting, no extra space used)

void bubble_sort(vector<int>&arr){
    for(int i=arr.size()-1;i>=0;i--){
        int didswap=0;
        for(int j=0;j<=i-1;j++){
            if(arr[j]>arr[j+1]){
                swap(arr[j],arr[j+1]);
                didswap=1;
            } 
        }
        if(didswap==0) break;
    }
}

int main() {
    vector<int> arr = {64, 25, 12, 22, 11};
    bubble_sort(arr);
    cout << "Sorted array: ";
    for(int num : arr) {
        cout << num << " ";
    }

    return 0;
}
