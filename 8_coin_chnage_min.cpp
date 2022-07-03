/* Minimum coins need to make target
 * unlimited supply of coins
*/

#include <bits/stdc++.h>
using namespace std;

vector<int> coins;
vector<vector<int>> mem;

/* Recursion
 * TC -> exponential O(c^n) : where c is variable -> much bigger than O(2^n)
 * SC -> O(target)
 * 
 * Memerization
 * TC -> O(n * target)
 * Sc -> O(n * target) mem array + O(target) stack space
*/

int solve(int i, int target) {
    if (i == 0) {
        if (target%coins[0] == 0) 
            return target/coins[i];
        
        return (int)1e9;
    }

    if (mem[i][target] != -1) return mem[i][target];

    int not_taken = solve(i-1, target);
    int taken = (int)1e9;
    if (coins[i] <= target) {
        taken = 1 + solve(i, target - coins[i]);
    }

    return mem[i][target] = min(not_taken, taken);
}

 
/* Tabulation
 * TC -> O(n * target)
 * Sc -> O(n * target) mem array 
*/

int solve_tabulation(int n, int T) {
    vector<vector<int>> dp(n, vector<int>(T+1, 0));
    for (int t = 0; t <= T; ++t) 
        dp[0][t] = t%coins[0] == 0 ? t/coins[0] : (int)1e9;

    for (int i = 1; i < n; ++i) {
        for (int target = 0; target <= T; ++target) {
            int not_taken = dp[i-1][target];
            int taken = (int)1e9;
            if (coins[i] <= target) {
                taken = 1 + dp[i][target - coins[i]];
            }

            dp[i][target] = min(not_taken, taken);
        }
    }
    return dp[n-1][T];
}

int main() {
    coins = { 9, 6, 5, 1 };
    int n = coins.size();
    int target = 11;
    mem.resize(n, vector<int>(target+1, -1));

    cout << solve(n-1, target) << "\n";
    cout << solve_tabulation(n, target) << "\n";

    return 0;
}