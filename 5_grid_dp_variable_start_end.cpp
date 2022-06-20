#include<bits/stdc++.h>
using namespace std;

int n, m;
vector<vector<int>> mat;
vector<vector<int>> mem;

/* Recursion
 * TC -> 3^(n+m) + O(m)
 * SC -> O(n)
*/
int solve(int i, int j) {
    if (j < 0 || j >= m) return -1e9;
    if (i == 0) return mat[0][j];

    int up = mat[i][j] + solve(i-1, j);
    int upLeft = mat[i][j] + solve(i-1, j-1);
    int upRight = mat[i][j] + solve(i-1, j+1);

    return max({ up, upLeft, upRight });
}

/* Memorization
 * TC -> O(n*m) + O(m)
 * SC -> O(n*m) mem aray + O(n) recursion stack soace
*/
int solve_memorize(int i, int j) {
    if (j < 0 || j >= m) return -1e9;
    if (i == 0) return mat[0][j];

    if (mem[i][j] != -1) return mem[i][j];

    int up = mat[i][j] + solve(i-1, j);
    int upLeft = mat[i][j] + solve(i-1, j-1);
    int upRight = mat[i][j] + solve(i-1, j+1);

    return mem[i][j] = max({ up, upLeft, upRight });
}

/* Tabulation
 * TC -> O(n*m) + O(m)
 * SC -> O(n*m)
*/
int solve_tabulation() {
    vector<vector<int>> dp(n, vector<int>(m));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (i == 0) {
                dp[0][j] = mat[0][j];
            }
            else {
                int upLeft = -1e9, upRight = -1e9;
                int up = mat[i][j] + dp[i-1][j];
                if (j > 0) {
                    upLeft = mat[i][j] + dp[i-1][j-1];
                }
                if (j+1 < m) {
                    upRight = mat[i][j] + dp[i-1][j+1];
                }
                dp[i][j] = max({ up, upLeft, upRight });
            }
        }
    }

    int ans = INT_MIN;
    for (int j = 0; j < m; ++j) {
        ans = max(ans, dp[n-1][j]);
    }
    return ans;
}

int main() {
    n = 4, m = 4;
    mem.resize(n, vector<int>(m, -1));
    mat = {
        { 1, 2, 10, 4 },
        { 100, 3, 2, 1 },
        { 1, 1, 20, 2 },
        { 1, 2, 2, 1 },
    };

    int ans = INT_MIN;
    for (int j = 0; j < m; ++j) {
        ans = max(ans, solve(n-1, j));
    }
    cout << "recursion: " << ans << "\n";

    int ans_m = INT_MIN;
    for (int j = 0; j < m; ++j) {
        ans_m = max(ans_m, solve_memorize(n-1, j));
    }
    cout << "memorize: " << ans_m << "\n";

    cout << "tabulation: " << solve_tabulation() << "\n";

    return 0;
}