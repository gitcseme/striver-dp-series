#include <bits/stdc++.h>
using namespace std;
int n = 10;
vector<vector<int>> g(n);
vector<bool> vis(n, 0), dfsVis(n, 0);

/**
 * TC -> O(N+E)
 * SC -> O(2N) + O(N) auxiliary stack stape
*/

bool dfsCycle(int u) {
    vis[u] = dfsVis[u] = true;

    for (int v : g[u]) {
        if (!vis[v]) {
            if (dfsCycle(v)) return true;
        }
        else if (dfsVis[v]) {
            cout << "cycle at: " << v << "\n";
            return true;
        }
    }
    dfsVis[u] = false;
    return false;
}

int main() {
    // graph has multiple connected components
    g[1] = {2};
    g[2] = {3};
    g[3] = {4, 6};
    g[4] = {5};
    g[5] = {};
    g[6] = {5};
    g[7] = {2, 8};
    g[8] = {9};
    g[9] = {7};

    bool dfsFlag = false;
    for (int i = 1; i < n; ++i) {
        if (!vis[i]) {
            if (dfsCycle(i)) {
                dfsFlag = true;
                break;
            }
        }
    }

    if (dfsFlag) cout << "(DFS)-> Cycle detected!!" << "\n";

    // fill(vis.begin(), vis.end(), false);

    // for (int i = 1; i < 12; ++i) {
    //     if (vis[i] == false) {
    //         if (dfsCycle(i, -1)) {
    //             cout << "DFS Cycle detected!!" << "\n";
    //             return 0;
    //         }
    //     }
    // }

    else cout << "No cycle!!" << "\n";

    return 0;
}