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

template<class T> struct is_vector : false_type {};
template<class T> struct is_vector<vector<T>> : true_type {};
template<class T> typename enable_if<!is_vector<T>::value, size_t>::type bytes(const T& x) { return sizeof(x); }
template<class T> typename enable_if<is_vector<T>::value, size_t>::type bytes(const T& x) {
    return x.size() == 0 ? 0 : x.size() * bytes(x[0]);
}

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

const pair<LL, bool> LLINF = {1e18, true};
const int MAX_N = 100005;
const int MOD = 1e9 + 7;

struct Solution {
    int n;
    vector<pair<LL, bool>> g;
    vector<int> visited, selfloop;
    vector<int> vs;
    vector<vector<int>> G0, rG0, G1, rG1;

    template<class T>
        vector<int> dfs2(int v, const T& rG) {
            visited[v] = true;
            vector<int> res = {v};
            for(int u : rG[v]) {
                if(not visited[u]) {
                    auto res_u = dfs2(u, rG);
                    res.insert(res.end(), all(res_u));
                }
            }
            return res;
        }

    template<class T>
        void dfs1(int v, const T& G) {
            visited[v] = true;
            for(int u : G[v]) {
                if(not visited[u]) {
                    dfs1(u, G);
                }
            }
            vs.push_back(v);
        }

    void add(pair<LL, bool>& a, const pair<LL, bool>& b) {
        if(a == LLINF or b == LLINF) {
            a = LLINF;
        } else {
            a.first += b.first;
            if(a.first >= MOD) {
                a.first -= MOD;
                a.second = true;
            }
            a.second |= b.second;
        }
    }

    template<class T>
        pair<LL, bool> solve2(const T& G, const T& rG, int target) {
            vs.clear();
            memset(&visited[0], 0, bytes(visited));

            for(int i = 1; i <= n + 1; ++i) {
                if(not visited[i]) {
                    dfs1(i, G);
                }
            }

            memset(&visited[0], 0, bytes(visited));
            for(int i = n; i >= 0; --i) {
                if(not visited[vs[i]]) {
                    auto res = dfs2(vs[i], rG);
                    bool found = false;
                    pair<LL, bool> sum = {0, false};
                    for(auto v : res) {
                        add(sum, g[v]);

                        if(v == target) {
                            found = true;
                        }
                    }
                    if(found) {
                        return sum;
                    }

                    bool is_inf = ((res.size() > 1 or selfloop[res[0]]) and sum != make_pair(0LL, false));

                    for(auto v : res) {
                        for(auto u : G[v]) {
                            if(not visited[u]) {
                                add(g[u], is_inf ? LLINF : g[v]);
                            }
                        }
                    }
                }
            }
            assert(false);
            return LLINF;
        }

    Solution(int) {
        cin >> n;

        g.resize(n + 2);
        selfloop.resize(n + 2);
        visited.resize(n + 2);
        G0.resize(n + 2);
        rG0.resize(n + 2);
        G1.resize(n + 2);
        rG1.resize(n + 2);

        memset(&selfloop[0], 0, bytes(selfloop));
        for(int i = 1; i <= n; ++i) {
            int u, v;
            cin >> u >> v;

            G0[i].push_back(u);
            G0[i].push_back(v);
            rG0[u].push_back(i);
            rG0[v].push_back(i);

            G1[i].push_back(u == 1 ? n + 1 : u);
            rG1[u == 1 ? n + 1 : u].push_back(i);
            G1[i].push_back(v == 1 ? n + 1 : v);
            rG1[v == 1 ? n + 1 : v].push_back(i);

            if(i == u or i == v) {
                selfloop[i] = true;
            }
        }

        memset(&g[0], 0, bytes(g));
        for(int i = 1; i <= n; ++i) {
            cin >> g[i].first;
        }

        auto ans = solve2(G0, rG0, 1);

        if(ans != make_pair(0LL, false)) {
            memset(&g[0], 0, bytes(g));
            g[1] = {1, false};
            selfloop[1] = false;

            auto ans2 = solve2(G1, rG1, n + 1);
            if(ans2 != make_pair(1LL, false) and ans2 != make_pair(0LL, false)) {
                ans = LLINF;
            }
        }

        if(ans == LLINF) {
            cout << "UNBOUNDED" << endl;
        } else {
            cout << ans.first << endl;
        }
    }
};

int main() {
    int T;
    cin >> T;
    for(int i = 1; i <= T; ++i) {
        cout << "Case #" << i << ": ";
        ignore = Solution(i);
    }
    return 0;
}
