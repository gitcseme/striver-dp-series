/* Minimum coins need to make target
 * unlimited supply of coins
*/

#include <bits/stdc++.h>
using namespace std;

vector<int> coins;
vector<int> a;
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

/* Recursion
 * TC -> exponential O(c^n) : where c is variable -> much bigger than O(2^n)
 * SC -> O(target)
 * 
 * Memerization
 * TC -> O(n * target)
 * Sc -> O(n * target) mem array + O(target) stack space
*/
int solve_count(int i, int target) {
    if (i == 0)
        return (target%a[0] == 0);

    if (mem[i][target] != -1) return mem[i][target];

    int not_taken = solve_count(i-1, target);
    int taken = 0;
    if (a[i] <= target) {
        taken = solve_count(i, target - a[i]);
    }

    return mem[i][target] = not_taken + taken;
}



int main() {
    coins = { 9, 6, 5, 1 };
    int n = coins.size();
    int target = 11;
    mem.resize(n, vector<int>(target+1, -1));

    cout << "memorization: " << solve(n-1, target) << "\n";
    cout << "tabulation: " << solve_tabulation(n, target) << "\n";

    a =  { 1, 2, 3 };
    n = a.size();
    target = 4;
    fill(mem.begin(), mem.end(), vector<int>(target+1, -1));
    cout << "total ways: " << solve_count(n-1, target) << "\n";

    return 0;
}