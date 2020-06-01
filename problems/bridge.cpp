/*{{{*/
#include "bits/stdc++.h"
using namespace std;

#define MT make_tuple
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

struct edge {
    int to, cost, id;
};
vector<vector<edge>> G;
vector<bool> visited;

bool dfs(int v, int t, vector<tuple<int, int>>& path) {
    visited[v] = true;
    if(v == t) {
        return true;
    }

    for(auto& e : G[v]) {
        if(not visited[e.to]) {
            path.emplace_back(e.cost, e.id);
            if(dfs(e.to, t, path)) {
                return true;
            }
            path.pop_back();
        }
    }
    return false;
}

vector<int> ids, low;
bool find_bridge(int v, int p, int t, int ban, int& k, int& best, int& best_id) {
    bool res = false;
    ids[v] = k++;
    low[v] = ids[v];
    visited[v] = true;

    for(auto& e : G[v]) {
        if(e.id == ban or e.id == p) {
            continue;
        }
        if(not visited[e.to]) {
            auto res_u = find_bridge(e.to, e.id, t, ban, k, best, best_id);
            res |= res_u;

            debug() << imie(v) imie(ids[v]) imie(e.to) imie(low[e.to]) imie(res_u) << endl;
            if(res_u and ids[v] < low[e.to]) {
                if(best > e.cost) {
                    best = e.cost;
                    best_id = e.id;
                }
            }
        }
        low[v] = min(low[v], low[e.to]);
    }

    debug() << imie(v) imie(ids[v]) imie(low[v]) << endl;
    if(v == t) {
        res = true;
    }
    return res;
}

void solve(int) {
    int n, m;
    cin >> n >> m;
    G.resize(n + 1);
    visited.assign(n + 1, false);

    int s, t;
    cin >> s >> t;
    for(int i = 0; i < m; ++i) {
        int u, v, cost;
        cin >> u >> v >> cost;
        G[u].push_back({v, cost, i + 1});
        G[v].push_back({u, cost, i + 1});
    }
    vector<tuple<int, int>> path = {{0, -1}};
    auto ret = dfs(s, t, path);
    if(not ret) {
        cout << "0\n0\n";;
        return;
    }

    ids.resize(n + 1);
    low.resize(n + 1);
    int best = INT_MAX, best_id0 = -1, best_id1 = -1;
    for(auto& e : path) {
        int cost, id;
        tie(cost, id) = e;

        int res = INF, res_id = 0, k = 0;
        fill(all(visited), false);
        find_bridge(s, 0, t, id, k, res, res_id);

        debug() << imie(range(ids.begin() + 1, ids.end())) << endl << endl;
        if(res_id == 0) {
            continue;
        }
        if(cost + res < best) {
            best = cost + res;
            best_id0 = id;
            best_id1 = res_id;
        }
    }

    if(best == INT_MAX) {
        cout << -1 << endl;
        return;
    }

    cout << best << endl;

    vector<int> ans;
    if(best_id0 != -1) {
        ans.push_back(best_id0);
    }
    if(best_id1 != -1) {
        ans.push_back(best_id1);
    }
    cout << ans.size() << endl;
    for(size_t i = 0; i < ans.size(); ++i) {
        cout << ans[i] << " \n"[i + 1 == ans.size()];
    }
}

// https://codeforces.com/contest/700/problem/C

int main() {
    int T = 1;
    //cin >> T;
    for(int i = 1; i <= T; ++i) {
        solve(i);
    }
    return 0;
}
