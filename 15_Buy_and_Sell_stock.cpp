#include <bits/stdc++.h>
using namespace std;

vector<int> prices;
int n;
vector<vector<int>> mem;

/* Recursion:
 * TC -> O(2^n)
 * SC -> O(n) auxiliary stack space
 * 
 * Memorization:
 * TC -> O(n*2)
 * SC -> O(n) O(n) auxiliary stack space
*/
int solve(int i, int bought) {
    if (i == n) return 0;

    if (mem[i][bought] != -1) return mem[i][bought];

    int profit;
    if (!bought) {
        int buy = -prices[i] + solve(i+1, 1);
        int not_buy = solve(i+1, 0);
        profit = max(buy, not_buy);
    }
    else {
        int sell = prices[i] + solve(i+1, 0);
        int not_sell = solve(i+1, 1);
        profit = max(sell, not_sell);
    }

    return mem[i][bought] = profit;
}

int main() {
    prices = { 7, 1, 5, 3, 6, 4 };
    n = prices.size();
    mem.resize(n, vector<int>(2, -1));

    cout << solve(0, 0) << "\n";
}