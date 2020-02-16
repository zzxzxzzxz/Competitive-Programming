#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 300005;
const int MAX_LOG_N = 20;

vector<int> G[MAX_N];

struct LCA {
    vector<array<int, MAX_LOG_N>> parent;
    vector<int> depth;
    int n, root;

    LCA(int n, int root): n(n), root(root) {
        parent.resize(n);
        depth.resize(n);
        build();
    }

    void build() {
        dfs(root, -1, 0);
        for(int k = 0; k + 1 < MAX_LOG_N; k++) {
            for(int v = 0; v < n; v++) {
                if(parent[v][k] == -1) {
                    parent[v][k + 1] = -1;
                } else {
                    parent[v][k + 1] = parent[parent[v][k]][k];
                }
            }
        }
    }

    void dfs(int v, int p, int d) {
        parent[v][0] = p;
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
            if((depth[v] - depth[u]) & (1 << k)) {
                v = parent[v][k];
            }
        }
        if(u == v) {
            return u;
        }
        for(int k = MAX_LOG_N - 1; k >= 0; k--) {
            if(parent[u][k] != parent[v][k]) {
                u = parent[u][k];
                v = parent[v][k];
            }
        }
        return parent[u][0];
    }
};

int main()
{
    cout << "          1" << endl;
    cout << "         / \\" << endl;
    cout << "        2   4" << endl;
    cout << "       / \\   \\" << endl;
    cout << "      3   5   7" << endl;
    cout << "     / \\" << endl;
    cout << "    6   8" << endl;
    cout << endl;

    int n = 8;
    vector<int> p = {1, 2, 1, 2, 3, 4, 3};
    for(int i = 2; i <= n; i++) {
        int u = i, v = p[i - 2];
        G[u].push_back(v);
        G[v].push_back(u);
    }

    LCA lca(n + 1, 1);
    cout << "lca(6, 8): " << lca.get(6, 8) << endl;
    cout << "lca(6, 7): " << lca.get(6, 7) << endl;
    cout << "lca(2, 6): " << lca.get(2, 6) << endl;
    return 0;
}
