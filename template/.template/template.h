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

template<class T> constexpr inline auto _start1(true_type, T&) {return 0;}
template<class T> constexpr inline auto _start1(false_type, T &x) {return x.begin();}
template<class T> constexpr inline auto _start(T &x) {return _start1(is_fundamental<T>(), x);}
template<class T> constexpr inline auto _end1(true_type, T &x) {return x;}
template<class T> constexpr inline auto _end1(false_type, T &x) {return x.end();}
template<class T> constexpr inline auto _end(T &x) {return _end1(is_fundamental<T>(), x);}

template<class T, class U> constexpr inline auto _maxtype1(true_type, true_type, T x, U) {return int(x);}
template<class V, class W, class T, class U> constexpr inline auto _maxtype1(V, W, T x, U) {return LL(x);}
template<class T, class U> constexpr inline auto _maxtype(T x, U y) {
    return _maxtype1(is_same<T, int>(), is_same<U, int>(), x, y);
}

#define GET_MACRO(_1,_2,_3,_4,NAME,...) NAME
#define REP2(i,n) for(auto i=_start(n);i!=_end(n);++i)
#define REP3(i,m,n) for(auto i=_maxtype((m),(n));i<_max_type((n),(m));++i)
#define REP4(i,m,n,s) for(auto i=_maxtype((m),(n));((s)>0 and i<_maxtype((n),(m))) or ((s)<0 and i>(n));i+=(s))
#define REP(...) GET_MACRO(__VA_ARGS__, REP4, REP3, REP2)(__VA_ARGS__)
#define PN() putchar('\n')
#define PB push_back
#define EB emplace_back

template<class T> void _read(T &x) {cin>>x;}
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
void _print(const int &x) {printf("%d", x);}
void _print(const LL &x) {printf("%lld", x);}
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
template<class T> void print1(T& x, int cond = 0) {
    _print(x);
    printf("%c", " \n"[cond]);
}

#define LLINF 0x3f3f3f3f3f3f3f3f
#define INF 0x3f3f3f3f

const int MOD = 1000000007;
#define MAX_N 300005

