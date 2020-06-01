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

void solve(int) {
    int N;
    cin >> N;
    vector<int> P(N + 1);
    for(int i = 1; i <= N; ++i) {
        cin >> P[i];
    }
    vector<vector<int>> G(N + 1);
    for(int i = 1; i <= N; ++i) {
        if(P[i] != -1) {
            G[i].push_back(P[i]);
            G[P[i]].push_back(i);
        }
    }

    vector<bool> visited(N + 1, false);
    auto dfs = [&](auto self, int v) -> pair<int, int> {
        visited[v] = true;
        int m1 = (P[v] == -1), res = 1;
        for(int u : G[v]) {
            if(not visited[u]) {
                int m1_u, res_u;
                tie(m1_u, res_u) = self(self, u);
                m1 += m1_u;
                res += res_u;
            }
        }
        return {m1, res};
    };

    int cycles = 0;
    vector<LL> weak;
    for(int i = 1; i <= N; ++i) {
        if(not visited[i]) {
            int m1, sz;
            tie(m1, sz) = dfs(dfs, i);
            if(m1 > 0) {
                weak.push_back(sz);
            } else {
                ++cycles;
            }
        }
    }

    debug() << imie(cycles) imie(weak) << endl;
    int M = weak.size();

    if(M == 0) {
        cout << N - cycles << endl;
        return;
    }

    vector<vector<LL>> dp(M + 1, vector<LL>(M + 1, 0));
    dp[0][0] = 1;
    for(int i = 1; i <= M; ++i) {
        dp[i][0] = 1;
        for(int j = 1; j <= i; ++j) {
            dp[i][j] = (weak[i - 1] * dp[i - 1][j - 1] + dp[i - 1][j]) % MOD;
        }
    }
    dp[M][1] = (dp[M][1] + MOD - M) % MOD;

    vector<LL> F(N + 1, 1), X(N + 1, 1);
    for(int i = 1; i <= N; ++i) {
        F[i] = F[i - 1] * i % MOD;
        X[i] = X[i - 1] * (N - 1) % MOD;
    }

    LL ans = (N - cycles) * X[M] % MOD;
    for(int i = 1; i <= M; ++i) {
        ans = (ans + MOD - dp[M][i] * F[i - 1] % MOD * X[M - i] % MOD) % MOD;
    }
    cout << ans << endl;
}

// https://atcoder.jp/contests/nomura2020/tasks/nomura2020_d

int main() {
    int T = 1;
    //cin >> T;
    for(int i = 1; i <= T; ++i) {
        solve(i);
    }
    return 0;
}
