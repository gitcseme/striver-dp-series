#include <bits/stdc++.h>
using namespace std;

/*
    TC -> O(N+E)
    SC -> O(N+E) + O(N) for queue + O(N) for color array
*/
int n = 10;

vector<vector<int>> g(n);
vector<int> color(n, -1);

bool checkBipartiteBfs(int i) {
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
    for (int i = 1; i <= 8; ++i) {
        if (color[i] == -1) {
            if (checkBipartiteBfs(i) == false) {
                cout << "Not Bipartite!!" << "\n";
                return 0;
            }
        }
    }

    cout << "Bipartite Graph!!" << "\n";
    return 0;
    
}