#include <bits/stdc++.h>
using namespace std;

const int INF = 0x3f3f3f3f;

struct MaxFlow {//{{{
    struct edge {
        int to, cap, rev;
    };

    vector<vector<edge>> G;
    vector<char> used;

    MaxFlow(int V) {
        G.resize(V + 1);
        used.resize(V + 1);
    }

    void clear() {
        for(auto& es : G) {
            es.clear();
        }
    }

    void add(int from, int to, int cap) {
        int i = G[from].size();
        int j = G[to].size();
        G[from].push_back({to, cap, j});
        G[to].push_back({from, 0, i});
    }

    int dfs(int v, int t, int f) {
        if(v == t) {
            return f;
        }
        used[v] = true;
        for(auto& e : G[v]) {
            if(not used[e.to] and e.cap > 0) {
                int d = dfs(e.to, t, min(f, e.cap));
                if(d > 0) {
                    e.cap -= d;
                    G[e.to][e.rev].cap += d;
                    return d;
                }
            }
        }
        return 0;
    }

    int solve(int s, int t) {
        int flow = 0;
        fill(used.begin(), used.end(), false);
        int f = dfs(s, t, INF);
        while(f > 0) {
            flow += f;
            fill(used.begin(), used.end(), false);
            f = dfs(s, t, INF);
        }
        return flow;
    }
};//}}}

int main() {
    int V = 5;
    vector<tuple<int, int, int>> edges = {
        {0, 1, 10},
        {0, 2, 2},
        {1, 2, 6},
        {1, 3, 6},
        {3, 2, 3},
        {3, 4, 8},
        {2, 4, 5}
    };

    auto mf = MaxFlow(V);

    for(auto [a, b, cap]: edges) {
        mf.add(a, b, cap);
    }
    int s = 0, t = 4;
    int ans = mf.solve(s, t);
    cout << ans << endl;
    return 0;
}
