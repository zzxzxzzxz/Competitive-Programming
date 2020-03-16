#include <bits/stdc++.h>
using namespace std;

using PII = pair<int, int>;
const int INF = 0x3f3f3f3f;
const int MAX_N = 300005;

struct edge {
    int to;
    int cost;
};

vector<edge> G[MAX_N];
int d[MAX_N];

void dijkstra(int s) {
    priority_queue<PII, vector<PII>, greater<PII>> pq;
    memset(d, INF, sizeof(d));
    d[s] = 0;
    pq.push({0, s});

    while(not pq.empty()) {
        int dist, v;
        tie(dist, v) = pq.top();
        pq.pop();
        if(d[v] < dist) {
            continue;
        }
        for(const edge& e: G[v]) {
            if(d[e.to] > d[v] + e.cost) {
                d[e.to] = d[v] + e.cost;
                pq.push({d[e.to], e.to});
            }
        }
    }
}

int main() {
    vector<array<int, 3>> g = {
        {0, 1, 2}, {0, 2, 5}, {1, 2, 4}, {1, 3, 6}, {2, 3, 2},
        {1, 4, 10}, {3, 5, 1}, {4, 5, 3}, {4, 6, 5}, {5, 6, 9},
    };
    for(const auto& e : g) {
        int u, v, cost;
        tie(u, v, cost) = e;
        G[u].push_back(edge{ v, cost });
        G[v].push_back(edge{ u, cost });
    }
    dijkstra(0);
    cout << d[6] << endl;
    return 0;
}
