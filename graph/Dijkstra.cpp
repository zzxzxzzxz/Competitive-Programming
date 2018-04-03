#include <bits/stdc++.h>
using namespace std;

#define INF 0x3f3f3f3f

const int MOD = 1000000007;
#define MAX_N 300005

struct edge {
    int to;
    int cost;
};

int V;
vector<edge> G[MAX_N];
int d[MAX_N];

void dijkstra(int s) {
    priority_queue<pair<int, int>,
                   vector<pair<int, int> >,
                   greater<pair<int, int> > > que;
    memset(d, INF, sizeof(d));
    d[s] = 0;
    que.push(make_pair(0, s));

    while(not que.empty()) {
        pair<int, int> p = que.top();
        que.pop();
        int v = p.second;
        if(d[v] < p.first) {
            continue;
        }
        for(int i = 0; i < (int)G[v].size(); i++) {
            edge& e = G[v][i];
            if(d[e.to] > d[v] + e.cost) {
                d[e.to] = d[v] + e.cost;
                que.push(make_pair(d[e.to], e.to));
            }
        }
    }
}

int main()
{
    V = 7;
    vector<vector<int> > g = {{0, 1, 2}, {0, 2, 5}, {1, 2, 4},
                              {1, 3, 6}, {2, 3, 2}, {1, 4, 10},
                              {3, 5, 1}, {4, 5, 3}, {4, 6, 5},
                              {5, 6, 9}};
    for(int i = 0; i < (int)g.size(); i++) {
        int u = g[i][0], v = g[i][1], cost = g[i][2];
        G[u].push_back(edge({v, cost}));
        G[v].push_back(edge({u, cost}));
    }
    dijkstra(0);
    printf("%d\n", d[6]);
    return 0;
}
