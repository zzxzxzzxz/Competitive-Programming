#include <bits/stdc++.h>
using namespace std;

#define REP(i,n) for(int i=0;i<(n);i++)
#define REPIT(i,c) for(__typeof((c).begin()) i=(c).begin();i!=(c).end();i++)
#define DRI(...) int __VA_ARGS__;RI(__VA_ARGS__)

typedef pair<int,int> PII;
typedef long long LL;
typedef unsigned long long ULL;

void RI() {}
template<typename... T>
void RI( int& head, T&... tail ) {
    scanf("%d",&head);
    RI(tail...);
}

#define MAX_E 100000
#define MAX_V 10000
#define INF INT_MAX

struct edge {
    int from, to, cost;
};

edge es[MAX_V];

int d[MAX_V];
int V, E;

bool bellman_ford(int s) {
    for (int i = 0; i < V; i++)
        d[i] = INF;
    d[s] = 0;
    REP(j, V) {
        bool update = false;
        REP(i, E) {
            edge& e = es[i];
            if (d[e.from] != INF and d[e.to] > d[e.from] + e.cost) {
                d[e.to] = d[e.from] + e.cost;
                update = true;
            }
        }
        if (!update)
            break;
        if (j == V-1) //negative loop exists
            return true;
    }
    return false;
}

int main()
{
    RI(V, E);
    REP(i, E) {
        RI(es[i].from, es[i].to, es[i].cost);
    }
    bellman_ford(0);
    REP(i, V) {
        printf("%d\n", d[i]);
    }

    return 0;
}
