#include <bits/stdc++.h>
using namespace std;

#define INF 0x3f3f3f3f

int main()
{
    int n = 12;
    vector<pair<int, int>> edges = {
        {1, 2}, {1, 3}, {1, 4},
        {2, 5},
        {3, 2}, {3, 6},
        {4, 7},
        {5, 2},
        {7, 1},
        {8, 9},
        {9, 10},
        {10, 7}, {10, 8},
        {11, 8}, {11, 9},
        {12, 11},
    };
    vector<vector<int>> G(n + 1), rG(n + 1);
    vector<int> cpn(n + 1);
    for(auto& [u, v]: edges) {
        G[u].push_back(v);
        rG[v].push_back(u);
    }

    vector<int> vs;
    vector<bool> visited(n + 1, false);

    auto dfs = [&](auto self, const int v) -> void {
        visited[v] = true;
        for(int u: G[v]) {
            if(not visited[u]) {
                self(self, u);
            }
        }
        vs.push_back(v);
    };

    auto rdfs = [&](auto self, const int v, const int k) -> void {
        visited[v] = true;
        cpn[v] = k;

        for(int u: rG[v]) {
            if(not visited[u]) {
                self(self, u, k);
            }
        }
    };

    for(int i = 1; i <= n; ++i) {
        if(not visited[i]) {
            dfs(dfs, i);
        }
    }

    visited.assign(n + 1, false);
    int k = 0;
    for(int i = n - 1; i >= 0; --i) {
        if(not visited[vs[i]]) {
            rdfs(rdfs, vs[i], k++);
        }
    }
    for(int i = 1; i <= n; ++i) {
        printf("%2d ", i);
    }
    printf("\n");
    for(int i = 1; i <= n; ++i) {
        printf("%2d ", cpn[i]);
    }
    printf("\n");
    return 0;
}
