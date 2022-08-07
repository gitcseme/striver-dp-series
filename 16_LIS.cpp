#include <bits/stdc++.h>
using namespace std;

vector<int> a;
int n;
vector<vector<int>> mem;

/* Recursion:
 * TC -> O(2^n)
 * SC -> O(n) auxiliary stack space
*/
int solve(int i, int prev) {
    if (i == n) return 0;

    int not_take = solve(i+1, prev);
    int take = 0;
    if (prev == -1 || a[i] > a[prev]) 
        take = 1 + solve(i+1, i);

    return max(not_take, take);
}

/* Memorization with co-ordinate shrft of prev
 * TC -> O(n*n)
 * SC -> O(n*n) + O(n) auxiliary stack space
*/
int solve2(int i, int prev) {
    if (i == n) return 0;
    if (mem[i][prev+1] != -1) return mem[i][prev+1];

    int not_take = solve2(i+1, prev);
    int take = 0;
    if (prev == -1 || a[i] > a[prev]) 
        take = 1 + solve2(i+1, i);

    return mem[i][prev+1] = max(not_take, take);
}

int solve_tabulation(int n) {
    vector<vector<int>> dp(n+1, vector<int>(n+1, 0));

    for (int i = n-1; i >= 0; --i) {
        for (int prev = i-1; prev >= -1; --prev) {
            int not_take = dp[i+1][prev+1];
            int take = 0;
            if (prev == -1 || a[i] > a[prev]) 
                take = 1 + dp[i+1][i+1];

            dp[i][prev+1] = max(not_take, take);
        }
    }

    return dp[0][0];
}

int main() {
    a = { 10, 9, 2, 5, 3, 7, 101, 18 };
    n = a.size();
    mem.resize(n, vector<int>(n+1, -1));

    cout << solve(0, -1) << "\n";
    cout << solve2(0, -1) << "\n";
    cout << solve_tabulation(n)<< "\n";
}