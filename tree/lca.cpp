#include <bits/stdc++.h>
using namespace std;

#define GET_MACRO(_1,_2,_3,_4,NAME,...) NAME
#define REP2(i,n) for(int i=0;i<(int)(n);i++)
#define REP3(i,m,n) for(int i=m;i<(int)(n);i++)
#define REP4(i,m,n,s) for(int i=m;(s>0 and i<(int)(n)) or (s<0 and i>(int)(n));i+=s)
#define REP(...) GET_MACRO(__VA_ARGS__, REP4, REP3, REP2)(__VA_ARGS__)
#define REPIT(i,c) for(__typeof((c).begin()) i=(c).begin();i!=(c).end();i++)
#define PIS(x) printf("%d ",x)
#define PN() putchar('\n')
#define MP make_pair
#define PB push_back
#define EB emplace_back
#define MT make_tuple

using PII = pair<int, int>;
using TI3 = tuple<int, int, int>;
using LL = long long;
using ULL =  unsigned long long;
using MAT = array<array<LL, 2>, 2>;

void RI() {}
template<typename... T>
void RI( int& head, T&... tail ) {
    scanf("%d", &head);
    RI(tail...);
}
void RLL() {}
template<typename... T>
void RLL( LL& head, T&... tail ) {
    scanf("%lld", &head);
    RLL(tail...);
}
void print() {putchar('\n');}
template<typename T, typename... U>
void print(T head, U... tail) {
    cout << head << " ";
    print(tail...);
}

const int MOD = 1000000007;
#define MAX_N 300005
#define MAX_LOG_N 19

vector<int> G[MAX_N];
const int root = 1;
int parent[MAX_LOG_N][MAX_N];
int depth[MAX_N];

void dfs(int v, int p, int d) {
    parent[0][v] = p;
    depth[v] = d;
    for(int i = 0; i < (int)G[v].size(); i++) {
        if(G[v][i] != p) {
            dfs(G[v][i], v, d + 1);
        }
    }
}

void init(int n) {
    dfs(root, -1, 0);
    for(int k = 0; k + 1 < MAX_LOG_N; k++) {
        for(int v = 0; v < n; v++) {
            if(parent[k][v] < 0) {
                parent[k + 1][v] = -1;
            } else {
                parent[k + 1][v] = parent[k][parent[k][v]];
            }
        }
    }
}

int lca(int u, int v) {
    if(depth[u] > depth[v]) {
        swap(u, v);
    }
    for(int k = 0; k < MAX_LOG_N; k++) {
        if((depth[v] - depth[u]) >> k & 1) {
            v = parent[k][v];
        }
    }
    if(u == v) {
        return u;
    }
    for(int k = MAX_LOG_N - 1; k >= 0; k--) {
        if(parent[k][u] != parent[k][v]) {
            u = parent[k][u];
            v = parent[k][v];
        }
    }
    return parent[0][u];
}

int main()
{
    int n = 5;
    vector<int> g = {1, 2, 1, 2};
    for(int i = 2; i <= n; i++) {
        int u = i, v = g[i-2];
        G[u].push_back(v);
        G[v].push_back(u);
    }
    init(n + 1);
    printf("%d\n", lca(1, 2));
    printf("%d\n", lca(3, 4));
    printf("%d\n", lca(3, 5));
    return 0;
}
