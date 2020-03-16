#include <bits/stdc++.h>
using namespace std;

using PII = pair<int, int>;
const int INF = 0x3f3f3f3f;

struct MinCostFlow {
    struct edge {
        int to, cap, cost, rev;
    };
    vector<vector<edge>> G;
    vector<int> h, d, prevv, preve;

    MinCostFlow(int V) {
        G.resize(V + 1);
        h.resize(V + 1);
        d.resize(V + 1);
        prevv.resize(V + 1);
        preve.resize(V + 1);
    }

    void clear() {
        for(auto& es : G) {
            es.clear();
        }
    }

    void add(int from, int to, int cap, int cost) {
        int i = G[from].size();
        int j = G[to].size();
        G[from].push_back({to, cap, cost, j});
        G[to].push_back({from, 0, -cost, i});
    }

    int solve(int s, int t, int required) {
        int res = 0;
        fill(h.begin(), h.end(), 0);
        while(required > 0) {
            fill(d.begin(), d.end(), INF);
            d[s] = 0;
            priority_queue<PII, vector<PII>, greater<PII>> pq;
            pq.push({0, s});
            while(not pq.empty()){
                auto [dist, v] = pq.top();
                pq.pop();
                if(dist > d[v]) {
                    continue;
                }
                for(int i = 0; i < int(G[v].size()); i++){
                    edge& e = G[v][i];
                    if(e.cap > 0 and d[e.to] > d[v] + e.cost + h[v] - h[e.to]){
                        d[e.to] = d[v] + e.cost + h[v] - h[e.to];
                        prevv[e.to] = v;
                        preve[e.to] = i;
                        pq.push({d[e.to], e.to});
                    }
                }
            }
            if(d[t] == INF) {
                return -1;
            }
            for(int i = 0; i < int(h.size()); i++) {
                h[i] += d[i];
            }
            int flow = required;
            for(int v = t; v != s; v = prevv[v]) {
                edge& e = G[prevv[v]][preve[v]];
                flow = min(flow, e.cap);
            }
            required -= flow;
            res += flow * h[t];

            for(int v = t; v != s; v = prevv[v]) {
                edge& e = G[prevv[v]][preve[v]];
                e.cap -= flow;
                G[v][e.rev].cap += flow;
            }
        }
        return res;
    }
};

int main() {
    int V = 5;
    vector<tuple<int, int, int, int>> edges = {
        {0, 1, 10, 2},
        {0, 2, 2, 4},
        {1, 2, 6, 6},
        {1, 3, 6, 2},
        {3, 2, 3, 3},
        {3, 4, 8, 6},
        {2, 4, 5, 2}
    };

    auto mcf = MinCostFlow(V);

    int s = 0, t = 4, f = 9;
    for(auto [a, b, cap, cost]: edges) {
        mcf.add(a, b, cap, cost);
    }
    int ans = mcf.solve(s, t, f);
    cout << ans << endl;
    return 0;
}
