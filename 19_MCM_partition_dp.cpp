#include <bits/stdc++.h>
using namespace std;

vector<int> a;
vector<vector<int>> mem;

/* Memorization:
 * TC -> O(n * n) * n  ~ O(n^3)
 * SC -> O(n * n) + O(n) auxiliary stack space
*/

int solve(int i, int j) {
    if (i == j) return 0;
    if (mem[i][j] != -1) return mem[i][j];

    int mini = 1e9;
    for (int k = i; k < j; ++k) {
        int steps = a[i-1] * a[k] * a[j] + solve(i, k) + solve(k+1, j);
        mini = min(mini, steps);
    }

    return mem[i][j] = mini;
}

int solve_tabulation() {
    int n = a.size();
    vector<vector<int>> dp(n, vector<int>(n));
    for (int i = 1; i < n; ++i) dp[i][i] = 0;

    for (int i = n-1; i >= 1; --i) {
        for (int j = i+1; j < n; ++j) {
            int mini = 1e9;
            for (int k = i; k < j; ++k) {
                int steps = a[i-1] * a[k] * a[j] + dp[i][k] + dp[k+1][j];
                mini = min(mini, steps);
            }

            dp[i][j] = mini;
        }
    }

    return dp[1][n-1];
}

int main() {
    a = { 10, 20, 30, 40, 50 };
    int n = a.size();
    mem.resize(n, vector<int>(n, -1));

    cout << solve(1, n-1) << "\n";
    cout << solve_tabulation() << "\n";
}