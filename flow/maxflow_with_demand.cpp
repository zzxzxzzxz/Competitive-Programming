#include <bits/stdc++.h>
using namespace std;

const int INF = 0x3f3f3f3f;
struct MaxFlow {/*{{{*/
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
};/*}}}*/
struct MaxFlowLB {/*{{{*/
    int s1, t1;
    MaxFlow mf;
    vector<int> din, dout;
    MaxFlowLB(int V):
        s1(V + 1), t1(V + 2), mf(MaxFlow(V + 2)), din(V + 1, 0), dout(V + 1, 0) {}

    void clear() {
        mf.clear();
        fill(din.begin(), din.end(), 0);
        fill(dout.begin(), dout.end(), 0);
    }

    void add(int from, int to, int cap, int demand) {
        mf.add(from, to, cap - demand);
        dout[from] += demand;
        din[to] += demand;
    }

    bool solve(int s, int t) {
        for(int v = 0; v < int(din.size()); ++v) {
            if(din[v] > 0) {
                mf.add(s1, v, din[v]);
            }
            if(dout[v] > 0) {
                mf.add(v, t1, dout[v]);
            }
        }
        mf.add(t, s, INF);

        mf.solve(s1, t1);
        for(auto& e : mf.G[s1]) {
            if(e.to < int(din.size()) and e.cap != 0) {
                return false;
            }
        }
        return true;
    }
};/*}}}*/

int main() {
    vector<int> M = {0, 1, 1, 2, 2};
    vector<int> m = {0, 0, 0, 0, 2};
    vector<string> r = {"",
        "[" + to_string(M[1]) + ", " + to_string(m[1]) + "]",
        "[" + to_string(M[2]) + ", " + to_string(m[2]) + "]",
        "[" + to_string(M[3]) + ", " + to_string(m[3]) + "]",
        "[" + to_string(M[4]) + ", " + to_string(m[4]) + "]",
    };

    cout << "          1  ---  3           "  << endl;
    cout <<r[1]<< "  /   \\   /   \\  " <<r[3]<< endl;
    cout << "       0      X      5        "  << endl;
    cout <<r[2]<< "  \\   /   \\   /  " <<r[4]<< endl;
    cout << "          2  ---  4           "  << endl;
    cout << endl;

    int V = 6;
    vector<tuple<int, int, int, int>> edges = {
        {0, 1, M[1], m[1]},
        {0, 2, M[2], m[2]},

        {1, 3, 1, 0},
        {1, 4, 1, 0},
        {2, 3, 1, 0},
        {2, 4, 1, 0},

        {3, 5, M[3], m[3]},
        {4, 5, M[4], m[4]},
    };

    auto mflb = MaxFlowLB(V);

    for(auto [a, b, cap, demand]: edges) {
        mflb.add(a, b, cap, demand);
    }

    int s = 0, t = 5;
    auto res = mflb.solve(s, t);

    if(not res) {
        cout << "No solution" << endl;
        return 0;
    }

    array<array<int, 2>, 2> ans = {};
    set<int> left = {1, 2}, right = {3, 4};
    for(int i : left) {
        for(auto& e : mflb.mf.G[i]) {
            if(right.count(e.to) and e.cap == 0) {
                ans[i - 1][e.to - 3] |= 1;
            }
        }
    }
    cout << "  3 4" << endl;
    for(int i = 0; i < 2; ++i) {
        cout << "12"[i] << " ";
        for(int j = 0; j < 2; ++j) {
            cout << ans[i][j] << " \n"[j];
        }
    }
    return 0;
}
