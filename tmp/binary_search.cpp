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

#define MAX_N 300005

int n = 13;

bool check(int mid, int k) {
    return mid >= k;
}
bool check2(int mid, int k) {
    return mid <= k;
}

int test(int k) {
    vector<TI3> tmp;
    int l = -1, r = n;
    while(r - l > 1) {
        int mid = l + (r - l) / 2;
        tmp.push_back({l, r, mid});

        if(check(mid, k)) {
            r = mid;
        } else {
            l = mid;
        }
    }
    tmp.push_back({l, r, INT_MIN});

    if(not (r == k)) {
        print("============mid >= k================", k);
        REP(ii, tmp) {
            auto [a, b, c] = *ii;
            if(c == INT_MIN) {
                print(a, b);
            } else {
                print(a, b, c);
            }
        }
        print("k =", k, "r =", r);
    }
    return r;
}

int test2(int k) {
    vector<TI3> tmp;
    int l = -1, r = n;
    while(r - l > 1) {
        int mid = l + (r - l) / 2;
        tmp.push_back({l, r, mid});

        if(check2(mid, k)) {
            l = mid;
        } else {
            r = mid;
        }
    }
    tmp.push_back({l, r, INT_MIN});

    if(not (l == k)) {
        print("============mid <= k================", k);
        REP(ii, tmp) {
            auto [a, b, c] = *ii;
            if(c == INT_MIN) {
                print(a, b);
            } else {
                print(a, b, c);
            }
        }
        print("k =", k, "l =", l);
    }
    return l;
}

int main() {
    print("boundary: -1, 13");
    for(int i = -2; i <= n + 1; ++i) {
        test(i);
        test2(i);
    }
    return 0;
}
