#include <bits/stdc++.h>
using namespace std;

// For top sort the graph should be a [DAG]
int n = 6;
vector<vector<int>> g(n);
vector<int> vis(n, 0);
stack<int> st;

void dfsTopSort(int u) {
    vis[u] = true;

    for (int v : g[u]) {
        if (!vis[v]) {
            dfsTopSort(v);
        }
    }
    st.push(u);
}

// Kahn's algo with BFS
vector<int> indegree(n, 0);

vector<int> bfsTopSort() {
    queue<int> q;
    for (int i = 0; i < n; ++i) {
        if (indegree[i] == 0) q.push(i);
    }

    vector<int> topSorted;
    while(!q.empty()) {
        int u = q.front();
        q.pop();
        topSorted.push_back(u);

        for (int v : g[u]) {
            indegree[v]--;
            if (indegree[v] == 0) {
                q.push(v);
            }
        }
    }

    return topSorted;
}


int main() {
    g[0] = {};
    g[1] = {};
    g[2] = {3};
    g[3] = {1};
    g[4] = {0, 1};
    g[5] = {0, 2};

    for (int i = 0; i < n; ++i) {
        if (!vis[i]) {
            dfsTopSort(i);
        }
    }

    vector<int> topSorted;
    while (!st.empty())
    {
        topSorted.push_back(st.top());
        st.pop();
    }
    
    cout << "DFS=> ";
    for (int x : topSorted) {
        cout << x << "-> ";
    }
    cout << "\n";


    // Kahn's algorithm with BFS counting in-degree
    for (int i = 0; i < n; ++i) {
        for (int j : g[i]) {
            indegree[j]++;
        }
    }

    auto ans = bfsTopSort();
    cout << "BFS=> ";
    for (int x : ans) {
        cout << x << "-> ";
    }
    cout << "\n";

    return 0;
}