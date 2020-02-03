#include <bits/stdc++.h>
using namespace std;

vector<int> parent, rnk;

struct DSU {
    DSU(int n) {
        rnk.assign(n, 0);
        parent.resize(n);
        iota(parent.begin(), parent.end(), 0);
    }

    int find(int x) {
        if(parent[x] == x) {
            return x;
        }
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
            parent[px] = py;
        } else {
            parent[py] = px;
            if(rnk[px] == rnk[py]) {
                rnk[px]++;
            }
        }
    }
};

int main()
{
    int n = 10;
    auto dsu = DSU(n + 1);
    dsu.unite(1, 2);
    cout << (dsu.find(1) == dsu.find(3)) << endl;
    dsu.unite(2, 3);
    cout << (dsu.find(1) == dsu.find(3)) << endl;
    return 0;
}
