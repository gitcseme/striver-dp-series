#include <bits/stdc++.h>
using namespace std;

string s = "ab*cd";
string t = "abdefcd";

vector<vector<int>> mem;

/* Recursion:
 * TC -> exponential
 * SC -> O(n + m) auxiliary stack space
 * 
 * Memorization:
 * TC -> O(n * m)
 * SC -> O(n * m) + O(n+m) auxiliary stack space
*/
bool solve(int i, int j) {
    if (i < 0 && j < 0) return true;
    if (i < 0 && j >= 0) return false;
    if (j < 0 && i >= 0) {
        for (int k = i; k >= 0; --k) 
            if (s[k] != '*') return false;
        return true;
    }

    if (mem[i][j] != -1) return mem[i][j];
    
    if (s[i] == t[j] || s[i] == '?') {
        return mem[i][j] = (int)solve(i-1, j-1);
    }
    else if (s[i] == '*') {
        bool way1 = solve(i, j-1); // keep i in place of * and match more from j
        bool way2 = solve(i-1, j-1); // finished matched * and let match rest
        return mem[i][j] = (int)(way1 || way2);
    }
    return mem[i][j] = (int)false;
}

int main() {
    int n = s.length();
    int m = t.length();
    mem.resize(n, vector<int>(m, -1));

    cout << solve(n-1, m-1) << "\n";

    return 0;
}