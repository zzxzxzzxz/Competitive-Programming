#include <bits/stdc++.h>
using namespace std;

const int MOD = 1000000007;
#define MAX_N 300005
#define MAX_LOG_N 19

vector<int> G[MAX_N];
int pos[MAX_N], vs[MAX_N], depth[MAX_N];

void euler(int v, int p, int d, int& sz) {
    pos[v] = sz;
    vs[sz] = v;
    depth[sz] = d;
    ++sz;
    for(int u: G[v]) {
        if(u == p) {
            continue;
        }
        euler(u, v, d + 1, sz);
        vs[sz] = v;
        depth[sz] = d;
        ++sz;
    }
}

int lca(int a, int b) {
    int best = INT_MAX, best_v = -1;
    int l = min(pos[a], pos[b]);
    int r = max(pos[a], pos[b]);
    for(int i = l; i < r; ++i) {
        if(depth[i] < best) {
            best = depth[i];
            best_v = vs[i];
        }
    }
    return best_v;
}

int main() {
    int n = 5;
    vector<int> g = {1, 2, 1, 2};
    for(int i = 2; i <= n; i++) {
        int u = i, v = g[i - 2];
        G[u].push_back(v);
        G[v].push_back(u);
    }
    int root = 1, sz = 0;
    euler(root, -1, 0, sz);

    cout << lca(1, 2) << endl;
    cout << lca(3, 4) << endl;
    cout << lca(3, 5) << endl;
    return 0;
}
