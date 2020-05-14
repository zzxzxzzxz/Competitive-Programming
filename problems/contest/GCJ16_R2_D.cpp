/*{{{*/
#include "bits/stdc++.h"
using namespace std;

#define all(x) begin(x), end(x)
#define putchar(x) cout << (x)
static int fastio = [](){ ios_base::sync_with_stdio(false); cin.tie(0); cout.precision(17); return 0; }();
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

template<class T> struct rge { T b, e; auto begin() const { return b; } auto end() const { return e; } };
template<class T> rge<T> range(T i, T j) { return rge<T>{i, j}; }
template<class T> auto dud(T* x) -> decltype(cerr << *x, 0);
template<class T> char dud(...);

template<class ...T> void absorb(T&& ...) {}
template<class OUT, size_t ...Is, class T>
void debug_tuple(OUT& out, index_sequence<Is...>, const T& t) {
    absorb((out << (Is != 0 ? ", " : "") << get<Is>(t))...);
}

struct debug {
#ifdef LOCAL
    template<class T> typename enable_if<sizeof dud<T>(0) != 1, debug&>::type operator<<(T i) {
        cerr << boolalpha << i; return * this;
    }
    template<class T> typename enable_if<sizeof dud<T>(0) == 1, debug&>::type operator<<(T i) {
        return *this << range(begin(i), end(i));
    }
    template<class T, class U> debug& operator<<(pair<T, U> d) {
        return *this << "(" << d.first << ", " << d.second << ")";
    }
    template<class ...T> debug& operator<<(tuple<T...> d) {
        *this << "(";
        debug_tuple(*this, index_sequence_for<T...>{}, d);
        return *this << ")";
    }
    template<class T> debug & operator <<(rge<T> d) {
        *this << "[";
        for(auto it = d.b; it != d.e; ++it)
            *this << (it != d.b ?  ", " : "") << *it;
        return * this << "]";
    }
    debug& operator<<(ostream&(*pf)(std::ostream&)) {
        cerr << pf; return *this;
    }
#else
    template<class T> debug& operator<<(T&&) { return *this; }
    debug& operator<<(ostream&(*pf)(std::ostream&)) { return *this; }
#endif
};
#define imie(...) " [" << #__VA_ARGS__ << ": " << (__VA_ARGS__) << "] "
/*}}}*/
using PII = pair<int, int>;
using LL = long long;

const int MOD = 1e9 + 7;
const int INF = 0x3f3f3f3f;
const LL LLINF = 0x3f3f3f3f3f3f3f3f;
const int MAX_N = 200005;

void solve(int) {
    int N;
    cin >> N;
    vector<vector<int>> G(N * 2);
    vector<string> can(N);
    int cnt = 0;
    for(int i = 0; i < N; ++i) {
        cin >> can[i];
    }

    auto count = [](auto s, auto val) {
        return s + (val - '0');
    };
    for(int i = 0; i < N; ++i) {
        cnt += accumulate(all(can[i]), 0, count);
    }

    for(int i = 0; i < N; ++i) {
        for(int j = 0; j < N; ++j) {
            if(can[i][j] == '1') {
                G[i].push_back(j + N);
                G[j + N].push_back(i);
            }
        }
    }

    vector<bool> visited(N * 2, false);

    auto dfs = [&visited, &G, &N](auto self, int v) -> array<int, 2> {
        visited[v] = true;
        array<int, 2> res = {};
        res[v >= N] += 1;

        for(int u : G[v]) {
            if(not visited[u]) {
                auto res_u = self(self, u);
                res[0] += res_u[0];
                res[1] += res_u[1];
            }
        }
        return res;
    };

    map<array<int, 2>, int> dict;
    for(int i = 0; i < N * 2; ++i) {
        if(not visited[i]) {
            dict[dfs(dfs, i)] += 1;
        }
    }
    debug() << imie(dict) << endl;

    vector<pair<array<int, 2>, int>> groups(dict.begin(), dict.end());
    int m = groups.size();

    vector<int> mx, ds(m);
    for(auto& g : groups) {
        mx.push_back(g.second);
    }
    ds[0] = 1;
    for(int i = 1; i < m; ++i) {
        ds[i] = ds[i - 1] * (mx[i - 1] + 1);
    }
    debug() << imie(ds) << endl;

    auto encode = [&ds, m](vector<int>& v) {
        int res = 0;
        for(int i = 0; i < m; ++i) {
            res += v[i] * ds[i];
        }
        return res;
    };
    auto decode = [&ds, m](int u) {
        vector<int> v(m);
        for(int i = 0; i < m - 1; ++i) {
            v[i] = (u % ds[i + 1]) / ds[i];
        }
        v[m - 1] = u / ds[m - 1];
        return v;
    };

    vector<int> dp(encode(mx) + 1, -1);
    dp[0] = 0;

    auto solve = [&](auto self, int u) -> int {
        if(dp[u] != -1) {
            return dp[u];
        }

        auto v = decode(u);
        int l = 0, r = 0;
        for(int i = 0; i < m; ++i) {
            l += groups[i].first[0] * v[i];
            r += groups[i].first[1] * v[i];
        }
        if(l != r) {
            dp[u] = INF;
            return INF;
        }

        int best = l * r;
        vector<int> state(m, 0);

        while(true) {
            int i = 0;
            state[0] += 1;
            while(i < m - 1 and state[i] == v[i] + 1) {
                state[i] = 0;
                state[++i] += 1;
            }

            int code = encode(state);
            if(code == u) {
                break;
            }
            int code1 = u - code;
            auto res = self(self, code) + self(self, code1);
            best = min(best, res);
        }
        dp[u] = best;
        return best;
    };

    auto res = solve(solve, encode(mx));
    cout << res - cnt << endl;
}

int main() {
    int T;
    cin >> T;
    for(int i = 1; i <= T; ++i) {
        cout << "Case #" << i << ": ";
        solve(i);
    }
    return 0;
}
