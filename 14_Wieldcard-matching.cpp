#include <bits/stdc++.h>
using namespace std;

string s = "ab*cd";
string t = "abdefcd";

vector<vector<int>> mem;

/* Recursion:
 * TC -> exponential
 * SC -> O(n + m) auxiliary stack space
 * 
 * Memorization:
 * TC -> O(n * m)
 * SC -> O(n * m) + O(n+m) auxiliary stack space
*/
bool solve(int i, int j) {
    if (i < 0 && j < 0) return true;
    if (i < 0 && j >= 0) return false;
    if (j < 0 && i >= 0) {
        for (int k = i; k >= 0; --k) 
            if (s[k] != '*') return false;
        return true;
    }

    if (mem[i][j] != -1) return mem[i][j];
    
    if (s[i] == t[j] || s[i] == '?') {
        return mem[i][j] = (int)solve(i-1, j-1);
    }
    else if (s[i] == '*') {
        bool way1 = solve(i, j-1); // keep i in place of * and match more from j
        bool way2 = solve(i-1, j-1); // finished matched * and let match rest
        return mem[i][j] = (int)(way1 || way2);
    }
    return mem[i][j] = (int)false;
}

bool solve_tabulation(int n, int m) {
    vector<vector<int>> dp(n+1, vector<int>(m+1, false));
    dp[0][0] = true;
    for (int j = 1; j <= m; ++j) dp[0][j] = false;
    for (int i = 1; i <= n; ++i) {
        bool flag = true;
        for (int k = 1; k <= i; ++k) {
            if (s[k-1] != '*') {
                flag = false;
                break;
            }
        }
        dp[i][0] = flag;
    }

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            if (s[i-1] == t[j-1] || s[i-1] == '?') {
                dp[i][j] = (int)dp[i-1][j-1];
            }
            else if (s[i-1] == '*') {
                bool way1 = dp[i][j-1]; // keep i in place of * and match more from j
                bool way2 = dp[i-1][j-1]; // finished matched * and let match rest
                dp[i][j] = (int)(way1 || way2);
            }
            else
                dp[i][j] = (int)false;
        }
    }

    return dp[n][m];
}

int main() {
    int n = s.length();
    int m = t.length();
    mem.resize(n, vector<int>(m, -1));

    cout << "Memorization: " << solve(n-1, m-1) << "\n";
    cout << "Tabulation: " << solve_tabulation(n, m) << "\n";

    return 0;
}