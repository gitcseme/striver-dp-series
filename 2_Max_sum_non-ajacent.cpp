/*
    Maximum sum of non adjacent elements
*/

#include <bits/stdc++.h>
using namespace std;

vector<int> a;
vector<int> mem;

/*
    Memorization
    TC -> O(n)
    SC -> O(n) recursion stack space + O(n) mem array
*/
int solve(int i) {
    if (i == 0) return a[0];
    if (i < 0) return 0;

    if (mem[i] != -1) return mem[i];

    int taken = a[i] + solve(i-2);
    int leave = solve(i-1);

    return mem[i] = max(taken, leave);
}

/*
    Tabulation
    TC -> O(n)
    Sc -> O(n) dp array
*/
int solve_tabulation(int n) {
    vector<int> dp(n);
    dp[0] = a[0];

    for (int i = 1; i < n; ++i) {
        int taken = a[i] + (i > 1 ? dp[i-2] : 0);
        int leave = dp[i-1];

        dp[i] = max(taken, leave);
    }

    return dp[n-1];
}

/*
    Space Optimization
    TC -> O(n)
    SC -> O(1)
*/
int solve_spaceOptimize(int n) {
    int prev_1 = a[0], prev_2 = 0;

    for (int i = 1; i < n; ++i) {
        int taken = a[i] + (i > 1 ? prev_2 : 0);
        int leave = prev_1;

        int current = max(taken, leave);
        prev_2 = prev_1;
        prev_1 = current;
    }

    return prev_1;
}

int main() {
    a = { 2, 1, 4, 9 };
    int n = a.size();
    mem.resize(n, -1);

    cout << "memorization: " << solve(n-1) << "\n";
    cout << "tabulation: " << solve_tabulation(n) << "\n";
    cout << "space optimized: " << solve_spaceOptimize(n) << "\n";

    return 0;
}