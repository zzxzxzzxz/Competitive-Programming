#include <bits/stdc++.h>
using namespace std;

//{{{
long long count(int v, int k);
//}}}

const int MAX_N = 50005;
using LL = long long;

struct edge {
    int to;
};

vector<edge> G[MAX_N];
bool used[MAX_N];
int subtree_size[MAX_N];

int compute_subtree_size(int v, int p) {
    int sz = 1;
    for(auto& e: G[v]) {
        if(e.to == p or used[e.to]) {
            continue;
        }
        sz += compute_subtree_size(e.to, v);
    }
    subtree_size[v] = sz;
    return sz;
}

pair<int, int> search_centroid(int v, int p, int total) {
    pair<int, int> res = {INT_MAX, -1};
    int maxsz = total - subtree_size[v];
    for(auto& e: G[v]) {
        if(e.to != p and not used[e.to]) {
            maxsz = max(maxsz, subtree_size[e.to]);
            res = min(res, search_centroid(e.to, v, total));
        }
    }
    res = min(res, make_pair(maxsz, v));
    return res;
}

int solve(int v, int k) {
    compute_subtree_size(v, -1);
    int ctr = search_centroid(v, -1, subtree_size[v]).second;
    used[ctr] = true;

    LL ans = count(ctr, k) / 2;

    for(auto& e: G[ctr]) {
        if(not used[e.to]) {
            ans += solve(e.to, k);
        }
    }
    return ans;
}

//{{{
LL count(int v, int k) {
    unordered_map<int, LL> cnt;
    auto dfs = [&](auto self, int v, int p, int depth) -> void {
        if(depth <= k) ++cnt[depth];
        for(auto& e : G[v]) {
            if(e.to != p and not used[e.to]) {
                self(self, e.to, v, depth + 1);
            }
        }
    };

    LL ans = 0;
    unordered_map<int, LL> cnt_all = {{0, 1}};
    for(auto& e : G[v]) {
        if(used[e.to]) continue;

        cnt.clear();
        dfs(dfs, e.to, v, 1);
        for(auto [key, val] : cnt) {
            cnt_all[key] += val;
            if(cnt.find(k - key) != cnt.end()) {
                ans -= val * cnt[k - key];
            }
        }
    }

    for(auto [key, val] : cnt_all) {
        if(cnt_all.find(k - key) != cnt_all.end()) {
            ans += val * cnt_all[k - key];
        }
    }
    return ans;
}
//}}}

// https://codeforces.com/contest/161/problem/D

int main()
{
    int n = 5, k = 2;
    vector<array<int, 2>> graph = {
        {1, 2}, {2, 3}, {3, 4}, {2, 5},
    };
    for(int i = 0; i < n - 1; ++i) {
        auto [u, v] = graph[i];
        G[u].push_back({v});
        G[v].push_back({u});
    }
    auto ans = solve(1, k);
    cout << ans << endl;
    return 0;
}
