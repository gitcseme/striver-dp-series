#include <bits/stdc++.h>
using namespace std;

vector<int> a;
int n;
vector<vector<int>> mem;

/* Memorization:
 * TC -> O(n*n)
 * SC -> O(n*n) + O(n+n) auxiliary stack space
*/

int solve(int i, int prev) {
    if (i >= n) return 0;
    if (mem[i][prev+1] != -1) return mem[i][prev+1];

    int take = 0;
    if (prev == -1 || a[i] % a[prev] == 0) {
        take = 1 + solve(i+1, i);
    }

    int not_take = solve(i+1, prev);

    return mem[i][prev+1] = max(take, not_take);
}

/* Algorithomic LIS dp
 * TC -> O(n^2)
 * SC -> O(n)
*/
pair<int, vector<int>> LDS_WITH_LIS_ALGO() {
    int n = a.size();
    sort(a.begin(), a.end());
    vector<int> dp(n, 1), path(n), lds;
    
    int maxi = 0, mx_ind = 0;
    for (int i = 0; i < n; ++i) {
        path[i] = i;
        for (int j = 0; j < i; ++j) {
            if (a[i]%a[j] == 0 && 1+dp[j] > dp[i]) {
                dp[i] = 1 + dp[j];
                path[i] = j;
            }
        }
        
        if (dp[i] > maxi) {
            maxi = dp[i];
            mx_ind = i;
        }
    }
    
    lds.push_back(a[mx_ind]);
    while(path[mx_ind] != mx_ind) {
        mx_ind = path[mx_ind];
        lds.push_back(a[mx_ind]);
    }
    reverse(lds.begin(), lds.end());
    
    return { maxi, lds };
}

int main() {
    a = { 1, 16, 7, 8, 4, 3, 9, 36, 18 };
    n = a.size();
    sort(a.begin(), a.end());
    mem.resize(n, vector<int>(n+1, -1));
    cout << solve(0, -1) << "\n";

    auto res = LDS_WITH_LIS_ALGO();
    cout << res.first << "\n";
    for (int x : res.second) {
        cout << x << " ";
    }
    cout << "\n";

    return 0;
}