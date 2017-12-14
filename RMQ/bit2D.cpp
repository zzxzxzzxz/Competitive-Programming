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
#define MAX_N 5005

int bit[MAX_N + 1][MAX_N + 1], n, m;

void build() {
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            int l = j + (j & -j);
            if(l <= m) {
                bit[i][l] += bit[i][j];
            }
        }
    }
    for(int i = 1; i <= n; i++) {
        int k = i + (i & -i);
        if(k <= n) {
            for(int j = 1; j <= m; j++) {
                bit[k][j] += bit[i][j];
            }
        }
    }
}


int sum(int i, int j) {
    int s = 0;
    while (i > 0) {
        int k = j;
        while(k > 0) {
            s += bit[i][k];
            k -= k & -k;
        }
        i -= i & -i;
    }
    return s;
}


void add(int i, int j, int x) {
    while (i <= n) {
        int k = j;
        while(k <= m) {
            bit[i][k] += x;
            k += k & -k;
        }
        i += i & -i;
    }
}

int main()
{
    /*
    4 4
    1 0 1 1
    1 0 1 0
    0 1 0 1
    1 0 0 1
    3
    1 1 -1
    2 3 1
    3 2 -1
    */

    RI(n, m);
    REP(i, 1, n + 1) {
        REP(j, 1, m + 1) {
            RI(bit[i][j]);
        }
    }
    build();

    REP(j, 1, n + 1) {
        REP(k, 1, m + 1) {
            PIS(sum(j, k));
        }
        PN();
    }
    PN();

    int q;
    RI(q);
    REP(i, q) {
        int row, col, value;
        RI(row, col, value);
        add(row, col, value);
        print(row, col, value);
        REP(j, 1, n + 1) {
            REP(k, 1, m + 1) {
                PIS(sum(j, k));
            }
            PN();
        }
        PN();
    }
    return 0;
}
