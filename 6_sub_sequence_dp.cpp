#include<bits/stdc++.h>
using namespace std;

vector<int> a;
vector<vector<int>> mem;
int target;

/* Recursion
 * TC -> O(2^n)
 * SC -> O(n) stack space
 * 
 * Memorization
 * TC -> O(n*target)
 * SC -> O(n*target) mem array + O(n) stack space
*/

bool solve(int i, int target) {
    if (target == 0) return true;
    if (i == 0) return a[0] == target;

    if (mem[i][target] != -1) return mem[i][target];

    int not_taken = solve(i-1, target);
    int taken = false;
    if (!not_taken && target >= a[i]) {
        taken = solve(i-1, target-a[i]);
    }

    return mem[i][target] = (int)(not_taken || taken);
}

int main()
{
    a = { 1, 3, 4, 6, 2, 1 };
    target = 7;
    int n = a.size();
    mem.resize(n, vector<int>(target+1, -1));

    cout << "memorization: " << solve(n-1, target) << "\n";
}