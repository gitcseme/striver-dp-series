#include <bits/stdc++.h>
using namespace std;

vector<int> a;
vector<vector<int>> mem;

/* Recursion
 * TC -> exponential O(c^n) : where c is variable -> much bigger than O(2^n)
 * SC -> O(n)
 * 
 * Memorization
 * TC -> O(n * n)
 * SC -> O(n * n) + O(n) recursion stack space
*/
int solve(int i, int n) {
    if (n == 0) return 0;
    if (i == 0) return n * a[0];

    if (mem[i][n] != -1) return mem[i][n];

    int not_taken = 0 + solve(i-1, n);
    
    int taken = -1e9;
    int rod_len = i+1;
    if (rod_len <= n) {
        taken = a[i] + solve(i, n - rod_len);
    }

    return mem[i][n] = max(not_taken, taken);
}

/* Tabulation
 * TC -> O(n * n)
 * SC -> O(n * n)
*/ 
int solve_tabuation(int len, int T) {
    vector<vector<int>> dp(len, vector<int>(T+1, -1));
    for (int i = 0; i < len; ++i) dp[i][0] = 0;
    for (int n = 0; n <= T; ++n) dp[0][n] = n * a[0];

    for (int i = 1; i < len; ++i) {
        for (int n = 1; n <= T; ++n) {
            int not_taken = 0 + dp[i-1][n];
    
            int taken = -1e9;
            int rod_len = i+1;
            if (rod_len <= n) {
                taken = a[i] + dp[i][n - rod_len];
            }

            dp[i][n] = max(not_taken, taken);
        }
    }
    
    return dp[len-1][T];
}

int main() {
    a = { 2, 5, 7, 8, 10 };
    int n = 5; // rod length
    int len = a.size();
    mem.resize(len, vector<int>(n+1, -1));

    cout << "Memorization: " << solve(len-1, n) << "\n";
    cout << "Tabulation: " << solve_tabuation(len, n) << "\n";
}