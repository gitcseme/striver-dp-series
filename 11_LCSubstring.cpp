#include <bits/stdc++.h>
using namespace std;

string a, b;

int solve(int i, int j, int count) {
    if (i < 0 || j < 0) return count;

    int ans = 0;
    if (a[i] == b[j]) 
        ans = solve(i-1, j-1, count + 1);
    
    int x = solve(i-1, j, 0);
    int y = solve(i, j-1, 0);

    ans = max(ans, max(x, y));
    return ans;
}

// tabulation by pushing indexes forward by 1 index
int solve_tabulation(int n, int m) {
    vector<vector<int>> dp(n+1, vector<int>(m+1));
    for (int i = 0; i <= n; ++i) dp[i][0] = 0;
    for (int j = 0; j <= m; ++j) dp[0][j] = 0;

    int ans = 0;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            if (a[i-1] == b[j-1]) {
                dp[i][j] = 1 + dp[i-1][j-1];
                ans = max(ans, dp[i][j]);
            }
            else dp[i][j] = 0;
        }
    }

    return ans;
}

int main() {
    a = "abcdxyz";
    b = "xyzabcd";
    int n = a.length();
    int m = b.length();

    cout << "Recursion: " << solve(n-1, m-1, 0) << "\n";
    cout << "Tabulation: " << solve_tabulation(n, m) << "\n";

    return 0;
}