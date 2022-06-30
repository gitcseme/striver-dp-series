#include<bits/stdc++.h>
using namespace std;

vector<int> price, wt;
vector<vector<int>> mem;

/* Recursion
 * TC -> O(2^n)
 * SC -> O(n)
 * 
 * Memorization
 * TC -> O(n * W)
 * SC -> O(n * W) mem array + O(n) stack space
*/
int solve(int i, int W) {
    if (i == 0) {
        if (wt[0] <= W) return price[0];
        return 0;
    }

    if (mem[i][W] != -1) return mem[i][W];

    int not_taken = solve(i-1, W);
    int taken = INT_MIN;
    if (wt[i] <= W)
        taken = price[i] + solve(i-1, W - wt[i]);

    return mem[i][W] = max(not_taken, taken);
}

/* Tabulation
 * TC -> O(n * W)
 * SC -> O(n * W) mem array
*/
int solve_tabulation(int n, int W) {
    vector<vector<int>> dp(n, vector<int>(W+1, 0));
    for (int w = 0; w <= W; ++w) 
        dp[0][w] = w < wt[0] ? 0 : price[0];

    for (int i = 1; i < n; ++i) {
        for (int w = 0; w <= W; ++w) {
            int not_taken = dp[i-1][w];
            int taken = INT_MIN;
            if (wt[i] <= w)
                taken = price[i] + dp[i-1][w - wt[i]];

            dp[i][w] = max(not_taken, taken);
        }
    }

    return dp[n-1][W];
}

int main() {
    wt = { 3, 2, 5 };
    price = { 30, 40, 60 };

    int n = wt.size();
    int W = 6;
    mem.resize(n, vector<int>(W+1, -1));

    cout << "memorization: " << solve(n-1, W) << "\n";
    cout << "tabulation: " << solve_tabulation(n, W) << "\n";
}