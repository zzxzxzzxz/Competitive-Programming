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

#define MAX_N 705

int dp[MAX_N][2][MAX_N];
int D[MAX_N];

int solve(int j, int idx, bool tight, int required) {
    if(idx < 0) {
        return required == 0;
    }

    if(dp[idx][tight][required] >= 0) {
        return dp[idx][tight][required];
    }

    int ret = 0;
    int limit = tight? D[idx]: 9;
    for(int k = 0; k <= limit; ++k) {
        bool new_tight = (k == D[idx]) and tight;
        int new_required = max(0, required - int(k >= j));
        // How many numbers has at least `new_required` digits that is at least j?
        ret = (ret + solve(j, idx - 1, new_tight, new_required)) % MOD;
    }
    dp[idx][tight][required] = ret;
    return ret;
}

// https://codeforces.com/contest/908/problem/G
/*
 * This is a digit dp problem. Let's try to solve the subproblem "How many ways can
 * the i-th digit be at least j?". Let's fix j, and solve this with dp. We have
 * a dp state dp[a][b][c] = number of ways given we've considered the first `a` digits
 * of X, we need `b` more occurrences of digits at least j, and `c` is a boolean saying
 * whether or not we are strictly less than X or not yet.
 *
 * For a fixed digit, we can compute this dp table in O(n^2) time, and then compute
 * the answers to our subproblem for each i (i.e. by varying b in our table).
 */

char tmp[1000];

int main()
{
    read(tmp);
    int n = strlen(tmp);

    // reverse the number
    REP(i, n) {
        D[i] = tmp[n - i - 1] - '0';
    }

    LL ans = 0;
    REP(j, 1, 10) {
        memset(dp, -1, sizeof(dp));
        LL pow10 = 1;
        REP(i, 1, n + 1) {
            // solve: "How many numbers have at least i digits that are at least j?"
            solve(j, n - 1, true, i);

            ans = (ans + dp[n - 1][1][i] * pow10) % MOD;
            pow10 = (pow10 * 10) % MOD;
        }
    }
    print(ans);
    return 0;
}
