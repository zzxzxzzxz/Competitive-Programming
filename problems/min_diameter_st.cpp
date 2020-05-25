/*{{{*/
#include "bits/stdc++.h"
using namespace std;

#define all(x) begin(x), end(x)
#define putchar(x) cout << (x)
static int fastio = [](){ ios_base::sync_with_stdio(false); cin.tie(0); cout.precision(17); return 0; }();
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

template<typename ...T> string format(const string& fmt, T&&... args) {
    size_t sz = snprintf(nullptr, 0, fmt.c_str(), args...) + 1;
    unique_ptr<char[]> buf(new char[sz]);
    snprintf(buf.get(), sz, fmt.c_str(), args...);
    return string(buf.get(), buf.get() + sz - 1);
}

template<class T> struct rge { T b, e; auto begin() const { return b; } auto end() const { return e; } };
template<class T> rge<T> range(T i, T j) { return rge<T>{i, j}; }
template<class T> auto dud(T* x) -> decltype(cerr << *x, 0);
template<class T> char dud(...);

struct debug {
#ifdef LOCAL
    debug(int line) {
        if(line) cerr << "LINE(" << line << ") -> ";
    }
    template<class T> typename enable_if<sizeof dud<T>(0) != 1, debug&>::type operator<<(T i) {
        cerr << boolalpha << i; return * this;
    }
    template<class T> typename enable_if<sizeof dud<T>(0) == 1, debug&>::type operator<<(T i) {
        return *this << range(begin(i), end(i));
    }
    template<class T, class U> debug& operator<<(pair<T, U> d) {
        return *this << "(" << d.first << ", " << d.second << ")";
    }
    debug& operator<<(tuple<>&) { return *this << "()"; };
    template<class ...T> debug& operator<<(tuple<T...> d) {
        *this << "("; debug_tuple<sizeof...(T), 0>(d);
        return *this << ")";
    }
    template<size_t L, size_t I, class T> void debug_tuple(const T& t) {
        *this << (I == 0 ? "" : ", ") << get<I>(t);
        if(I + 1 < L) debug_tuple<L, (I + 1) % L>(t);
    }
    template<class T> debug & operator <<(rge<T> d) {
        *this << "[";
        for(auto it = d.b; it != d.e; ++it)
            *this << (it != d.b ?  ", " : "") << *it;
        return *this << "]";
    }
    debug& operator<<(ostream&(*pf)(std::ostream&)) {
        cerr << pf; return *this;
    }
#else
    debug(int) {}
    template<class T> debug& operator<<(T&&) { return *this; }
    debug& operator<<(ostream&(*pf)(std::ostream&)) { return *this; }
#endif
};
#define imie(...) " [" << #__VA_ARGS__ << ": " << (__VA_ARGS__) << "] "

#define debug0()  debug(__LINE__)
#define debug1(x) debug(0)
#define GET_MACRO(_0, _1, NAME, ...) NAME
#define debug(...) GET_MACRO(_0, ##__VA_ARGS__, debug1, debug0)(__VA_ARGS__)
/*}}}*/
using LL = long long;

const int MOD = 1e9 + 7;
const int INF = 0x3f3f3f3f;
const LL LLINF = 0x3f3f3f3f3f3f3f3f;
const int MAX_N = 205;

struct edge {
    int to, cost;
};

int n, m;
vector<edge> G[MAX_N];
bool e[MAX_N][MAX_N];
int d[MAX_N][MAX_N];
vector<int> idxes[MAX_N];

int solve(int u, int v) {
    int ans = INF, dui = -1, dvi = -1, j = 1;

    while(j <= n) {
        int duj = d[u][idxes[u][j]], dvj = 0;

        while(j <= n and d[u][idxes[u][j]] == duj) {
            dvj = max(dvj, d[v][idxes[u][j]]);
            ++j;
        }

        if(dui == -1) {
            dui = duj;
            dvi = dvj;
            ans = dui;
        } else if(not (dui >= duj and dvi >= dvj)) {
            ans = min(ans, duj + (dvi + d[u][v] - duj) / 2);
            dui = duj;
            dvi = dvj;
        }
    }
    ans = min(ans, dvi);
    return ans;
}

void solve(int) {
    cin >> n >> m;

    memset(d, INF, sizeof(d));
    for(int i = 1; i <= n; ++i) {
        d[i][i] = 0;
    }

    for(int i = 0; i < m; ++i) {
        int u, v, cost;
        cin >> u >> v >> cost;
        e[u][v] = true;
        d[u][v] = cost * 2;
        d[v][u] = cost * 2;
    }

    for(int k = 1; k <= n; ++k) {
        for(int i = 1; i <= n; ++i) {
            for(int j = 1; j <= n; ++j) {
                d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
            }
        }
    }

    for(int i = 1; i <= n; ++i) {
        idxes[i].resize(n + 1);
        iota(idxes[i].begin() + 1, idxes[i].end(), 1);
        sort(idxes[i].begin() + 1, idxes[i].end(),
             [&](int u, int v) { return d[i][u] > d[i][v]; });
    }

    int ans = INF;
    for(int i = 1; i <= n; ++i) {
        for(int j = 1; j <= n; ++j) {
            if(e[i][j]) {
                ans = min(ans, solve(i, j));
            }
        }
    }
    cout << double(ans) / 2 << endl;
}

// https://codeforces.com/contest/266/problem/D

int main() {
    int T = 1;
    //cin >> T;
    for(int i = 1; i <= T; ++i) {
        solve(i);
    }
    return 0;
}
