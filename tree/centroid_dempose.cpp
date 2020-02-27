#include <bits/stdc++.h>
using namespace std;

//{{{
int k;
long long count(int v);
//}}}

const int MAX_N = 50005;
using LL = long long;

struct edge {
    int to;
};

vector<edge> G[MAX_N];
bool used[MAX_N];
int subtsz[MAX_N];

pair<int, int> search_centroid(int total, int v, int p = -1) {
    pair<int, int> res = {INT_MAX, -1};
    subtsz[v] = 1;
    int maxsz = 0;
    for(auto& e: G[v]) {
        if(e.to != p and not used[e.to]) {
            res = min(res, search_centroid(total, e.to, v));
            maxsz = max(maxsz, subtsz[e.to]);
            subtsz[v] += subtsz[e.to];
        }
    }
    maxsz = max(maxsz, total - subtsz[v]);
    res = min(res, make_pair(maxsz, v));
    return res;
}

int solve(int v, int total) {
    int ctr = search_centroid(total, v).second;
    used[ctr] = true;

    LL ans = count(ctr);

    for(auto& e: G[ctr]) {
        if(not used[e.to]) {
            int sz = subtsz[e.to] > subtsz[ctr] ? total - subtsz[ctr] : subtsz[e.to];
            ans += solve(e.to, sz);
        }
    }
    return ans;
}

//{{{
LL count(int v) {
    unordered_map<int, int> cnt;
    auto dfs = [&](auto self, int v, int p, int depth) -> void {
        if(depth <= k) ++cnt[depth];
        for(auto& e : G[v]) {
            if(e.to != p and not used[e.to]) {
                self(self, e.to, v, depth + 1);
            }
        }
    };

    LL ans = 0;
    unordered_map<int, int> cnt_all = {{0, 1}};
    for(auto& e : G[v]) {
        if(used[e.to]) continue;

        cnt.clear();
        dfs(dfs, e.to, v, 1);
        for(auto [key, val] : cnt) {
            cnt_all[key] += val;
            if(cnt.find(k - key) != cnt.end()) {
                ans -= 1LL * val * cnt[k - key];
            }
        }
    }

    for(auto [key, val] : cnt_all) {
        if(cnt_all.find(k - key) != cnt_all.end()) {
            ans += 1LL * val * cnt_all[k - key];
        }
    }
    ans >>= 1;
    return ans;
}
//}}}

// https://codeforces.com/contest/161/problem/D

int main()
{
    k = 2;
    int n = 5;
    vector<array<int, 2>> graph = {
        {1, 2}, {2, 3}, {3, 4}, {2, 5},
    };

    for(int i = 0; i < n - 1; ++i) {
        auto [u, v] = graph[i];
        G[u].push_back({v});
        G[v].push_back({u});
    }
    auto ans = solve(1, n);
    cout << ans << endl;
    return 0;
}
