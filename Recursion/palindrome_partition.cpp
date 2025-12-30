 #include <bits/stdc++.h>
using namespace std;

// Utility function to check if a substring is a palindrome
bool isPalindrome(string s, int start, int end) {
    while (start <= end) {
        if (s[start++] != s[end--]) return false;
    }
    return true;
}

// Recursive backtracking function to generate all palindromic partitions
void generatePartitions(int index, string s, vector<string>& path, vector<vector<string>>& result) {
    // Base case: if index reaches end of string, push current path to result
    if (index == s.size()) {
        result.push_back(path);
        return;
    }

    // Try all substrings starting from index
    for (int i = index; i < s.size(); i++) {
        // If substring s[index..i] is a palindrome, include it in path
        if (isPalindrome(s, index, i)) {
            path.push_back(s.substr(index, i - index + 1)); // Add current palindrome substring
            generatePartitions(i + 1, s, path, result);     // Recurse for remaining substring
            path.pop_back(); // Backtrack
        }
    }
}

int main() {
    string s = "aabb";

    vector<vector<string>> result;
    vector<string> path;

    generatePartitions(0, s, path, result);

    // Output all the partitions
    cout << "Palindrome Partitions of \"" << s << "\":" << endl;
    for (const auto& partition : result) {
        cout << "[ ";
        for (const string& str : partition) {
            cout << "\"" << str << "\" ";
        }
        cout << "]" << endl;
    }

    return 0;
}
