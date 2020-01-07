#include <bits/stdc++.h>

using namespace std;

struct Node {
    int l, r;
};
Node T[30000000];
int nodes = 1;

pair<int, int> Split(int node, int b, int e, int k) {
    if (node == 0) return {0, 0};
    if (b == e) {
        int l = (b < k ? node : 0);
        int r = (b >= k ? node : 0);
        return {l, r};
    }

    int clone = nodes++;

    int m = (b + e) / 2;
    if (k <= m) {
        auto [l, r] = Split(T[node].l, b, m, k);
        T[node].l = r;
        T[clone].l = l;
        return {clone, node};
    } else {
        auto [l, r] = Split(T[node].r, m + 1, e, k);
        T[node].r = l;
        T[clone].r = r;
        return {node, clone};
    }
}

int Merge(int node1, int node2) {
    if (node1 == 0) return node2;
    if (node2 == 0) return node1;
    T[node1].l = Merge(T[node1].l, T[node2].l);
    T[node1].r = Merge(T[node1].r, T[node2].r);
    return node1;
}

int Make(int b, int e, int val) {
    int ret = nodes++;
    if (b == e) return ret;

    int m = (b + e) / 2;
    if (val <= m) {
        T[ret].l = Make(b, m, val);
    } else {
        T[ret].r = Make(m + 1, e, val);
    }

    return ret;
}

template<typename F>
void DFS(int node, int b, int e, F f) {
    if (node == 0) return;
    if (b == e) {
        f(b);
    } else {
        int m = (b + e) / 2;
        DFS(T[node].l, b, m, f);
        DFS(T[node].r, m + 1, e, f);
    }
}

/*
 * https://codeforces.com/contest/911/problem/G
 *
 * input:
 * 5
 * 1 2 3 4 5
 * 3
 * 3 5 3 5
 * 1 5 5 1
 * 1 5 1 5
 *
 * output:
 * 5 2 5 4 5
 */

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n; cin >> n;
    vector<int> trees(101);
    for (int i = 0; i < n; ++i) {
        int x; cin >> x;
        trees[x] = Merge(trees[x], Make(0, n - 1, i));
    }

    int q; cin >> q;
    while (q--) {
        int l, r, x, y;
        cin >> l >> r >> x >> y;

        int lf, md, rt;
        tie(lf, md) = Split(trees[x], 0, n - 1, l - 1);
        tie(md, rt) = Split(md, 0, n - 1, r);
        trees[x] = Merge(lf, rt);
        trees[y] = Merge(trees[y], md);
    }

    vector<int> ret(n);
    for (int i = 1; i <= 100; ++i) {
        DFS(trees[i], 0, n - 1, [&](int val) {
            ret[val] = i;
        });
    }

    for (auto x : ret) cout << x << " "; cout << endl;

    return 0;
}
