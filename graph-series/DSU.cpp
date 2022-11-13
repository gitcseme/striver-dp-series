#include <bits/stdc++.h>
using namespace std;

int n = 100000;
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

int main() {
    makeSet();

    int edges, u, v;
    cin >> edges;
    while (edges--)
    {
        cin >> u >> v;
        unionSets(u, v);
    }

    int queries, a, b;
    cin >> queries;
    while (queries--)
    {
        cin >> a >> b;
        if (findParent(a) == findParent(b)) {
            cout << "Same component!!";
        }
        else {
            cout << "Different!!";
        }
    }
    
    return 0;
}