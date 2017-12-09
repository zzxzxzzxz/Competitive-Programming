#include <bits/stdc++.h>
using namespace std;

#define REP(i,n) for(int i=0;i<(n);i++)
#define REPIT(i,c) for(__typeof((c).begin()) i=(c).begin();i!=(c).end();i++)
#define DRI(...) int __VA_ARGS__;RI(__VA_ARGS__)
#define PI(x) printf("%d\n",x)
#define PIS(x) printf("%d ",x)
#define MP make_pair
#define PB push_back

typedef pair<int,int> PII;
typedef long long LL;
typedef unsigned long long ULL;

void RI() {}
template<typename... T>
void RI( int& head, T&... tail ) {
    scanf("%d",&head);
    RI(tail...);
}

#define MAXN 100000
int parent[MAXN];
int rnk[MAXN];

void init(int n) {
    for (int i = 0; i < n; i++) {
        parent[i] = i;
        rnk[i] = 0;
    }
}

int find(int x) {
    if (parent[x] == x) {
        return x;
    } else {
        parent[x] = find(parent[x]);
        return parent[x];
    }
}

void unite(int x, int y) {
    x = find(x);
    y = find(y);
    if (x == y)
        return;
    if (rnk[x] < rnk[y]) {
        parent[x] = y;
    } else {
        parent[y] = x;
        if (rnk[x] == rnk[y])
            rnk[x]++;
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
