#include<bits/stdc++.h>
using namespace std;

vector<int> price, wt;
vector<vector<int>> mem;

/* Recursion
 * TC -> O(2^n)
 * SC -> O(n)
 * 
 * Memorization
 * TC -> O(n * W)
 * SC -> O(n * W) mem array + O(n) stack space
*/
int solve(int i, int W) {
    if (i == 0) {
        if (wt[0] <= W) return price[0];
        return 0;
    }

    if (mem[i][W] != -1) return mem[i][W];

    int not_taken = solve(i-1, W);
    int taken = INT_MIN;
    if (wt[i] <= W)
        taken = price[i] + solve(i-1, W - wt[i]);

    return mem[i][W] = max(not_taken, taken);
}

int main() {
    wt = { 3, 2, 5 };
    price = { 30, 40, 60 };

    int n = wt.size();
    int W = 6;
    mem.resize(n, vector<int>(W+1, -1));

    cout << "memorization: " << solve(n-1, W) << "\n";
}