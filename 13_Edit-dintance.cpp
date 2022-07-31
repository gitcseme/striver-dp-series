#include <bits/stdc++.h>
using namespace std;

string s = "horse";
string t = "ros";

vector<vector<int>> mem;

/* Recursion:
 * TC -> O(3^n * 3^m) -> near exponential
 * SC -> O(n+m) auxiliary stack space
 * 
 * Memorization:
 * TC -> O(n*m)
 * SC -> O(n*m) + O(n+m) auxiliary stack space
*/

int solve(int i, int j) {
    if (j < 0) return i+1; // need to delete i+1 characters
    if (i < 0) return j+1; // need to insert j+1 characters

    if (mem[i][j] != -1) return mem[i][j];

    if (s[i] == t[j]) {
        return solve(i-1, j-1); // matched so -> no operation needed
    }

    int way1 = 1 + solve(i, j-1); // insert in s
    int way2 = 1 + solve(i-1, j-1); // replace in s
    int way3 = 1 + solve(i-1, j); // remove from s

    return mem[i][j] = min(min(way1, way2), way3);
}

/* Tabulation:
 * TC -> O(n*m)
 * SC -> O(n*m)
*/
int solve_tabulation(int n, int m) {
    vector<vector<int>> dp(n+1, vector<int>(m+1));

    for (int i = 0; i <= n; ++i) dp[i][0] = i;
    for (int j = 0; j <= m; ++j) dp[0][j] = j;

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            if (s[i-1] == t[j-1]) {
                dp[i][j] = dp[i-1][j-1]; // matched so -> no operation needed
            }
            else {
                int way1 = 1 + dp[i][j-1]; // insert in s
                int way2 = 1 + dp[i-1][j-1]; // replace in s
                int way3 = 1 + dp[i-1][j]; // remove from s

                dp[i][j] = min(min(way1, way2), way3);
            }
        }
    }
    return dp[n][m];
}

int main() {
    int n = s.length();
    int m = t.length();
    mem.resize(n, vector<int>(m, -1));

    cout << "Memorization: " << solve(n-1, m-1) << "\n";
    cout << "Tabulation: " << solve_tabulation(n-1, m-1) << "\n";

    return 0;
}