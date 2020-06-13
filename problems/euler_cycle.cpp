/*{{{*/
#include "bits/stdc++.h"
using namespace std;

#define MT make_tuple
#define all(x) begin(x), end(x)
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
    debug& operator<<(ostream&(*)(std::ostream&)) { return *this; }
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
const int MAX_N = 200005;

int n;
vector<array<int, 2>> a;
vector<bool> visited;
vector<int> ans;

struct edge {
    int to, id;
};
array<vector<edge>, 1 << 20> G;

void dfs2(int v, int id) {
    while(G[v].size()) {
        auto e = G[v].back();
        G[v].pop_back();

        if(visited[e.id >> 1]) {
            continue;
        }
        visited[e.id >> 1] = true;
        dfs2(e.to, e.id);
    }
    if(id != -1) {
        ans.push_back(id ^ 1);
        ans.push_back(id);
    }
}

void dfs1(int v) {
    visited[v] = true;
    for(auto& e : G[v]) {
        if(not visited[e.to]) {
            dfs1(e.to);
        }
    }
}

bool check(int mask) {
    visited.assign(mask + 1, false);
    for(int i = 0; i <= mask; ++i) {
        G[i].clear();
    }

    for(int i = 0; i < n; ++i) {
        int u = a[i][0] & mask;
        int v = a[i][1] & mask;

        G[u].push_back({v, i * 2 + 0});
        G[v].push_back({u, i * 2 + 1});
    }

    int cnt = 0;
    for(int i = 0; i <= mask; ++i) {
        if(G[i].size() & 1) {
            return false;
        }
        if(G[i].size() > 0 and not visited[i]) {
            ++cnt;
            dfs1(i);
        }
    }
    return cnt == 1;
}

void restore(int mask) {
    ans.clear();
    visited.assign(n, false);

    for(int i = 0; i <= mask; ++i) {
        if(G[i].size() > 0) {
            dfs2(i, -1);
            break;
        }
    }
    for(int i = 0; i < n * 2; ++i) {
        printf("%d%c", ans[i] + 1, " \n"[i + 1 == n * 2]);
    }
}

void solve(int) {
    scanf("%d", &n);
    a.resize(n);
    for(int i = 0; i < n; ++i) {
        scanf("%d%d", &a[i][0], &a[i][1]);
    }

    for(int i = 20; i >= 0; --i) {
        int mask = (1 << i) - 1;
        if(check(mask)) {
            printf("%d\n", i);
            restore(mask);
            return;
        }
    }
    assert(false);
}

// https://codeforces.com/contest/1361/problem/C

int main() {
    solve(0);
    return 0;
}
