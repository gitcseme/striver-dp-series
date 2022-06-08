/*
    If frog jumps from i to j then energy cost = abs(a[i] - a[j])
    fi minimul energy cost to reach nth stair

    1. represent the problem in terms of index
    2. Do all stuff on that index
    3. Take min(from all those stuffs)
*/

#include <bits/stdc++.h>
using namespace std;

vector<int> a;
vector<int> mem;

/* Top-down
 * TC -> O(n)
 * SC -> O(n) == recursion stack space
*/
int solve(int i) {
    if (i == 0) return 0;
    if (mem[i] != -1) return mem[i];

    int left = solve(i-1) + abs(a[i] - a[i-1]);
    int right = INT_MAX;
    if (i-2 >= 0) {
        right = solve(i-2) + abs(a[i] - a[i-2]);
    }

    return mem[i] = min(left, right);
}

/* Bottom-up
 * TC -> O(n)
 * SC -> O(n) ==> dp array
*/
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

///// frog can jump k distance
/* k-jumps
 * TC -> O(n * k)
 * SC -> O(n) == recursion stack space
*/
int solve_k_jump(int i, int k) {
    if (i == 0) return 0;
    if (mem[i] != -1) return mem[i];

    int min_jmp = INT_MAX;
    for(int j = 1; j <= k; ++j) {
        if (i-j >= 0) {
            int jmp = solve_k_jump(i-j, k) + abs(a[i] - a[i-j]);
            min_jmp = min(min_jmp, jmp);
        } else {
            break;
        }
    }

    return mem[i] = min_jmp;
}

/* k-jump iterative
 * TC -> O(n * k)
 * SC => O(n) ==> dp array
*/
int solve_k_jump_iterative(int n, int k) {
    vector<int> dp(n);
    dp[0] = 0;
    for (int i = 1; i < n; ++i) {
        int min_jmp = INT_MAX;
        for (int j = 1; j <= k; ++j) {
            if (i-j >= 0) {
                int jmp = dp[i-j] + abs(a[i] - a[i-j]);
                min_jmp = min(min_jmp, jmp);
            }
        }
        dp[i] = min_jmp;
    }
    return dp[n-1];
}

int main() {
    a = { 30, 10, 60, 10, 60, 50 };
    int n = a.size();
    mem.resize(n, -1);

    cout << "memorization:  " << solve(n-1) << "\n";
    cout << "tabulation: " << solve_itarative(n) << "\n";
    cout << "space optm: " << solve_itarative_spaceOptimized(n) << "\n";

    mem.resize(n, -1);
    cout << "memorization_k: " << solve_k_jump(n-1, 3) << "\n";
    cout << "tabulation_k: " << solve_k_jump_iterative(n, 3);

    return 0;
}