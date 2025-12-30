#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

// ✅ Brute-force O(n^2) version
int lengthoflongestsubstr_brute(string s)
{
    int maxlen = 0, n = s.length();

    for (int i = 0; i < n; i++)
    {
        int hash[256] = {0}; // reset for every starting index

        for (int j = i; j < n; j++)
        {
            if (hash[s[j]])
                break; // if already seen, break

            hash[s[j]] = 1; // mark as seen
            int len = j - i + 1;
            maxlen = max(maxlen, len);
        }
    }
    return maxlen;
}
// ✅ Optimized sliding window O(n) version
int lengthOfLongestSubstring(string s)
{
    int hash[256];
    for (int i = 0; i < 255; i++)
        hash[i] = -1; // initialize all characters as not seen

    int n = s.length();
    int l = 0, r = 0, maxlen = 0;

    while (r < n)
    {
        // if current character already seen and inside current window
        if (hash[s[r]] != -1)
        {
            if (hash[s[r]] >= l)
                l = hash[s[r]] + 1; // move left pointer to avoid duplicate
        }

        int len = r - l + 1;       // current window length
        maxlen = max(len, maxlen); // update max length

        hash[s[r]] = r; // update last seen index
        r++;            // move right pointer
    }

    return maxlen;
}

// --------------- MAIN FUNCTION ---------------
int main()
{
    string input = "abcabcbb";
    int result1 = lengthOfLongestSubstring(input);
    cout << "Optimal (O(n)) result: " << result1 << endl;

    int result2 = lengthoflongestsubstr_brute(input);
    cout << "Brute-force (O(n^2)) result: " << result2 << endl;
    return 0;
}
