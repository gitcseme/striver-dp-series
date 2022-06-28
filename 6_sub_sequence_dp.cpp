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

int min_abs_diff_2subset(int n) {
    int total = accumulate(a.begin(), a.end(), 0);
    int k = total / 2;

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
    
    int min_diff = k + 1;
    for (int i = 0; i <= k; ++i) {
        if (dp[n-1][i])
            min_diff = min(min_diff, abs(total - 2*i));
            // S - S1 - S1
    }

    return min_diff;
}

int solve_count(int i, int target) {
    if (target == 0) return 1;
    if (i == 0) return (int)(a[0] == target);

    if (mem[i][target] != -1) return mem[i][target];

    int not_taken = solve_count(i-1, target);
    int taken = 0;
    if (a[i] <= target) {
        taken = solve_count(i-1, target-a[i]);
    }

    return mem[i][target] = not_taken + taken;
}

int solve_count_tabulation(int n, int k) {
    vector<vector<int>> dp(n, vector<int>(k+1, 0));
    for (int i = 0; i < n; ++i) dp[i][0] = 1;
    dp[0][a[0]] = 1;

    for (int i = 1; i < n; ++i) {
        for (int target = 1; target <= k; ++target) {
            int not_taken = dp[i-1][target];
            int taken = 0;
            if (a[i] <= target) {
                taken = dp[i-1][target-a[i]];
            }

            dp[i][target] = not_taken + taken;
        }
    }

    return dp[n-1][k];
}

int main()
{
    a = { 3, 2, 7, 5, 1, 4 };
    int target = 9;
    int n = a.size();
    mem.resize(n, vector<int>(target+1, -1));

    cout << "memorization: " << solve(n-1, target) << "\n";
    cout << "tabulation: " << solve_tabulation(n, target) << "\n\n";

    cout << "minumum subset diff: " << min_abs_diff_2subset(n) << "\n";

    fill(mem.begin(), mem.end(), vector<int>(target+1, -1));
    cout << "freq of sum k: " << solve_count(n-1, target) << "\n";
    cout << "freq of sum k tabulation: " << solve_count_tabulation(n, target) << "\n";
}