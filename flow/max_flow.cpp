#include <bits/stdc++.h>
using namespace std;

const int MOD = 1000000007;
#define MAX_N 5000
#define INF 0x3f3f3f3f

struct edge {
    int to, cap, rev;
};

vector<edge> G[MAX_N];
int level[MAX_N];
int iter[MAX_N];

void add_edge(int from, int to, int cap) {
    int i = G[from].size();
    int j = G[to].size();
    G[from].push_back((edge){to, cap, j});
    G[to].push_back((edge){from, 0, i});
}

void bfs(int s) {
    memset(level, -1, sizeof(level));
    queue<int> que;
    level[s] = 0;
    que.push(s);
    while(!que.empty()) {
        int v = que.front();
        que.pop();
        for(int i = 0; i < int(G[v].size()); i++) {
            edge &e = G[v][i];
            if(e.cap > 0 and level[e.to] < 0) {
                level[e.to] = level[v] + 1;
                que.push(e.to);
            }
        }
    }
}

int dfs(int v, int t, int f) {
    if(v == t) {
        return f;
    }
    for(int &i = iter[v]; i < int(G[v].size()); i++) {
        edge &e = G[v][i];
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

int max_flow(int s, int t) {
    int flow = 0;
    while(true) {
        bfs(s);
        if(level[t] < 0) {
            return flow;
        }
        memset(iter, 0, sizeof(iter));
        int f = dfs(s, t, INF);
        while(f > 0) {
            flow += f;
            f = dfs(s, t, INF);
        }
    }
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
