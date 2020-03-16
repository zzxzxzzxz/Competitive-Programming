#pragma comment(linker, "/stack:200000000")
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

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

template<class T> void _read( T &x ) { cin>>x; }
void _read(int &x) { scanf("%d", &x); }
void _read(LL &x) { scanf("%lld", &x); }
void _read(double &x) { scanf("%lf", &x); }
void _read(char &x) { scanf(" %c", &x); }
void _read(char *x) { scanf("%s", x); }
void read() {}
template<class T, class... U>
void read( T& head, U&... tail ) {
    _read(head);
    read(tail...);
}

template<class T> void _print( const T &x ) { cout << x; }
void _print( const int &x ) { printf("%d", x); }
void _print( const LL &x ) { printf("%lld", x); }
void _print( const double &x ) { printf("%.16lf",x); }
void _print( const char &x ) { putchar(x); }
void _print( const char *x ) { printf("%s",x); }
template<class T> void _print( const vector<T> &x ) { for (auto i = x.begin(); i != x.end(); _print(*i++)) if (i != x.cbegin()) putchar(' '); }
void print() {}
template<class T, class... U> void print( const T& head, const U&... tail ) {
    _print(head);
    putchar(sizeof...(tail) ? ' ' : '\n');
    print(tail...);
}

const int MOD = 1000000007;
#define MAX_N 200005

LL a[MAX_N];
LL cumsum[MAX_N];
LL ccsum[MAX_N];

int N, Q;

LL calc(LL S, LL n) {
    LL s = 0;
    LL scnt = 0;
    REP(i, 1, N + 1) {
        LL cnt = i - (lower_bound(cumsum, cumsum + i, cumsum[i] - S) - cumsum);
        s += cnt * cumsum[i] - ccsum[i-1] + ccsum[i - cnt - 1];
        scnt += cnt;
    }
    s -= S * (scnt - n);
    return s;
}

bool OK(LL k, LL n) {
    LL s = 0;
    REP(i, 1, N + 1) {
        LL cnt = i - (lower_bound(cumsum, cumsum + i, cumsum[i] - k) - cumsum);
        s += cnt;
    }
    return s > n;
}

void solve() {
    LL m = LLONG_MAX;
    read(N, Q);
    REP(i, N) {
        read(a[i]);
        m = min(m, a[i]);
    }
    REP(i, 1, N + 1) {
        cumsum[i] = cumsum[i - 1] + a[i - 1];
    }
    REP(i, 1, N + 1) {
        ccsum[i] = ccsum[i - 1] + cumsum[i];
    }
    PN();
    LL L, R;
    REP(i, Q) {
        read(L, R);
        LL l = m, r = 200000 * 100 + 1;
        REP(t, 30) {
            LL mid = l + (r - l) / 2;
            bool ok = OK(mid, L - 1);
            if(ok) {
                r = mid;
            } else {
                l = mid;
            }
        }
        LL sL = r;
        l = m, r = 200000 * 100 + 1;
        REP(t, 30) {
            LL mid = l + (r - l) / 2;
            bool ok = OK(mid, R);
            if(ok) {
                r = mid;
            } else {
                l = mid;
            }
        }
        LL sR = r;
        LL A = calc(sL, L - 1);
        LL B = calc(sR, R);
        print(B - A);
    }

}

int main() {
    int T;
    scanf("%d", &T);
    for(int i = 0; i < T; i++) {
        printf("Case #%d: ", i+1);
        solve();
    }

    return 0;
}
