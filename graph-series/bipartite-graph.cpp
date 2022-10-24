#include <bits/stdc++.h>
using namespace std;

/*  
    TC -> O(N+E)
    (BFS) -> SC -> O(N+E) + O(N) for queue + O(N) for color array
    (DFS) -> SC -> O(N+E) + O(N) for recursion stack + O(N) for color array
*/
int n = 10;

vector<vector<int>> g(n);
vector<int> color(n, -1);

bool bfsCheck(int i) {
    queue<int> q;
    q.push(i);
    color[i] = 1;

    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        for (int v : g[u]) {
            if (color[v] == -1) {
                color[v] = 1 - color[u];
                q.push(v);
            }
            else if (color[v] == color[u]) {
                return false;
            }
        }
    }
    return true;
}

bool dfsCheck(int u) {
    if (color[u] == -1) color[u] = 1;

    for (int v : g[u]) {
        if (color[v] == -1) {
            color[v] = 1 - color[u];
            if (dfsCheck(v) == false) 
                return false;
        }
        else if (color[v] == color[u])
            return false;
    }

    return true;
}

int main() {
    g[1] = {2};
    g[2] = {1, 3, 7};
    g[3] = {2, 4};
    g[4] = {3, 5};
    g[5] = {4, 6, 8};
    g[6] = {5, 7};
    g[7] = {2, 6};
    g[8] = {5};

    // there are multiple separated graph part hence looping
    bool bfsFlag = true;
    for (int i = 1; i <= 8; ++i) {
        if (color[i] == -1) {
            if (bfsCheck(i) == false) {
                bfsFlag = false;
                break;
            }
        }
    }
    if (bfsFlag) cout << "(BFS)-> Bipartite Graph!!" << "\n";

    fill(color.begin(), color.end(), -1);

    bool dfsFlag = true;
    for (int i = 1; i <= 8; ++i) {
        if (color[i] == -1) {
            if (dfsCheck(i) == false) {
                dfsFlag = false;
                break;
            }
        }
    }
    if (dfsFlag) cout << "(DFS)-> Bipartite Graph!!" << "\n";

    return 0;
    
}