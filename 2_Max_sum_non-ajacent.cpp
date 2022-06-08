/*
    Maximum sum of non adjacent elements
*/

#include <bits/stdc++.h>
using namespace std;

vector<int> a;
vector<int> mem;

int solve(int i) {
    if (i == 0) return a[0];
    if (i < 0) return 0;

    if (mem[i] != -1) return mem[i];

    int taken = a[i] + solve(i-2);
    int leave = solve(i-1);

    return mem[i] = max(taken, leave);
}

int main() {
    a = { 2, 1, 4, 9 };
    int n = a.size();
    mem.resize(n, -1);

    cout << "memorization: " << solve(n-1) << "\n";
}