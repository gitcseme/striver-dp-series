#include<bits/stdc++.h>
using namespace std;

vector<int> a;
vector<vector<int>> mem;

/* Recursion
 * TC -> O(2^n)
 * SC -> O(n) stack space
 * 
 * Memorization
 * TC -> O(n*target)
 * SC -> O(n*target) mem array + O(n) stack space
*/

bool solve(int i, int target) {
    if (target == 0) return true;
    if (i == 0) return a[0] == target;

    if (mem[i][target] != -1) return mem[i][target];

    int not_taken = solve(i-1, target);
    int taken = false;
    if (!not_taken && target >= a[i]) {
        taken = solve(i-1, target-a[i]);
    }

    return mem[i][target] = (int)(not_taken || taken);
}

/* Tabulation
 * TC -> O(n*target)
 * SC -> O(n*target) mem array
*/
bool solve_tabulation(int n, int k) {
    vector<vector<bool>> dp(n, vector<bool>(k+1, false));
    for (int i = 0; i < n; ++i) dp[i][0] = true;
    dp[0][a[0]] = true;

    for (int i = 1; i < n; ++i) {
        for (int target = 1; target <= k; ++target) {
            int not_taken = dp[i-1][target];
            int taken = false;
            if (!not_taken && target >= a[i]) {
                taken = dp[i-1][target-a[i]];
            }

            dp[i][target] = (int)(not_taken || taken);
        }
    }
    return dp[n-1][k];
}

int main()
{
    a = { 1, 3, 4, 6, 2, 1 };
    int target = 19;
    int n = a.size();
    mem.resize(n, vector<int>(target+1, -1));

    cout << "memorization: " << solve(n-1, target) << "\n";
    cout << "tabulation: " << solve_tabulation(n, target) << "\n";
}