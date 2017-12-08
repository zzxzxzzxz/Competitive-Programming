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
using T3U = tuple<int, int, int>;
using LL = long long;
using ULL =  unsigned long long;
using Mat = array<array<int, 2>, 2>;

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

int bit[MAX_N + 1], n;

void build() {
    for(int i = 1; i <= n; i++) {
        int j = i + (i & -i);
        if(j <= n) {
            bit[j] += bit[i];
        }
    }
}

int sum(int i) {
    int s = 0;
    while (i > 0) {
        s += bit[i];
        i -= i & -i;
    }
    return s;
}

void add(int i, int x) {
    i += 1;
    while (i <= n) {
        bit[i] += x;
        i += i & -i;
    }
}

int main()
{
    int i, x;
    RI(n);
    REP(i, 1, n + 1) {
        RI(bit[i]);
    }
    build();
    REP(i, 1, n + 1) {
        PIS(sum(i));
    }
    PN();
    while (scanf("%d%d", &i, &x) > 0) {
        printf("%d %d\n", i, x);
        arr[i] += x;
        add(i, x);
        REP(j, n) {
            printf("%d ", arr[j]);
        }
        printf("\n");
        for(int j = 1; j <= n; j++) {
            printf("%d ", sum(j));
        }
        printf("\n");
    }

    return 0;
}
