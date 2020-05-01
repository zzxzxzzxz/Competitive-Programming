#include <bits/stdc++.h>
using namespace std;

struct DSU {//{{{
    vector<tuple<int, int, int>> ops;
    vector<int> parent, rnk;

    DSU(int n) {
        rnk.assign(n, 0);
        parent.resize(n);
        iota(parent.begin(), parent.end(), 0);
    }

    int find(int x) {
        if(parent[x] == x) {
            return x;
        }
        ops.emplace_back(0, x, parent[x]);
        parent[x] = find(parent[x]);
        return parent[x];
    }

    void unite(int x, int y) {
        int px = find(x);
        int py = find(y);
        if(px == py) {
            return;
        }

        if(rnk[px] < rnk[py]) {
            ops.emplace_back(0, px, parent[px]);
            parent[px] = py;
        } else {
            ops.emplace_back(0, py, parent[py]);
            parent[py] = px;
            if(rnk[px] == rnk[py]) {
                ops.emplace_back(1, px, 1);
                rnk[px]++;
            }
        }
    }

    void rollback() {
        reverse(ops.begin(), ops.end());
        for(auto& op : ops) {
            if(get<0>(op) == 0) {
                auto [t, x, p] = op;
                parent[x] = p;
            } else {
                auto [t, x, _] = op;
                rnk[x] -= 1;
            }
        }
        ops.clear();
    }

    void commit() {
        ops.clear();
    }

};//}}}

int main() {
    auto dsu = DSU(10);

    dsu.unite(1, 2);
    dsu.commit();
    dsu.unite(2, 3);
    dsu.unite(3, 4);
    cout << (dsu.find(1) == dsu.find(4)) << endl;

    dsu.rollback();
    dsu.unite(3, 4);
    cout << (dsu.find(1) == dsu.find(4)) << endl;

    dsu.unite(2, 3);
    cout << (dsu.find(1) == dsu.find(4)) << endl;
    return 0;
}
