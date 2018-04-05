#include <bits/stdc++.h>
using namespace std;

const int MOD = 1000000007;
#define MAX_N 300005

int parent[MAX_N];
int rnk[MAX_N];

void init(int n) {
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
    x = find(x);
    y = find(y);
    if(x == y) {
        return;
    }

    if(rnk[x] < rnk[y]) {
        parent[x] = y;
    } else {
        parent[y] = x;
        if(rnk[x] == rnk[y]) {
            rnk[x]++;
        }
    }
}

bool same(int x, int y) {
    return find(x) == find(y);
}

int main()
{
    int n = 10;
    init(n);
    unite(1, 2);
    printf("%d\n", same(1, 3));
    unite(2, 3);
    printf("%d\n", same(1, 3));
    return 0;
}
