#include <bits/stdc++.h>
using namespace std;

using PII = pair<int, int>;

#define INF 0x3f3f3f3f

const int MOD = 1000000007;
#define MAX_N 5000

struct edge {
    int to, cap, cost, rev;
};

int V;
vector<edge> G[MAX_N];
int h[MAX_N];
int d[MAX_N];
int prevv[MAX_N], preve[MAX_N];

void add_edge(int from, int to, int cap, int cost) {
    int i = G[from].size();
    int j = G[to].size();
    G[from].push_back({to, cap, cost, j});
    G[to].push_back({from, 0, -cost, i});
}

int min_cost_flow(int s, int t, int f) {
    int res = 0;
    memset(h, 0, sizeof(h));
    while(f > 0){
        priority_queue<PII, vector<PII>, greater<PII> > que;
        memset(d, INF, sizeof(d));
        d[s] = 0;
        que.push({0, s});
        while(not que.empty()){
            auto [dist, v] = que.top();
            que.pop();
            if(d[v] < dist) {
                continue;
            }
            for(int i = 0; i < int(G[v].size()); i++){
                edge& e = G[v][i];
                if(e.cap > 0 and d[e.to] > d[v] + e.cost + h[v] - h[e.to]){
                    d[e.to] = d[v] + e.cost + h[v] - h[e.to];
                    prevv[e.to] = v;
                    preve[e.to] = i;
                    que.push({d[e.to], e.to});
                }
            }
        }
        if(d[t] == INF) {
            return -1;
        }
        for(int i = 0; i < V; i++) {
            h[i] += d[i];
        }
        int d = f;
        for(int v = t; v != s; v = prevv[v]) {
            edge& e = G[prevv[v]][preve[v]];
            d = min(d, e.cap);
        }
        f -= d;
        res += d * h[t];
        for(int v = t; v != s; v = prevv[v]) {
            edge& e = G[prevv[v]][preve[v]];
            e.cap -= d;
            G[v][e.rev].cap += d;
        }
    }
    return res;
}

int main()
{
    vector<tuple<int, int, int, int>> E = {
        {0, 1, 10, 2},
        {0, 2, 2, 4},
        {1, 2, 6, 6},
        {1, 3, 6, 2},
        {3, 2, 3, 3},
        {3, 4, 8, 6},
        {2, 4, 5, 2}
    };
    V = 5;
    int s = 0, t = 4, f = 9;
    for(auto& e: E) {
        auto [a, b, cap, cost] = e;
        add_edge(a, b, cap, cost);
    }
    int ans = min_cost_flow(s, t, f);
    printf("%d\n", ans);
    return 0;
}
