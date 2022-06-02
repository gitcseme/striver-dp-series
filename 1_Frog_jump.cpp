/*
    If frog jumps from i to j then energy cost = abs(a[i] - a[j])
    fi minimul energy cost to reach nth stair

    1. represent the problem in terms of iex
    2. Do all stuff on that iex
    3. Take min(from all those stuffs)
*/

#include <bits/stdc++.h>
using namespace std;

vector<int> a;
vector<int> mem;

// Top-down
int solve(int i) {
    if (i == 0) return 0;
    if (mem[i] != -1) return mem[i];

    int left = solve(i-1) + abs(a[i] - a[i-1]);
    int right = INT_MAX;
    if (i-2 >= 0) {
        right = solve(i-2) + abs(a[i] - a[i-2]);
    }

    mem[i] = min(left, right);

    return mem[i];
}

// Bottom-up
int solve_itarative(int n) {
    vector<int> dp(n);
    dp[0] = 0;
    for (int i = 1; i < n; ++i) {
        int left = dp[i-1] + abs(a[i] - a[i-1]);
        int right = INT_MAX;
        if (i-2 >= 0) {
            right = dp[i-2] + abs(a[i] - a[i-2]);
        }

        dp[i] = min(left, right);
    }
    return dp[n-1];
}

int solve_itarative_spaceOptimized(int n) {
    int prev_1 = 0, prev_2 = 0, current;

    for (int i = 1; i < n; ++i) {
        int left = prev_1 + abs(a[i] - a[i-1]);
        int right = INT_MAX;
        if (i-2 >= 0) {
            right = prev_2 + abs(a[i] - a[i-2]);
        }

        current = min(left, right);
        prev_2 = prev_1;
        prev_1 = current;
    }
    return prev_1;
}

int main() {
    a = { 30, 10, 60, 10, 60, 50 };
    int n = a.size();
    mem.resize(n, -1);

    cout << "recursive:  " << solve(n-1) << "\n";
    cout << "tabulation: " << solve_itarative(n) << "\n";
    cout << "space optm: " << solve_itarative_spaceOptimized(n) << "\n";

    return 0;
}