#include<iostream>
#include<vector>
#include<algorithm>
#include<numeric> // For accumulate
using namespace std;

// Count how many students are needed if max allowed pages is 'pages'
int countStudent(vector<int> arr, int pages) {
    int students = 1;
    long long pagesStudent = 0;

    for (int i = 0; i < arr.size(); i++) {
        if (pagesStudent + arr[i] <= pages) {
            pagesStudent += arr[i];
        } else {
            students++;
            pagesStudent = arr[i];
        }
    }

    return students;
}

// Brute-force version: Try every possible max page from max(books) to sum(books)
int findPagesBrute(vector<int>& arr, int m, int n) {
    if (m > n) return -1;

    int low = *max_element(arr.begin(), arr.end());
    int high = accumulate(arr.begin(), arr.end(), 0);

    for (int pages = low; pages <= high; pages++) {
        if (countStudent(arr, pages) <= m) {
            return pages;
        }
    }

    return -1;  // Shouldn't reach here
}

// Binary Search on answer to find the minimum pages that can be assigned
int findPages(vector<int>& arr, int m, int n) {
    if (m > n) return -1;  // Can't assign if students > books

    int low = *max_element(arr.begin(), arr.end());           // At least one book per student
    int high = accumulate(arr.begin(), arr.end(), 0);         // At most all books to one student

    while (low <= high) {
        int mid = low + ((high - low) / 2);
        int students = countStudent(arr, mid);
 
        if (students > m) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    return low;  // Minimum number of max pages
}

int main() {
    vector<int> books = {12, 34, 67, 90};  // Pages in each book
    int students = 2;                      // Number of students
    int n = books.size();

    int result = findPages(books, students, n);
    if (result != -1)
        cout << "Minimum pages: " << result << endl;
    else
        cout << "Assignment not possible!" << endl;
    
    findPagesBrute(books, students, n);
    if (result != -1)
        cout << "Minimum pages (brute): " << result << endl;
    else
        cout << "Assignment not possible!" << endl;

    return 0;
}
