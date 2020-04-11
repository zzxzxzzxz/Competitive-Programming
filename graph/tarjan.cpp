#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 200005;
vector<int> G[MAX_N];

vector<int> ssc(int V) {
    vector<int> ids, low, stk;
    vector<bool> in_stack;

    ids.assign(V + 1, -1);
    low.resize(V + 1);
    in_stack.assign(V + 1, false);

    auto dfs = [&](auto self, int v, int& id) -> void {
        in_stack[v] = true;
        stk.push_back(v);
        ids[v] = low[v] = id++;

        for(int u : G[v]) {
            if(ids[u] == -1) {
                self(self, u, id);
            }
            if(in_stack[u]) {
                low[v] = min(low[v], low[u]);
            }
        }

        if(ids[v] == low[v]) {
            while(stk.back() != v) {
                in_stack[stk.back()] = false;
                stk.pop_back();
            }
            in_stack[v] = false;
            stk.pop_back();
        }
    };

    int id = 0;
    for(int i = 1; i <= V; ++i) {
        if(ids[i] == -1) {
            dfs(dfs, i, id);
        }
    }
    return low;
}

int main() {
    int n = 12;
    vector<pair<int, int>> edges = {
        {1, 2}, {1, 3}, {1, 4},
        {2, 5},
        {3, 2}, {3, 6},
        {4, 7},
        {5, 2},
        {7, 1},
        {8, 9},
        {9, 10},
        {10, 7}, {10, 8},
        {11, 8}, {11, 9},
        {12, 11},
    };

    for(auto& e: edges) {
        int u, v;
        tie(u, v) = e;
        G[u].push_back(v);
    }

    auto cpn = ssc(n);

    for(int i = 1; i <= n; ++i) {
        printf("%2d ", i);
    }
    printf("\n");
    for(int i = 1; i <= n; ++i) {
        printf("%2d ", cpn[i]);
    }
    printf("\n");
    return 0;
}
