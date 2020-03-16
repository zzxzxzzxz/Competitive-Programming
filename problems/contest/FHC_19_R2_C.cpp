//{{{
#pragma comment(linker, "/stack:200000000")
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

#include <bits/stdc++.h>
using namespace std;

using PII = pair<int, int>;
using TI3 = tuple<int, int, int>;
using LL = long long;
using ULL = unsigned long long;
using MAT = array<array<LL, 2>, 2>;

template<class T> constexpr inline T begin(const T&) {return 0;}
template<class T> constexpr inline T end(const T& x) {return max(T(0), x);}

#define SZ(x) int((x).size())
#define PB push_back
#define EB emplace_back
#define GET_MACRO(_1,_2,_3,_4,NAME,...) NAME
#define CHECK(a,b) static_assert(std::is_same<decltype(a), decltype(b)>::value, "REP diff types");

#define REPPP(i,s,c,t) for(i; ((s) and (c)) or (putchar("\n "[c]) and (c)); (t))
#define REPP2(i,n) REPPP(auto i=begin(n),i==begin(n),i!=end(n),++i)
#define REPP3(i,m,n) CHECK(m,n) REPPP(auto i=(m),i==(m),i<(n),++i)
#define REPP4(i,m,n,s) CHECK(m,n) REPPP(auto i=(m),i==(m),((s)>0 and i<(n)) or ((s)<0 and i>(n)),i+=(s))
#define REPP(...) GET_MACRO(__VA_ARGS__, REPP4, REPP3, REPP2)(__VA_ARGS__)

#define REP2(i,n) for(auto i=begin(n);i!=end(n);++i)
#define REP3(i,m,n) CHECK(m,n) for(auto i=(m);i<(n);++i)
#define REP4(i,m,n,s) CHECK(m,n) for(auto i=(m);((s)>0 and i<(n)) or ((s)<0 and i>(n));i+=(s))
#define REP(...) GET_MACRO(__VA_ARGS__, REP4, REP3, REP2)(__VA_ARGS__)

template<class T> void _read(T &x) {cin >> x;}
void _read(size_t &x) {scanf("%zu", &x);}
void _read(int &x) {scanf("%d", &x);}
void _read(LL &x) {scanf("%lld", &x);}
void _read(ULL &x) {scanf("%llu", &x);}
void _read(double &x) {scanf("%lf", &x);}
void _read(char &x) {scanf(" %c", &x);}
void _read(char *x) {scanf("%s", x);}
void read() {}
template<class T, class... U>
void read(T& head, U&... tail) {
    _read(head);
    read(tail...);
}

template<class T> void _print(const T &x) {cout << x;}
void _print(const size_t &x) {printf("%zu", x);}
void _print(const int &x) {printf("%d", x);}
void _print(const LL &x) {printf("%lld", x);}
void _print(const ULL &x) {printf("%llu", x);}
void _print(const double &x) {printf("%.16lf", x);}
void _print(const char &x) {putchar(x);}
void _print(const char *x) {printf("%s", x);}
void _print(const string &x) {printf("%s", x.c_str());}
template<class T> void _print(const vector<T> &x) {
    for(auto i = x.begin(); i != x.end(); _print(*i++)) {
        if (i != x.cbegin()) putchar(' ');
    }
}
void print() {putchar('\n');}
template<class T, class... U> void print(const T& head, const U&... tail) {
    _print(head);
    if(sizeof...(tail)) putchar(' ');
    print(tail...);
}

//}}}
const int MOD = 1000000007;

#define LLINF 0x3f3f3f3f3f3f3f3f
#define INF 0x3f3f3f3f

char p[500][500];
int dp[500][500][2]; // ith paper, switch, subject
int F[2][500];

void solve() {
    int H, S, K;
    read(H, S, K);
    REP(i, H) {
        read(p[i]);
    }

    memset(F, 0, sizeof(F));
    REP(f, 2) {
        REP(i, S) {
            memset(dp, INF, sizeof(dp));
            REP(c, H + 1) {
                dp[0][c][f] = 0;
            }
            REP(k, 1, H + 1) {
                int t = int(p[k - 1][i] - 'A');

                REP(c, 0, H + 1) {
                    dp[k][c][t] = dp[k - 1][c][t]; // grade
                    dp[k][c][t^1] = dp[k - 1][c][t^1] + 1; // discard
                    if(c > 0) {
                        dp[k][c][t] = min(dp[k][c][t], dp[k - 1][c - 1][t^1]); // grade
                    }
                }
            }
            REP(c, H + 1) {
                F[f][c] += min(dp[H][c][0], dp[H][c][1]);
            }
        }
    }
    int minD[500];
    REP(c, H + 1) {
        minD[c] = min(F[0][c], F[1][c]);
    }

    REPP(k, K) {
        int l;
        read(l);
        int idx = lower_bound(minD, minD + H + 1, l, greater()) - minD;
        _print(idx + 1);
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
