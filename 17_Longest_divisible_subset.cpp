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

int main() {
    a = { 1, 16, 7, 8, 4, 3, 9, 36, 18 };
    n = a.size();
    sort(a.begin(), a.end());
    mem.resize(n, vector<int>(n+1, -1));

    cout << solve(0, -1) << "\n";
}