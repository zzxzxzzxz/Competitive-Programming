#include <bits/stdc++.h>
using namespace std;

const int INF = 0x3f3f3f3f;

struct MaxFlow {//{{{
    struct edge {
        int to, cap, rev;
    };
    vector<vector<edge>> G;
    vector<int> level, iter;

    MaxFlow(int V) {
        G.resize(V + 1);
        level.resize(V + 1);
        iter.resize(V + 1);
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

    void bfs(int s) {
        fill(level.begin(), level.end(), -1);
        level[s] = 0;
        deque<int> que = {s};
        while(not que.empty()) {
            int v = que.front();
            que.pop_front();
            for(auto& e : G[v]) {
                if(e.cap > 0 and level[e.to] < 0) {
                    level[e.to] = level[v] + 1;
                    que.emplace_back(e.to);
                }
            }
        }
    }

    int dfs(int v, int t, int f) {
        if(v == t) {
            return f;
        }
        for(int& i = iter[v]; i < int(G[v].size()); i++) {
            auto& e = G[v][i];
            if(e.cap > 0 and level[v] < level[e.to]) {
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
        bfs(s);
        while(level[t] != -1) {
            fill(iter.begin(), iter.end(), 0);
            int f = dfs(s, t, INF);
            while(f > 0) {
                flow += f;
                f = dfs(s, t, INF);
            }
            bfs(s);
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
