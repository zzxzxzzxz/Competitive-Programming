#include <bits/stdc++.h>
using namespace std;

#define GET_MACRO(_1,_2,_3,_4,NAME,...) NAME
#define REP2(i,n) for(int i=0;i<(int)(n);i++)
#define REP3(i,m,n) for(int i=m;i<(int)(n);i++)
#define REP4(i,m,n,s) for(int i=m;(s>0 and i<(int)(n)) or (s<0 and i>(int)(n));i+=s)
#define REP(...) GET_MACRO(__VA_ARGS__, REP4, REP3, REP2)(__VA_ARGS__)
#define REPIT(i,c) for(__typeof((c).begin()) i=(c).begin();i!=(c).end();i++)
#define PIS(x) printf("%d ",x)
#define PRINTIA(a,n) REP(i,n){printf("%d ", *((a)+i));}putchar('\n');
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
void PI(const int head, T... tail ) {
    printf("%d ", head);
    PI(tail...);
}

#define MAX_N 50000

struct edge {
    int to, cost;
};
const int INF = INT_MAX;
int V;
vector<edge> G[MAX_N];
int d[MAX_N];

void dijkstra(int s) {
    priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > que;
    fill(d, d + V, INF);
    d[s] = 0;
    que.push(make_pair(0, s));

    while(!que.empty()) {
        pair<int, int> p = que.top();
        que.pop();
        int v = p.second;
        if(d[v] < p.first)
            continue;
        for(int i = 0; i < (int)G[v].size(); i++) {
            edge e = G[v][i];
            if(d[e.to] > d[v] + e.cost) {
                d[e.to] = d[v] + e.cost;
                que.push(make_pair(d[e.to], e.to));
            }
        }
    }
}

int main()
{
    int E;
    RI(V, E);
    REP(i, E) {
        int from, to, cost;
        RI(from, to, cost);
        G[from].PB(edge{to, cost});
    }
    dijkstra(0);
    PI(d[6]);
    return 0;
}
