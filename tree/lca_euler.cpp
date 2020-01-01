#include <bits/stdc++.h>
using namespace std;

const int MOD = 1000000007;
#define MAX_N 300005

vector<int> G[MAX_N];
int pos[MAX_N], vs[MAX_N], depth[MAX_N];
int dat[2 * MAX_N];

struct SegTree {
    const int zero_c = MAX_N - 1;
    void modify(int& val1, int val2) {
        val1 = val2;
    }
    int combine(int val1, int val2) {
        if(depth[val1] < depth[val2]) {
            return val1;
        }
        return val2;
    }

    int N;
    SegTree(int n_, int *a = NULL) {
        N = 1;
        while(N < n_) {
            N <<= 1;
        }
        fill(dat, dat + 2 * N, zero_c);

        if(a != NULL) {
            for(int i = 0; i < n_; i++) {
                dat[i + N] = a[i];
            }
            build();
        }
    }

    void build() {
        for(int k = N - 1; k >= 0; k--) {
            dat[k] = combine(dat[k * 2], dat[k * 2 + 1]);
        }
    }

    void update(int a, int val, int l = 0, int r = -1, int k = 1) {
        r = (r < 0)? N : r;

        if(r <= a or a < l) {
            return;
        }
        if(l == r - 1) {
            modify(dat[k], val);
            return;
        }
        int mid = l + (r - l) / 2;
        update(a, val, l, mid, k * 2);
        update(a, val, mid, r, k * 2 + 1);
        dat[k] = combine(dat[k * 2], dat[k * 2 + 1]);
    }

    int query(int a, int b, int l = 0, int r = -1, int k = 1) {
        r = (r < 0)? N : r;

        if(r <= a or b <= l) {
            return zero_c;
        }

        if(a <= l and r <= b) {
            return dat[k];
        }
        int mid = l + (r - l) / 2;
        int vl = query(a, b, l, mid, k * 2);
        int vr = query(a, b, mid, r, k * 2 + 1);
        return combine(vl, vr);
    }
};

void euler(int v, int p, int d, int& sz) {
    pos[v] = sz;
    vs[sz] = v;
    //depth[sz] = d;
    depth[v] = d;
    ++sz;
    for(int u: G[v]) {
        if(u == p) {
            continue;
        }
        euler(u, v, d + 1, sz);
        vs[sz] = v;
        //depth[sz] = d;
        ++sz;
    }
}

int lca(SegTree& t, int u, int v) {
    int l = min(pos[u], pos[v]);
    int r = max(pos[u], pos[v]) + 1;
    return t.query(l, r);
}

int main() {
    int n = 5;
    vector<int> g = {1, 2, 1, 2};
    for(int i = 2; i <= n; i++) {
        int u = i, v = g[i - 2];
        G[u].push_back(v);
        G[v].push_back(u);
    }
    int root = 1, sz = 0;
    euler(root, -1, 0, sz);

    depth[MAX_N - 1] = INT_MAX;
    SegTree t(sz, &vs[0]);

    cout << lca(t, 1, 2) << endl;
    cout << lca(t, 3, 4) << endl;
    cout << lca(t, 3, 5) << endl;
    return 0;
}
