#include <bits/stdc++.h>
using namespace std;

const int MOD = 1000000007;
#define MAX_N 300005

int parent[MAX_N];
int rnk[MAX_N];

struct DSU {
    DSU(int n) {
        for(int i = 0; i < n; i++) {
            parent[i] = i;
            rnk[i] = 0;
        }
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

    bool same(int x, int y) {
        return find(x) == find(y);
    }
};

int main()
{
    int n = 10;
    DSU dsu(n + 1);
    dsu.unite(1, 2);
    cout << dsu.same(1, 3) << endl;
    dsu.unite(2, 3);
    cout << dsu.same(1, 3) << endl;
    return 0;
}
