#include <bits/stdc++.h>
using namespace std;

string a, b;
int n, m;

int solve(int i, int j, int count) {
    if (i < 0 || j < 0) return count;

    int ans = 0;
    if (a[i] == b[j]) {
        ans = solve(i-1, j-1, count + 1);
    }
    
    int x = solve(i-1, j, 0);
    int y = solve(i, j-1, 0);

    cout << ans << " " << x << " " << y << endl;

    ans = max(ans, max(x, y));

    return ans;
}

// int solve_tabulation(int n, int m) {

// }

int main() {
    a = "abcdxyz";
    b = "xyzabcd";
    n = a.length();
    m = b.length();

    cout << solve(n-1, m-1, 0) << "\n";

    return 0;
}