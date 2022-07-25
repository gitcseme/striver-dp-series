#include <bits/stdc++.h>
using namespace std;

string a, b;
int n, m;
vector<vector<int>> mem;

// print LCS 
string lcs = "";
void printLCS(vector<vector<int>> &dp, int i, int j) {
    if (i == 0) {
        lcs += a[i];
        return;
    }
    if (j == 0) {
        lcs += b[j];
        return;
    }

    if (dp[i][j-1] == dp[i-1][j] ) {
        lcs += a[i];
        printLCS(dp, i-1, j-1);
    }
    else if (dp[i][j-1] > dp[i-1][j]) printLCS(dp, i, j-1);
    else printLCS(dp, i-1, j);
}

/* Recursion:
 * TC -> O(2^n * 2^m) --> near exponential
 * SC -> O(n+m) stack space
 * 
 * Memorization:
 * TC -> O(n * m)
 * SC -> O(n * m) + O(n+m) stack space
*/
int solve(int i, int j) {
    if (i < 0 | j < 0) return 0;

    if (mem[i][j] != -1) return mem[i][j];

    int maxLen;
    if (a[i] == b[j])
        maxLen = 1 + solve(i-1, j-1);
    else
        maxLen = max(solve(i-1, j), solve(i, j-1));

    return mem[i][j] = maxLen;
}

/* Tabulation / bottom-up:
 * TC -> O(n * m)
 * SC -> O(n * m)
*/
int solve_tabulation(int n, int m) {
    vector<vector<int>> dp(n, vector<int>(m));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            int maxLen;
            if (a[i] == b[j]) {
                maxLen = 1 + ((i-1>=0 && j-1>=0) ? dp[i-1][j-1] : 0);
            }
            else {
                int x = i-1 >= 0 ? dp[i-1][j] : 0;
                int y = j-1 >= 0 ? dp[i][j-1] : 0;
                maxLen = max(x, y);
            }

            dp[i][j] = maxLen;
        }
    }

    printLCS(dp, n-1, m-1);

    return dp[n-1][m-1];
}


int main() {
    a = "abcde";
    b = "bdgek";
    n = a.length();
    m = b.length();
    mem.resize(n, vector<int>(m, -1));

    cout << solve(n-1, m-1) << "\n";
    cout << solve_tabulation(n, m) << "\n";
    reverse(lcs.begin(), lcs.end());
    cout << "LCS: " << lcs << "\n";

    return 0;
}