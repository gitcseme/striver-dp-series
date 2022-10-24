#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> g(12);
vector<bool> vis(12, 0);

bool bfsCycle(int i) {
    queue<pair<int, int>> q;
    vis[i] = true;
    q.push({i, -1});

    while (!q.empty())
    {
        int u = q.front().first;
        int parent = q.front().second;
        q.pop();

        for (int v : g[u])
        {
            if (!vis[v]) {
                vis[v] = true;
                q.push({v, u});
            }
            else if (v != parent) {
                cout << "bfs cycle ends: " << v << "\n";
                return true; // encountered cycle
            }
        }
        
    }
    return false;
}

bool dfsCycle(int u, int parent) {
    vis[u] = true;

    for (int v : g[u]) {
        if (!vis[v]) {
            if (dfsCycle(v, u)) return true;
        }
        else if (v != parent) {
            cout << "cycle at: " << v << "\n";
            return true; // encountered cycle
        }
    }
    return false;
}

int main() {
    // graph has multiple connected components
    g[1] = {2};
    g[2] = {1, 4};
    g[3] = {5};
    g[4] = {2};
    g[5] = {3, 10, 6};
    g[6] = {5, 7};
    g[7] = {6, 8};
    g[8] = {7, 9, 11};
    g[9] = {10, 8};
    g[10] = {5, 9};
    g[11] = {8};

    for (int i = 1; i < 12; ++i) {
        if (!vis[i]) {
            if (bfsCycle(i)) {
                cout << "BFS Cycle detected!!" << "\n";
                break;
            }
        }
    }

    fill(vis.begin(), vis.end(), false);

    for (int i = 1; i < 12; ++i) {
        if (vis[i] == false) {
            if (dfsCycle(i, -1)) {
                cout << "DFS Cycle detected!!" << "\n";
                return 0;
            }
        }
    }

    cout << "No cycle!!";

    return 0;
}