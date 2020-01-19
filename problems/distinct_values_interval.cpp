//{{{
#pragma comment(linker, "/stack:200000000")
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

#include <bits/stdc++.h>
using namespace std;

using PII = pair<int, int>;
using LL = long long;
using ULL = unsigned long long;
using MAT = array<array<LL, 2>, 2>;

template<class T> constexpr inline T begin(const T&) {return T(0);}
template<class T> constexpr inline T end(const T& x) {return max(T(0), x);}

#define SZ(x) int((x).size())
#define PB push_back
#define EB emplace_back
#define GET_MACRO(_1,_2,_3,_4,NAME,...) NAME
#define RM_REF_T(x) remove_reference<decltype(x)>::type
#define CHECK(a,b) static_assert(std::is_same<RM_REF_T(a), RM_REF_T(b)>::value, "REP diff types");

#define REPP__(d,c,t,f,m,n) CHECK(m,n) for(auto d; ((f) and (c)) or (putchar("\n "[c]) and (c)); (t))
#define REP__(d,c,t,f,m,n) CHECK(m,n) for(auto d; c; t)
#define REPP_(...) REPP__(__VA_ARGS__)
#define REP_(...) REP__(__VA_ARGS__)

#define FOR4(i,m,n,s) i=(m),((s)>0 and i<(n)) or ((s)<0 and i>(n)),i+=(s),i==(m),m,n
#define FOR3(i,m,n) i=(m),i<(n),++i,i==(m),m,n
#define FOR2(i,n) i=begin(n),i!=end(n),++i,i==begin(n),n,n
#define FOR(...) GET_MACRO(__VA_ARGS__, FOR4, FOR3, FOR2)(__VA_ARGS__)

#define REPP(...) REPP_(FOR(__VA_ARGS__))
#define REP(...) REP_(FOR(__VA_ARGS__))

template<class T> inline void _read(T &x) {cin >> x;}
inline void _read(size_t &x) {scanf("%zu", &x);}
inline void _read(int &x) {scanf("%d", &x);}
inline void _read(LL &x) {scanf("%lld", &x);}
inline void _read(ULL &x) {scanf("%llu", &x);}
inline void _read(double &x) {scanf("%lf", &x);}
inline void _read(char &x) {scanf(" %c", &x);}
inline void _read(char *x) {scanf("%s", x);}

inline void read() {}
template<class T, class... U> inline void read(T& head, U&... tail) {
    _read(head);
    read(tail...);
}

template<class T> inline void _print(const T &x) {cout << x;}
inline void _print(const size_t &x) {printf("%zu", x);}
inline void _print(const int &x) {printf("%d", x);}
inline void _print(const LL &x) {printf("%lld", x);}
inline void _print(const ULL &x) {printf("%llu", x);}
inline void _print(const double &x) {printf("%.16lf", x);}
inline void _print(const char &x) {putchar(x);}
inline void _print(const char *x) {printf("%s", x);}
inline void _print(const string &x) {printf("%s", x.c_str());}

inline void print() {putchar('\n');}
template<class T, class... U> inline void print(const T& head, const U&... tail) {
    _print(head);
    if(sizeof...(tail)) putchar(' ');
    print(tail...);
}

//}}}
const int MOD = 1000000007;

#define LLINF 0x3f3f3f3f3f3f3f3f
#define INF 0x3f3f3f3f

#define MAX_N 300005

int N;
int bit[MAX_N * 2];
int a[MAX_N * 2];
int last[MAX_N];
int maxi[MAX_N], mini[MAX_N];

int sum(int i) {
    int s = 0;
    while (i > 0) {
        s += bit[i];
        i -= i & -i;
    }
    return s;
}

void add(int i, int x) {
    while (i <= N) {
        bit[i] += x;
        i += i & -i;
    }
}

/*
 * https://codeforces.com/contest/1288/problem/E
 *
 * input:
 * 5 4
 * 3 5 1 4
 *
 * output:
 * 1 3
 * 2 5
 * 1 4
 * 1 5
 * 1 5
 */

int main()
{
    int n, m;
    read(n, m);
    N = n + m;

    REP(i, n) {
        a[i] = n - i;
        mini[i + 1] = i + 1;
        maxi[i + 1] = i + 1;
    }
    REP(i, m) {
        read(a[i + n]);
    }

    //REPP(i, n + m) {
    //    _print(a[i]);
    //}

    memset(last, -1, sizeof(last));
    REP(i, n + m) {
        if(i >= n) {
            mini[a[i]] = 1;
        }
        if(last[a[i]] != -1) {
            int l = last[a[i]];
            // number of distinct values in [l, i)
            int n_distinct = sum(i) - sum(l);
            maxi[a[i]] = max(maxi[a[i]], n_distinct);
            add(l + 1, -1);
        }
        add(i + 1, 1);
        last[a[i]] = i;
    }
    REP(i, 1, n + 1) {
        maxi[i] = max(maxi[i], sum(n + m) - sum(last[i]));
    }
    REP(i, 1, n + 1) {
        print(mini[i], maxi[i]);
    }
    return 0;
}
