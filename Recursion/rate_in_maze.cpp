#include <bits/stdc++.h>
using namespace std;

// Recursive function to explore all valid paths from (i, j) to (n-1, n-1)
void solve(int i, int j, vector<vector<int>>& a, int n, vector<string>& ans, string move, vector<vector<int>>& vis) {
    // Base case: Reached bottom-right cell
    if (i == n - 1 && j == n - 1) {
        ans.push_back(move);
        return;
    }

    // Move Down
    if (i + 1 < n && !vis[i][j] && a[i + 1][j] == 1) {
        vis[i][j] = 1;
        solve(i + 1, j, a, n, ans, move + 'D', vis);
        vis[i][j] = 0;
    }

    // Move Left
    if (j - 1 >= 0 && !vis[i][j] && a[i][j - 1] == 1) {
        vis[i][j] = 1;
        solve(i, j - 1, a, n, ans, move + 'L', vis);
        vis[i][j] = 0;
    }

    // Move Right
    if (j + 1 < n && !vis[i][j] && a[i][j + 1] == 1) {
        vis[i][j] = 1;
        solve(i, j + 1, a, n, ans, move + 'R', vis);
        vis[i][j] = 0;
    }

    // Move Up
    if (i - 1 >= 0 && !vis[i][j] && a[i - 1][j] == 1) {
        vis[i][j] = 1;
        solve(i - 1, j, a, n, ans, move + 'U', vis);
        vis[i][j] = 0;
    }
}

// Function to initialize visited matrix and start solving
vector<string> findpath(vector<vector<int>>& m, int n) {
    vector<string> ans;
    vector<vector<int>> vis(n, vector<int>(n, 0));
    if (m[0][0] == 1)
        solve(0, 0, m, n, ans, "", vis);
    return ans;
}

// Main function to test the pathfinding
int main() {
    vector<vector<int>> maze = {
        {1, 0, 0, 0},
        {1, 1, 0, 1},
        {0, 1, 0, 0},
        {1, 1, 1, 1}
    };
    int n = maze.size();

    vector<string> paths = findpath(maze, n);

    if (paths.empty()) {
        cout << "No path exists from start to end." << endl;
    } else {
        cout << "Possible paths from (0,0) to (" << n - 1 << "," << n - 1 << "):" << endl;
        for (const string& path : paths)
            cout << path << endl;
    }

    return 0;
}
