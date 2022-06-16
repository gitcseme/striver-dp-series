#include <bits/stdc++.h>
using namespace std;

int m, n;
vector<vector<int>> a;
vector<vector<int>> mem;

/* Memorization 
 * TC -> O(m * n)
 * SC -> O(m * n) + O(m * n)
*/
int solve(int i, int j) {
    if (i == 0 && j == 0) return 1;
    if (i < 0 || j < 0) return 0;
    if (mem[i][j] != -1) return mem[i][j];

    int top = solve(i-1, j);
    int left = solve(i, j-1);

    return mem[i][j] = top + left;
}

/* Tabulation
 * TC -> O(m * n)
 * SC -> O(m * n)
*/
int solve_tabulation() {
    vector<vector<int>> dp(m, vector<int>(n));
    
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i == 0 && j == 0) {
                dp[i][j] = 1;
            }
            else {
                int top = 0, left = 0;
                if (i > 0) top = dp[i-1][j];
                if (j > 0) left = dp[i][j-1];
                dp[i][j] = top + left;
            }
        }
    }
    return dp[m-1][n-1];
}

/* Tabulation space optimize
 * TC -> O(m * n)
 * SC -> O(n + n)
*/
int solve_spaceOptimize() {
    vector<int> prev(n, 0), current(n);

    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i == 0 && j == 0) {
                current[j] = 1;
            }
            else {
                int top = 0, left = 0;
                if (i > 0) top = prev[j];
                if (j > 0) left = current[j-1];
                current[j] = top + left;
            }
        }
        prev = current;
    }
    return prev[n-1];
}

// grid has death cells
int solve_deathcell(int i, int j) {
    if (i >= 0 && j >= 0 && a[i][j] == -1) return 0;
    if (i == 0 && j == 0) return 1;
    if (i < 0 || j < 0) return 0;
    if (mem[i][j] != -1) return mem[i][j];

    int top = solve_deathcell(i-1, j);
    int left = solve_deathcell(i, j-1);

    return mem[i][j] = top + left;
}

// grid has death cells tabulation
int solve_deathcell_tabulation() {
    vector<vector<int>> dp(m, vector<int>(n));
    
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            if (a[i][j] == -1) {
                dp[i][j] = 0;
            }
            else if (i == 0 && j == 0) {
                dp[i][j] = 1;
            }
            else {
                int top = 0, left = 0;
                if (i > 0) top = dp[i-1][j];
                if (j > 0) left = dp[i][j-1];
                dp[i][j] = top + left;
            }
        }
    }
    return dp[m-1][n-1];
}


int main() {
    m = 3; n = 3;
    mem.resize(m, vector<int>(n, -1));
    cout << "memorize: " << solve(m-1, n-1) << "\n";
    cout << "tabulation: " << solve_tabulation() << "\n";
    cout << "space optimization: " << solve_spaceOptimize() << "\n";

    a = {
        { 0, 0, 0 },
        { 0, -1, 0 },
        { 0, 0, 0 },
    };
    
    fill(mem.begin(), mem.end(), vector<int>(n, -1));
    cout << "grid death cell: " << solve_deathcell(m-1, n-1) << "\n";
    cout << "grid death cell tabulation: " << solve_deathcell_tabulation() << "\n";


    return 0;
}