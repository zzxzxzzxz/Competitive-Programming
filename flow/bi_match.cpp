#include <bits/stdc++.h>
using namespace std;

const int INF = 0x3f3f3f3f;

struct MaxMatch {
    vector<vector<int>> G;
    vector<int> match;
    vector<char> used;

    MaxMatch(int V) {
        G.resize(V + 1);
        match.resize(V + 1);
        used.resize(V + 1);
    }

    void clear() {
        for(auto& es : G) {
            es.clear();
        }
    }

    void add(int u, int v) {
        G[u].push_back(v);
        G[v].push_back(u);
    }

    bool dfs(int v) {
        used[v] = true;
        for(int i = 0; i < (int)G[v].size(); i++) {
            int u = G[v][i], w = match[u];
            if(w < 0 or (not used[w] and dfs(w))) {
                match[v] = u;
                match[u] = v;
                return true;
            }
        }
        return false;
    }

    int solve() {
        int res = 0;
        fill(match.begin(), match.end(), -1);
        for(int v = 0; v < int(G.size()); v++) {
            if(match[v] < 0) {
                fill(used.begin(), used.end(), false);
                if(dfs(v)) {
                    ++res;
                }
            }
        }
        return res;
    }
};

int main() {
    vector<pair<int, int>> edges = {
        {1, 4},
        {1, 5},
        {2, 4},
        {2, 6},
        {3, 5},
    };
    int V = 7;
    auto mm = MaxMatch(V);

    for(auto [u, v] : edges) {
        mm.add(u, v);
    }
    int ans = mm.solve();
    cout << ans << endl;
    return 0;
}
