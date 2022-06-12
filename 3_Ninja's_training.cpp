/*
    Ninja can perform 1 task among 3 in a given day.
    But can't perform the same in consecutuve days.
    Find the maximum training points he can obtain.
*/

#include <bits/stdc++.h>
using namespace std;

int n;
vector<vector<int>> a;
vector<vector<int>> mem;

int getMaxWithout(int last) {
    int maxp = 0;
    for (int i = 0; i < 3; ++i) if (i != last) {
        maxp = max(maxp, a[0][i]);
    }
    return maxp;
}

int solve(int day, int last) {
    if (day == 0) return getMaxWithout(last);

    if (mem[day][last] != -1) return mem[day][last];

    int maxPoints = 0;
    for (int i = 0; i < 3; ++i) {
        if (i == last) continue;
        int points = a[day][i] + solve(day-1, i);
        maxPoints = max(maxPoints, points);
    }

    return mem[day][last] = maxPoints;
}

int main() {
    n = 4;
    mem.resize(n, vector<int>(4, -1));
    a = {
        { 2, 1, 3 },
        { 3, 4, 6 },
        { 10,1, 6 },
        { 8, 3, 7 }
    };

    cout << "memorization: " << solve(n-1, 3) << "\n";

    return 0;
}