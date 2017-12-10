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
using MAT = array<array<int, 2>, 2>;

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
#define MAX_N 100005

const int& (*func)(const int&, const int&) = min<int>;
const int zero = INT_MAX;

int n;
int t[2 * MAX_N];

void build() {
    for(int i = n - 1; i > 0; i--) {
        t[i] = func(t[i << 1], t[(i << 1)|1]);
    }
}

int query(int l, int r) {
    int resl = zero, resr = zero;
    for(l += n, r += n; l < r; l >>= 1, r >>= 1) {
        if(l & 1) {
            resl = func(resl, t[l++]);
        }
        if(r & 1) {
            resr = func(t[--r], resr);
        }
    }
    return func(resl, resr);
}

void update(int p, int v) {
    for(t[p += n] = v; p > 1; p >>= 1) {
        t[p >> 1] = func(t[p], t[p^1]);
    }
}

int main()
{
/*
    5
    4 5 1 2 3
    5
    0 1 4
    1 2 10
    0 1 4
    1 3 10
    0 1 4
*/
    scanf("%d", &n);
    for(int i = 0; i < n; i++) {
        scanf("%d", &t[i + n]);
    }
    build();

    for(int k = 0; k < n; k++) {
        printf("%d ", t[k + n]);
    }
    printf("\n");

    int m;
    scanf("%d", &m);
    for(int i = 0; i < m; i++) {
        int q;
        scanf("%d", &q);
        if(q == 0) {
            int l, r;
            scanf("%d%d", &l, &r);
            printf("[%d, %d): %d\n", l, r, query(l, r));
        } else {
            int j, v;
            scanf("%d%d", &j, &v);
            update(j, v);
            for(int k = 0; k < n; k++) {
                printf("%d ", t[k + n]);
            }
            printf("\n");
        }
    }
    return 0;
}
