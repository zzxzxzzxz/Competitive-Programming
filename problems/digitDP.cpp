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

template<class T, int = numeric_limits<T>::min()> constexpr inline T _start(const T&) {return 0;}
template<class T> constexpr inline typename T::const_iterator _start(const T& x) {return x.begin();}
template<class T, int = numeric_limits<T>::min()> constexpr inline T _end(const T& x) {return x;}
template<class T> constexpr inline typename T::const_iterator _end(const T& x) {return x.end();}

#define PN() putchar('\n')
#define PB push_back
#define EB emplace_back
#define GET_MACRO(_1,_2,_3,_4,NAME,...) NAME
#define CHECK(a,b) static_assert(std::is_same<decltype(a), decltype(b)>::value, "REP diff type");

#define REPPP(i,s,c,t) for(i; ((s) and (c)) or (putchar("\n "[c]) and (c)); (t))
#define REPP2(i,n) REPPP(auto i=_start(n),i==_start(n),i!=_end(n),++i)
#define REPP3(i,m,n) CHECK(m,n) REPPP(auto i=(m),i==(m),i<(n),++i)
#define REPP4(i,m,n,s) CHECK(m,n) REPPP(auto i=(m),i==(m),((s)>0 and i<(n)) or ((s)<0 and i>(n)),i+=(s))
#define REPP(...) GET_MACRO(__VA_ARGS__, REPP4, REPP3, REPP2)(__VA_ARGS__)

#define REP2(i,n) for(auto i=_start(n);i!=_end(n);++i)
#define REP3(i,m,n) CHECK(m,n) for(auto i=(m);i<(n);++i)
#define REP4(i,m,n,s) CHECK(m,n) for(auto i=(m);((s)>0 and i<(n)) or ((s)<0 and i>(n));i+=(s))
#define REP(...) GET_MACRO(__VA_ARGS__, REP4, REP3, REP2)(__VA_ARGS__)

template<class T> void _read(T &x) {cin>>x;}
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
void _print(const double &x) {printf("%.16lf",x);}
void _print(const char &x) {putchar(x);}
void _print(const char *x) {printf("%s",x);}
template<class T> void _print(const vector<T> &x) {
    for(auto i = x.begin(); i != x.end(); _print(*i++)) {
        if (i != x.cbegin()) putchar(' ');
    }
}
void print() {}
template<class T, class... U> void print(const T& head, const U&... tail) {
    _print(head);
    putchar(sizeof...(tail) ? ' ' : '\n');
    print(tail...);
}

#define LLINF 0x3f3f3f3f3f3f3f3f
#define INF 0x3f3f3f3f

const int MOD = 1000000007;
#define MAX_N 300005

int dp[705][2][705];
int D[705];

int solve(int j, int len, bool is_equal, int cnt) {
    if(len == 0) {
        return cnt == 0;
    }

    if(dp[len][is_equal][cnt] >= 0) {
        return dp[len][is_equal][cnt];
    }

    int ret = 0;
    int limit = is_equal? D[len-1]: 9;
    for(int i = 0; i <= limit; ++i) {
        bool new_is_equal = (i == D[len-1]) and is_equal;
        if(i >= j) {
            ret = (ret + solve(j, len-1, new_is_equal, max(0, cnt - 1))) % MOD;
        } else {
            ret = (ret + solve(j, len-1, new_is_equal, cnt)) % MOD;
        }
    }
    dp[len][is_equal][cnt] = ret;
    return ret;
}

char tmp[1000];

int main()
{
    read(tmp);
    int n = strlen(tmp);
    REP(i, n) {
        D[i] = tmp[n-i-1] - '0';
    }
    LL ans = 0;
    REP(j, 1, 10) {
        memset(dp, -1, sizeof(dp));
        LL pow10 = 1;
        REP(i, 1, n + 1) {
            solve(j, n, true, i);
            ans = (ans + dp[n][1][i] * pow10) % MOD;
            pow10 = (pow10 * 10) % MOD;
        }
    }
    print(ans);
    return 0;
}
