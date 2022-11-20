#include <bits/stdc++.h>
using namespace std;

int n = 8;
vector<vector<int>> adj(n);
vector<int> tin(n), low(n);
vector<bool> vis(n, false);

void dfs(int u, int parent, int time) {
    tin[u] = low[u] = ++time;
    vis[u] = true;

    for (int v : adj[u]) {
        if (v == parent) continue;

        if (!vis[v]) {
            dfs(v, u, time);
            low[u] = min(low[u], low[v]);

            if (low[v] > tin[u]) {
                cout << u << "-x-" << v << "\n";
            }
        }
        else {
            low[u] = min(low[u], tin[v]);
        }
    }
}

int main() {
    adj[1] = { 2, 3 };
    adj[2] = { 1, 3, 4 };
    adj[3] = { 1, 2, 6 };
    adj[4] = { 2, 5, 6 };
    adj[5] = { 4, 7 };
    adj[6] = { 3, 4 };
    adj[7] = { 5 };

    dfs(1, -1, 0);

    return 0;
}