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

struct edge {
    int to;
    int cost;
};

const int INF = 1e8;
int V;
vector<edge> G[MAX_N];
int d[MAX_N];

void dijkstra(int s) {
    priority_queue<pair<int, int>,
                   vector<pair<int, int> >,
                   greater<pair<int, int> > > que;
    fill(d, d + V, INF);
    d[s] = 0;
    que.push(make_pair(0, s));

    while(not que.empty()) {
        pair<int, int> p = que.top();
        que.pop();
        int v = p.second;
        if(d[v] < p.first) {
            continue;
        }
        for(int i = 0; i < (int)G[v].size(); i++) {
            edge& e = G[v][i];
            if(d[e.to] > d[v] + e.cost) {
                d[e.to] = d[v] + e.cost;
                que.push(make_pair(d[e.to], e.to));
            }
        }
    }
}

int main()
{
    V = 7;
    vector<vector<int> > g = {{0, 1, 2}, {0, 2, 5}, {1, 2, 4},
                              {1, 3, 6}, {2, 3, 2}, {1, 4, 10},
                              {3, 5, 1}, {4, 5, 3}, {4, 6, 5},
                              {5, 6, 9}};
    for(int i = 0; i < (int)g.size(); i++) {
        int u = g[i][0], v = g[i][1], cost = g[i][2];
        G[u].push_back(edge({v, cost}));
        G[v].push_back(edge({u, cost}));
    }
    dijkstra(0);
    printf("%d\n", d[6]);
    return 0;
}
