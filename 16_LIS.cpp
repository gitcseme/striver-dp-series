#include <bits/stdc++.h>
using namespace std;

vector<int> a;
int n;
vector<vector<int>> mem;

/* Recursion:
 * TC -> O(2^n)
 * SC -> O(n + n) auxiliary stack space
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

/* binary search 
 * TC -> O(n * log(n))
 * SC -> O(n)
*/
int LIS_binary_search() {
    int n = a.size();
    vector<int> tmp = { a[0] };

    for (int i = 1; i < n; ++i) {
        if (a[i] > tmp.back()) {
            tmp.push_back(a[i]);
        }
        else {
            int idx = lower_bound(tmp.begin(), tmp.end(), a[i]) - tmp.begin();
            tmp[idx] = a[i];
        }
    }
    return tmp.size();
}

vector<int> path;
pair<int, vector<int>> LIS_Itarative() {
    int n = a.size();
    vector<int> dp(n, 1);
    path.resize(n);

    int maxi = 1, max_ind = 0;

    for (int i = 0; i < n; ++i) {
        path[i] = i;

        for (int j = 0; j < i; ++j) {
            if (a[j] < a[i] && 1 + dp[j] > dp[i]) {
                dp[i] = 1 + dp[j];
                path[i] = j;
            }
            if (dp[i] > maxi) {
                maxi = dp[i];
                max_ind = i;
            }
        }
    }

    vector<int> lis = { a[max_ind] };
    while (path[max_ind] != max_ind) {
        max_ind = path[max_ind];
        lis.push_back(a[max_ind]);
    }
    reverse(lis.begin(), lis.end());
    return { maxi, lis };
}

int main() {
    a = { 10, 9, 2, 5, 3, 7, 101, 18 };
    n = a.size();
    mem.resize(n, vector<int>(n+1, -1));

    cout << solve(0, -1) << "\n";
    cout << solve2(0, -1) << "\n";
    cout << solve_tabulation(n)<< "\n";
    cout << LIS_binary_search()<< "\n";
    
    pair<int, vector<int>> data = LIS_Itarative();
    cout << data.first << "\n";
    for(int x : data.second) {
        cout << x << " ";
    }
    cout << "\n";
}