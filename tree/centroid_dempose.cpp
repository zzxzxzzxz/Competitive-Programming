#include <bits/stdc++.h>
using namespace std;

//{{{
int k;
long long count(int v);
//}}}

const int MAX_N = 50005;
const int MAX_K = 505;
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
int cnt_all[MAX_K], cnt[MAX_K];

void bfs(int v, int p) {
    memset(cnt, 0, sizeof(cnt));

    vector<pair<int, int>> stk = {{v, p}}, tmp;
    int depth = 1;
    while(depth <= k and not stk.empty()) {
        cnt[depth++] += stk.size();

        tmp.clear();
        for(auto [u, pu] : stk) {
            for(auto& e : G[u]) {
                if(e.to != pu and not used[e.to]) {
                    tmp.push_back({e.to, u});
                }
            }
        }
        swap(tmp, stk);
    }
}

LL count(int v) {
    memset(cnt_all, 0, sizeof(cnt_all));
    cnt_all[0] = 1;

    LL ans = 0;
    for(auto& e : G[v]) {
        if(not used[e.to]) {
            bfs(e.to, v);
            for(int i = 1; i <= k; ++i) {
                cnt_all[i] += cnt[i];
                ans -= 1LL * cnt[i] * cnt[k - i];
            }
        }
    }

    for(int i = 0; i <= k; ++i) {
        ans += 1LL * cnt_all[i] * cnt_all[k - i];
    }
    ans /= 2;
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
