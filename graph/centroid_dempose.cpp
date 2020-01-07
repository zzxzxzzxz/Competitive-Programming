#include <bits/stdc++.h>
using namespace std;

const int MOD = 1000000007;
#define MAX_N 100005

struct edge {
    int to, length;
};

int N, K;
vector<edge> G[MAX_N];

bool centroid[MAX_N];
int subtree_size[MAX_N];
int ans;

int compute_subtree_size(int v, int p) {
    int c = 1;
    for(auto& e: G[v]) {
        if(e.to == p or centroid[e.to]) {
            continue;
        }
        c += compute_subtree_size(e.to, v);
    }
    return c;
}

pair<int, int> search_centroid(int v, int p, int total) {
    pair<int, int> res = {INT_MAX, -1};
    int sz = 1, maxsz = 0;
    for(auto& e: G[v]) {
        if(e.to == p or centroid[e.to]) {
            continue;
        }
        res = min(res, search_centroid(e.to, v, total));
        maxsz = max(maxsz, subtree_size[e.to]);
        sz += subtree_size[e.to];
    }
    maxsz = max(maxsz, total - sz);
    res = min(res, make_pair(maxsz, v));
    return res;
}

int foo(int) { return 0; }

void solve(int v) {
    compute_subtree_size(v, -1);
    int c = search_centroid(v, -1, subtree_size[v]).second;
    centroid[c] = true;

    for(auto& e: G[c]) {
        if(centroid[e.to]) {
            continue;
        }
        solve(e.to);
    }
    ans += foo(c);
}

int main()
{
    ans = 0;
    solve(0);
    cout << ans << endl;
    return 0;
}
