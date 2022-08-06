#include <bits/stdc++.h>
using namespace std;

vector<int> prices;
int n;
vector<vector<int>> mem;

/* Recursion:
 * TC -> O(2^n)
 * SC -> O(n) auxiliary stack space
 * 
 * Memorization:
 * TC -> O(n*2)
 * SC -> O(n) O(n) auxiliary stack space
*/
int solve(int i, int buy) {
    if (i == n) return 0;
    if (mem[i][buy] != -1) return mem[i][buy];

    int profit = 0;
    if (buy) {
        profit = max(-prices[i] + solve(i+1, 0), solve(i+1, 1));
    }
    else {
        profit = max(prices[i] + solve(i+1, 1), solve(i+1, 0));
    }

    return mem[i][buy] = profit;
}

int sovle_tabulation(int n) {
    vector<vector<int>> dp(n+1, vector<int>(2, 0));
    dp[n][0] = dp[n][1] = 0;

    for (int i = n-1; i >= 0; --i) {
        for (int buy = 0; buy <= 1; ++buy) {
            int profit = 0;
            if (buy) {
                profit = max(-prices[i] + dp[i+1][0], dp[i+1][1]);
            }
            else {
                profit = max(prices[i] + dp[i+1][1], dp[i+1][0]);
            }
            dp[i][buy] = profit;
        }
    }
    return dp[0][1];
}

int main() {
    prices = { 7, 1, 5, 3, 6, 4 };
    n = prices.size();
    mem.resize(n, vector<int>(2, -1));

    cout << solve(0, 1) << "\n";
    cout << sovle_tabulation(n) << "\n";
}