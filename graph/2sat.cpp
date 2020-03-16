#include <bits/stdc++.h>
using namespace std;

struct SAT {//{{{
    vector<vector<int>> G;
    vector<int> vs;
    vector<char> color, visited;
    int V;
    SAT(int V): V(V) {
        G.resize((V + 1) * 2);
        color.resize((V + 1) * 2);
        visited.resize((V + 1) * 2);
    }

    void clear() {
        for(auto& es : G) {
            es.clear();
        }
    }

    void add(int i, bool b) {
        int v = i * 2 + b;
        G[v ^ 1].push_back(v);
    }

    void add(int i1, bool b1, int i2, bool b2) {
        int v1 = i1 * 2 + b1, v2 = i2 * 2 + b2;
        G[v1 ^ 1].push_back(v2);
        G[v2 ^ 1].push_back(v1);
    }

    void dfs(int v) {
        visited[v] = true;
        for(int u: G[v]) {
            if(not visited[u]) {
                dfs(u);
            }
        }
        vs.push_back(v);
    }

    bool assign(int v) {
        if(visited[v]) return color[v];
        visited[v] = true;
        color[v] = true;

        for(int u: G[v]) {
            if(not assign(u)) {
                return false;
            }
        }
        return true;
    }

    vector<char> solve() {
        vs.clear();
        fill(visited.begin(), visited.end(), false);
        for(int i = 0; i < int(G.size()); ++i) {
            if(not visited[i]) {
                dfs(i);
            }
        }
        reverse(vs.begin(), vs.end());

        fill(visited.begin(), visited.end(), false);
        for(auto i : vs) {
            if(not visited[i]) {
                visited[i] = true;
                color[i] = false;
                if(not assign(i ^ 1)) {
                    return {};
                }
            }
        }
        vector<char> res;
        for(int v = 0; v < V; ++v) {
            res.push_back(color[v * 2 + 1]);
        }
        return res;
    }
};//}}}

int main() {
    auto show = [](vector<char>& res) {
        if(res.empty()) {
            cout << "No solutions" << endl;
        } else {
            cout << bool(res[1]) << " "
                 << bool(res[2]) << " "
                 << bool(res[3]) << endl;
        }
    };

    auto sat = SAT(3);
    sat.add(1, false);
    sat.add(1, true, 2, true);
    sat.add(2, false, 3, false);
    auto res = sat.solve();
    show(res);

    sat.add(3, true);
    res = sat.solve();
    show(res);
    return 0;
}
