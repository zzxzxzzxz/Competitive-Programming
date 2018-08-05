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
#define PN() putchar('\n')
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
void print() {putchar('\n');}
template<class T, class... U> void print(const T& head, const U&... tail) {
    _print(head);
    if(sizeof...(tail)) {
        putchar(' ');
    }
    print(tail...);
}


#define LLINF 0x3f3f3f3f3f3f3f3f
#define INF 0x3f3f3f3f

const int MOD = 1000000007;

//}}}
#define MAX_N (1 << 20)

int N;
int dat[2 * MAX_N];

struct SegTree {
    int zero = INT_MIN;
    int func(const int a, const int b) {
        return max(a, b);
    }

    SegTree(int n_) {
        N = 1;
        while(N < n_) {
            N <<= 1;
        }
        fill(dat, dat + 2 * N, zero);
    }

    void build() {
        for(int k = N - 1; k >= 0; k--) {
            dat[k] = func(dat[k * 2], dat[k * 2 + 1]);
        }
    }

    void update(int k, int a) {
        k += N;
        dat[k] = a;
        while(k > 1) {
            k >>= 1;
            dat[k] = func(dat[k * 2], dat[k * 2 + 1]);
        }
    }

    int query(int a, int b, int k = 1, int l = 0, int r = N) {
        if(r <= a or b <= l) {
            return zero;
        }
        if(a <= l and r <= b) {
            return dat[k];
        }
        int mid = l + (r - l) / 2;
        int vl = query(a, b, k * 2, l, mid);
        int vr = query(a, b, k * 2 + 1, mid, r);
        return func(vl, vr);
    }
};

vector<vector<int>> G;
int sz = 0;
int pos[MAX_N], from[MAX_N], to[MAX_N];

void dfs(int v) {
    pos[v] = sz;
    from[v] = sz;
    to[v] = sz;
    ++sz;

    REP(ii, G[v]) {
        dfs(*ii);
        to[v] = max(to[v], to[*ii]);
    }
}

int c[MAX_N];
int depth[MAX_N];
void dfs2(int v, int d) {
    depth[v] = d;
    REP(ii, G[v]) {
        dfs2(*ii, d + 1);
    }
}

void solve() {
    sz = 0;
    memset(pos, 0, sizeof(pos));
    memset(from, 0, sizeof(from));
    memset(to, 0, sizeof(to));
    memset(depth, 0, sizeof(depth));
    G.clear();

    int n, M;
    LL A, B;
    read(n, M, A, B);
    G.resize(n + 1);
    REP(i, 1, n) {
        int p;
        read(p);
        G[p].push_back(i);
    }
    dfs(0);
    dfs2(0, 0);
    SegTree t(n);
    for(int i = 0; i < n; i++) {
        dat[pos[i] + N] = i;
    }
    t.build();
    //REP(i, n) {
    //    print(t.query(from[i], to[i] + 1));
    //}

    REP(i, M) {
        c[i] = (A * i + B) % n;
    }
    sort(c, c + M, [&](const int i, const int j) {
        return -depth[i] < -depth[j];
    });
    LL ans = 0;
    REP(i, M) {
        int x = t.query(from[c[i]], to[c[i]] + 1);
        ans += x;
        t.update(pos[x], 0);
    }
    print(ans);
}

int main()
{
    int T;
    scanf("%d", &T);
    for(int i = 0; i < T; i++) {
        printf("Case #%d: ", i+1);
        solve();
    }

    return 0;
}
