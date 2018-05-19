#include <bits/stdc++.h>
using namespace std;

const int MOD = 1000000007;
#define MAX_N 5000
#define INF 0x3f3f3f3f

int V = 0;
vector<int> G[MAX_N];
int match[MAX_N];
bool used[MAX_N];

void add_edge(int u, int v) {
    V = max(max(V, u + 1), v + 1);
    G[u].push_back(v);
    G[v].push_back(u);
}

bool dfs(int v) {
    used[v] = true;
    for(int i = 0; i < (int)G[v].size(); i++) {
        int u = G[v][i], w = match[u];
        if(w < 0 or (not used[w] and dfs(w))) {
            match[v] = u;
            match[u] = v;
            return true;
        }
    }
    return false;
}

int bipartite_matching() {
    int res = 0;
    memset(match, -1, sizeof(match));
    for(int v = 0; v < V; v++) {
        if(match[v] < 0) {
            memset(used, 0, sizeof(used));
            if(dfs(v)) {
                ++res;
            }
        }
    }
    return res;
}

int main()
{
    vector<pair<int, int>> E = {
        {1, 4},
        {1, 5},
        {2, 4},
        {2, 6},
        {3, 5},
    };
    for(auto& e: E) {
        int a, b;
        tie(a, b) = e;
        add_edge(a, b);
    }
    int ans = bipartite_matching();
    printf("%d\n", ans);
    return 0;
}
