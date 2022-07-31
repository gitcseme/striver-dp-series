#include <bits/stdc++.h>
using namespace std;

string s = "babgbag";
string t = "bag";

vector<vector<int>> mem;

/* Recursion:
 * TC -> 2^n * 2^m => near exponential
 * SC -> O(n + m) auxiliary stack space 
 * 
 * Memorization:
 * TC -> O(n * m)
 * SC -> O(n * m) + O(n + m) auxiliary stack space
*/
int solve(int i, int j) {

    if (j < 0) return 1;
    if (i < 0) return 0;

    if (mem[i][j] != -1) return mem[i][j];

    int way1 = 0;
    if (s[i] == t[j]) {
        way1 = solve(i-1, j-1);
    }

    int way2 = solve(i-1, j);

    return mem[i][j] = way1 + way2;
}

int solve_tabulation(int n, int m) {
    vector<vector<int>> dp(n+1, vector<int>(m+1));
    for (int j = 0; j <= m; ++j) dp[0][j] = 0;
    for (int i = 0; i <= n; ++i) dp[i][0] = 1;

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            int way1 = 0;
            if (s[i-1] == t[j-1]) {
                way1 = dp[i-1][j-1];
            }

            int way2 = dp[i-1][j];
            dp[i][j] = way1 + way2;
        }
    }
    return dp[n][m];
}

int main() {

    int n = s.length();
    int m = t.length();

    mem.resize(n, vector<int>(m, -1));

    cout << solve(n-1, m-1) << "\n";
    cout << solve_tabulation(n, m) << "\n";

    return 0;
}