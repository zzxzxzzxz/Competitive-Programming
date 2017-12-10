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
