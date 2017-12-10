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
#define PRINTARR(a,b) for(int i=0;(a+i)!=(b);i++){cout << *(a+i) << " ";}PN();
#define MP make_pair
#define PB push_back
#define EB emplace_back
#define MT make_tuple

typedef pair<int, int> PII;
typedef tuple<int, int, int> T3I;
typedef long long LL;
typedef unsigned long long ULL;

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
#define MAX_N 105

int N, P;
double INF = 1e18;
double D[MAX_N][MAX_N];

void warshall() {
    REP(k, 1, N+1) {
        REP(i, 1, N+1) {
            REP(j, 1, N+1) {
                D[i][j] = min(D[i][j], D[i][k] + D[k][j]);
            }
        }
    }
}
