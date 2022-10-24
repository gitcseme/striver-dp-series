#include <bits/stdc++.h>
using namespace std;

vector<int> prices;
int n;
vector<vector<vector<int>>> mem;

/* Recursion:
 * TC -> O(2^n)
 * SC -> O(n) auxiliary stack space
 * 
 * Memorization:
 * TC -> O(n*2*3)
 * SC -> O(n*2*3) + O(n) auxiliary stack space
*/
int solve(int i, int buy, int cnt) {
    if (cnt == 0) return 0;
    if (i == n) return 0;
    if (mem[i][buy][cnt] != -1) return mem[i][buy][cnt];

    int profit = 0;
    if (buy) {
        profit = max(-prices[i] + solve(i+1, 0, cnt), solve(i+1, 1, cnt));
    }
    else {
        profit = max(prices[i] + solve(i+1, 1, cnt-1), solve(i+1, 0, cnt));
    }

    return mem[i][buy][cnt] = profit;
}

/* Tabulation:
 * TC -> O(n*2*3)
 * SC -> O(n*2*3)
*/
int sovle_tabulation(int n) {
    vector<vector<vector<int>>> dp(n+1, vector<vector<int>>(2, vector<int>(3, 0)));
    for (int i = 0; i <= n; ++i)
        dp[i][0][0] = dp[i][1][0] = 0;
    
    for (int c = 0; c <= 2; ++c) 
        dp[n][0][c] = dp[n][1][c] = 0;

    for (int i = n-1; i >= 0; --i) {
        for (int buy = 0; buy <= 1; ++buy) {
            for (int cnt = 0; cnt <= 2; ++cnt) {
                int profit = 0;
                if (buy) {
                    profit = max(-prices[i] + dp[i+1][0][cnt], dp[i+1][1][cnt]);
                }
                else {
                    profit = max(prices[i] + dp[i+1][1][cnt-1], dp[i+1][0][cnt]);
                }

                dp[i][buy][cnt] = profit;
            }
        }
    }
    return dp[0][1][2];
}

int main() {
    prices = { 3, 3, 5, 0, 0, 3, 1, 4 };
    n = prices.size();
    mem.resize(n, vector<vector<int>>(2, vector<int>(3, -1)));

    cout << solve(0, 1, 2) << "\n";
    cout << sovle_tabulation(n) << "\n";
}