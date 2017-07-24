#include <bits/stdc++.h>
using namespace std;

#define GET_MACRO(_1,_2,_3,NAME,...) NAME
#define REP2(i,n) for(int i=0;i<(int)(n);i++)
#define REP3(i,m,n) for(int i=m;i<(int)(n);i++)
#define REP(...) GET_MACRO(__VA_ARGS__, REP3, REP2)(__VA_ARGS__)
#define REPIT(i,c) for(__typeof((c).begin()) i=(c).begin();i!=(c).end();i++)
#define PIS(x) printf("%d ",x)
#define PRINTIA(a,n) REP(i,n){printf("%d ", *((a)+i));} putchar('\n');
#define PN() putchar('\n')
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
void PI() {putchar('\n');}
template<typename... T>
void PI( const int& head, T&... tail ) {
    printf("%d ", head);
    PI(tail...);
}

#define MAX_V 200000
#define MAX_LOG_V 18

vector<int> G[MAX_V];
int root = 1;
int parent[MAX_LOG_V][MAX_V];
int depth[MAX_V];

void dfs(int v, int p, int d) {
    parent[0][v] = p;
    depth[v] = d;
    REP(i, G[v].size()) {
        if (G[v][i] != p) {
            dfs(G[v][i], v, d+1);
        }
    }
}

void init(int V) {
    dfs(root, -1, 0);
    for(int k = 0; k + 1 < MAX_LOG_V; k++) {
        for(int v = 0; v < V; v++) {
            if (parent[k][v] < 0)
                parent[k + 1][v] = -1;
            else
                parent[k + 1][v] = parent[k][parent[k][v]];
        }
    }
}

int lca(int u, int v) {
    if (depth[u] > depth[v])
        swap(u, v);

    for(int k = 0; k < MAX_LOG_V; k++) {
        if((depth[v] - depth[u]) >> k & 1) {
            v = parent[k][v];
        }
    }
    if (u == v)
        return u;
    for (int k = MAX_LOG_V - 1; k >= 0; k--) {
        if(parent[k][u] != parent[k][v]) {
            u = parent[k][u];
            v = parent[k][v];
        }
    }
    return parent[0][u];
}

int main()
{
    int N, step, a, b;
    RI(N, step);
    REP(i, N) {
        RI(a, b);
        G[a].PB(b);
        G[b].PB(a);
    }
    init(N+1);
    PI(lca(6, 5));
    PI(lca(2, 5));
    PI(lca(5, 3));
    return 0;
}
