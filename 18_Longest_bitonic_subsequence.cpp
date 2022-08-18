#include <bits/stdc++.h>
using namespace std;

vector<int> a;

int solve() {
    int n = a.size();
    vector<int> dpf(n, 1), dpr(n, 1);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < i; ++j) {
            if (a[j] < a[i] && 1 + dpf[j] > dpf[i]) {
                dpf[i] = 1 + dpf[j];
            }
        }
    }

    for (int i = n-1; i >= 0; --i) {
        for (int j = n-1; j > i; --j) {
            if (a[j] < a[i] && 1 + dpr[j] > dpr[i]) {
                dpr[i] = 1 + dpr[j];
            }
        }
    }

    int mx_bitonic = 1;
    for (int i = 0; i < n; ++i) {
        mx_bitonic = max(mx_bitonic, dpf[i] + dpr[i] - 1);
    }

    return mx_bitonic;
}

int main() {
    // a = { 1, 11, 2, 10, 4, 5, 2, 1 };
    a = { 9,8,1,7,6,5,4,3,2,1 };
    cout << solve() << "\n";

    return 0;
}