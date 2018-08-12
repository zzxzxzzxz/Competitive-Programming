#include <bits/stdc++.h>
using namespace std;

const int MOD = 1000000007;
#define MAX_N 300005
#define MAX_LOG_N 19

vector<int> G[MAX_N];
const int root = 1;
int parent[MAX_LOG_N][MAX_N];
int depth[MAX_N];

struct LCA {
    int n;
    LCA(int n_) {
        n = n_;
    }

    void build() {
        dfs(root, -1, 0);
        for(int k = 0; k + 1 < MAX_LOG_N; k++) {
            for(int v = 0; v < n; v++) {
                if(parent[k][v] < 0) {
                    parent[k + 1][v] = -1;
                } else {
                    parent[k + 1][v] = parent[k][parent[k][v]];
                }
            }
        }
    }

    void dfs(int v, int p, int d) {
        parent[0][v] = p;
        depth[v] = d;
        for(int i = 0; i < (int)G[v].size(); i++) {
            if(G[v][i] != p) {
                dfs(G[v][i], v, d + 1);
            }
        }
    }

    int get(int u, int v) {
        if(depth[u] > depth[v]) {
            swap(u, v);
        }
        for(int k = 0; k < MAX_LOG_N; k++) {
            if((depth[v] - depth[u]) >> k & 1) {
                v = parent[k][v];
            }
        }
        if(u == v) {
            return u;
        }
        for(int k = MAX_LOG_N - 1; k >= 0; k--) {
            if(parent[k][u] != parent[k][v]) {
                u = parent[k][u];
                v = parent[k][v];
            }
        }
        return parent[0][u];
    }
};

int main()
{
    int n = 5;
    LCA lca(n + 1);
    vector<int> g = {1, 2, 1, 2};
    for(int i = 2; i <= n; i++) {
        int u = i, v = g[i-2];
        G[u].push_back(v);
        G[v].push_back(u);
    }
    lca.build();
    cout << lca.get(1, 2) << endl;
    cout << lca.get(3, 4) << endl;
    cout << lca.get(3, 5) << endl;
    return 0;
}
