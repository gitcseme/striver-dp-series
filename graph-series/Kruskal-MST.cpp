#include <bits/stdc++.h>
using namespace std;
typedef pair<int, pair<int, int>> pipii;

vector<pipii> edges;

int n = 7;
vector<int> parent(n);
vector<int> rnk(n);

void makeSet() {
    for (int i = 1; i < n; ++i) {
        parent[i] = i;
        rnk[i] = 0;
    }
}

// Find parent with path compression
int findParent(int node) {
    if (parent[node] == node) {
        return node;
    }
    return parent[node] = findParent(parent[node]);
}

void unionSets(int u, int v) {
    u = findParent(u);
    v = findParent(v);

    if (rnk[u] < rnk[v]) {
        parent[u] = v;
    }
    else if (rnk[u] > rnk[v]) {
        parent[v] = u;
    }
    else {
        parent[v] = u;
        rnk[u]++;
    }
}

vector<pipii> kruskalMst() {
    makeSet();
    sort(edges.begin(), edges.end(), less<pipii>());
    vector<pipii> mstEdges;

    for(pipii edge : edges) {
        int u = edge.second.first;
        int v = edge.second.second;
        if (findParent(u) != findParent(v)) {
            mstEdges.push_back(edge);
            unionSets(u, v);
        }
    }

    return mstEdges;
}

int main() {
    edges.push_back({9, {4, 5}});
    edges.push_back({2, {1, 2}});
    edges.push_back({4, {1, 5}});
    edges.push_back({7, {2, 6}});
    edges.push_back({3, {2, 4}});
    edges.push_back({1, {1, 4}});
    edges.push_back({5, {3, 4}});
    edges.push_back({8, {3, 6}});
    edges.push_back({3, {2, 3}});

    vector<pipii> mstEdges = kruskalMst();
    int totalCost = 0;
    cout << "MST:\n";
    for(pipii edge : mstEdges) {
        totalCost += edge.first;
        cout << edge.second.first << ", " << edge.second.second << "\n";
    }

    cout << "MST Cost: " << totalCost << "\n";

    return 0;
}