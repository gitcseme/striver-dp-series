#include <bits/stdc++.h>
using namespace std;

int n = 9;
int INF = 999999;

vector<vector<int>> g(n);
vector<int> dist(n, INF);

void shortestPathBFS(int src) {
    queue<int> q;
    q.push(src);
    dist[src] = 0;

    while (!q.empty())
    {
        int u = q.front();
        q.pop();

        for (int v : g[u]) {
            if (dist[u] + 1 < dist[v]) {
                dist[v] = dist[u] + 1;
                q.push(v);
            }
        }
    }
}

int main() {
    g[0] = {1, 3};
    g[1] = {0, 2, 3};
    g[2] = {1, 6};
    g[3] = {0, 4};
    g[4] = {3, 5};
    g[5] = {4, 6};
    g[6] = {2, 5, 7, 8};
    g[7] = {6, 8};
    g[8] = {6, 7};

    shortestPathBFS(0);

    for (int i = 0; i < n; ++i) {
        cout << 0 << "->" << i << " => " << dist[i] << "\n";
    }

    return 0;
}