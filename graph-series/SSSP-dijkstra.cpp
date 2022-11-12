#include <bits/stdc++.h>
using namespace std;

int n = 6;
int INF = 999999;
vector<int> dist(n, INF);
vector<vector<pair<int, int>>> g(n);

void dijkstra(int src) {
    dist[src] = 0;
    priority_queue<pair<int, int>> pq;
    pq.push({0, src});


    while (!pq.empty())
    {
        int u = pq.top().second;
        int du = pq.top().first;
        pq.pop();

        for (pair<int, int> child : g[u])
        {
            int v = child.first;
            int dv = child.second;

            if (du + dv < dist[v]) {
                dist[v] = du + dv;
                pq.push({dist[v], v});
            }
        }
    }
}

int main() {
    g[1] = {{2, 2}, {4, 1}};
    g[2] = {{1, 2}, {5, 5}, {3, 4}};
    g[3] = {{2, 4}, {4, 3}, {5, 1}};
    g[4] = {{1, 1}, {3, 3}};
    g[5] = {{2, 5}, {3, 1}};

    int src = 1;
    dijkstra(src); 

    for (int i = 1; i < n; ++i) {
        cout << src << "->" << i << " => " << dist[i] << "\n";
    }

    return 0;
}