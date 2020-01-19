#include <bits/stdc++.h>
using namespace std;

const int MOD = 1000000007;
#define MAX_N 5000
#define INF 0x3f3f3f3f

struct edge {
    int to, cap, rev;
};

vector<edge> G[MAX_N];
bool used[MAX_N];

void add_edge(int from, int to, int cap) {
    int i = G[from].size();
    int j = G[to].size();
    G[from].push_back((edge){to, cap, j});
    G[to].push_back((edge){from, 0, i});
}

int dfs(int v, int t, int f) {
    if(v == t) {
        return f;
    }
    used[v] = true;
    for(int i = 0; i < int(G[v].size()); i++) {
        edge &e = G[v][i];
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

int max_flow(int s, int t) {
    int flow = 0;

    int f = dfs(s, t, INF);
    while(f > 0) {
        flow += f;
        memset(used, 0, sizeof(used));
        f = dfs(s, t, INF);
    }
    return flow;
}

int main()
{
    vector<tuple<int, int, int>> E = {
        {0, 1, 10},
        {0, 2, 2},
        {1, 2, 6},
        {1, 3, 6},
        {3, 2, 3},
        {3, 4, 8},
        {2, 4, 5}
    };
    int s = 0, t = 4;
    for(auto& t: E) {
        int a, b, cap;
        tie(a, b, cap) = t;
        add_edge(a, b, cap);
    }
    int ans = max_flow(s, t);
    printf("%d\n", ans);
    return 0;
}
