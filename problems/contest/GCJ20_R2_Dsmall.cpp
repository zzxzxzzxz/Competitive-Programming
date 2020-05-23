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
    template<class T> debug& operator<<(T&&) { return *this; }
    debug& operator<<(ostream&(*pf)(std::ostream&)) { return *this; }
#endif
};
#define imie(...) " [" << #__VA_ARGS__ << ": " << (__VA_ARGS__) << "] "
/*}}}*/
using LL = long long;

const int MOD = 1e9 + 7;
const int INF = 0x3f3f3f3f;
const LL LLINF = 0x3f3f3f3f3f3f3f3f;
const int MAX_N = 100005;

int K, Q;
string P;
vector<int> S, E, depth;
vector<int> d00;
array<vector<vector<int>>, 2> parent, dist;

int lg(int n) { return 31 - __builtin_clz(n); }

int get(int _u, int _v) {
    if(depth[_u] > depth[_v]) {
        swap(_u, _v);
    }

    array<int, 2> u = {_u, _u}, v = {_v, _v};
    array<LL, 2> best_v = {0, 0}, tmp_v;

    for(int k = 0; k <= lg(K); k++) {
        if((depth[v[0]] - depth[u[0]]) & (1 << k)) {
            tmp_v = best_v;
            for(int x = 0; x <= 1; ++x) {
                if(tmp_v[0] + dist[x][k][v[0]] < tmp_v[1] + dist[x][k][v[1]]) {
                    best_v[x] = tmp_v[0] + dist[x][k][v[0]];
                } else {
                    best_v[x] = tmp_v[1] + dist[x][k][v[1]];
                }
            }
            for(int x = 0; x <= 1; ++x) {
                v[x] = parent[x][k][v[x]];
            }
        }
    }

    if(v[0] == u[0]) {
        return best_v[0];
    } else if(v[1] == u[0]) {
        return best_v[1];
    }

    array<LL, 2> best_u = {0, 0}, tmp_u;

    for(int k = lg(K); k >= 0; --k) {
        if(parent[0][k][u[0]] != parent[0][k][v[0]]) {
            tmp_u = best_u;
            tmp_v = best_v;

            for(int x = 0; x <= 1; ++x) {
                if(tmp_u[0] + dist[x][k][u[0]] < tmp_u[1] + dist[x][k][u[1]]) {
                    best_u[x] = tmp_u[0] + dist[x][k][u[0]];
                } else {
                    best_u[x] = tmp_u[1] + dist[x][k][u[1]];
                }
            }
            for(int x = 0; x <= 1; ++x) {
                if(tmp_v[0] + dist[x][k][v[0]] < tmp_v[1] + dist[x][k][v[1]]) {
                    best_v[x] = tmp_v[0] + dist[x][k][v[0]];
                } else {
                    best_v[x] = tmp_v[1] + dist[x][k][v[1]];
                }
            }

            for(int x = 0; x <= 1; ++x) {
                u[x] = parent[x][k][u[x]];
                v[x] = parent[x][k][v[x]];
            }
        }
    }

    LL ans = LLINF;
    for(int x = 0; x <= 1; ++x) {
        for(int y = 0; y <= 1; ++y) {
            ans = min(ans, best_u[x] + best_v[y] + abs(d00[u[x]] - d00[v[y]]));

        }
    }

    tmp_u = best_u;
    tmp_v = best_v;

    if(parent[0][0][v[0]] != -1) {
        for(int x = 0; x <= 1; ++x) {
            if(tmp_u[0] + dist[x][0][u[0]] < tmp_u[1] + dist[x][0][u[1]]) {
                best_u[x] = tmp_u[0] + dist[x][0][u[0]];
            } else {
                best_u[x] = tmp_u[1] + dist[x][0][u[1]];
            }
        }
        for(int x = 0; x <= 1; ++x) {
            if(tmp_v[0] + dist[x][0][v[0]] < tmp_v[1] + dist[x][0][v[1]]) {
                best_v[x] = tmp_v[0] + dist[x][0][v[0]];
            } else {
                best_v[x] = tmp_v[1] + dist[x][0][v[1]];
            }
        }
        ans = min(ans, best_v[0] + best_u[0]);
        ans = min(ans, best_v[1] + best_u[1]);
    }
    return ans;
}

void solve(int) {
    cin >> K >> Q >> P;
    S.resize(Q);
    E.resize(Q);
    vector<int> L(K), R(K), J(K);
    for(int i = 0; i < K; ++i) {
        cin >> L[i];
    }
    for(int i = 0; i < K; ++i) {
        cin >> R[i];
    }
    for(int i = 0; i < K; ++i) {
        cin >> J[i];
    }
    for(int i = 0; i < Q; ++i) {
        cin >> S[i];
        --S[i];
    }
    for(int i = 0; i < Q; ++i) {
        cin >> E[i];
        --E[i];
    }

    parent[0].assign(lg(K) + 1, vector<int>(K));
    parent[1].assign(lg(K) + 1, vector<int>(K));
    dist[0].assign(lg(K) + 1, vector<int>(K));
    dist[1].assign(lg(K) + 1, vector<int>(K));
    depth.resize(K);

    vector<tuple<int, int, int, char>> rs = {{0, K, 1, '('}, {K - 1, -1, -1, ')'}};

    for(int x = 0; x <= 1; ++x) {
        vector<pair<int, int>> stk = {{-1, 0}};
        int b, e, step;
        char c;
        tie(b, e, step, c) = rs[x];
        for(int i = b; i != e; i += step) {
            if(P[i] == c) {
                depth[i] = stk.size() - 1;
                parent[x][0][i] = stk.back().first;
                dist[x][0][i] = ++stk.back().second;
                stk.emplace_back(i, 0);
            } else {
                stk.pop_back();
                depth[i] = stk.size() - 1;
                parent[x][0][i]= stk.back().first;
                dist[x][0][i] = ++stk.back().second;
            }
        }
    }

    d00 = dist[0][0];

    for(int i = 0; i < K; ++i) {
        if(dist[0][0][i] > dist[1][0][i] + 1) {
            dist[0][0][i] = dist[1][0][i] + 1;
        } else if(dist[1][0][i] > dist[0][0][i] + 1) {
            dist[1][0][i] = dist[0][0][i] + 1;
        }
    }

    for(int t = 0; t < lg(K); ++t) {
        for(int i = 0; i < K; ++i) {
            if(parent[0][t][i] == -1) {
                parent[0][t + 1][i] = -1;
                parent[1][t + 1][i] = -1;
                dist[0][t + 1][i] = -1;
                dist[1][t + 1][i] = -1;
            } else {
                parent[0][t + 1][i] = parent[0][t][parent[0][t][i]];
                parent[1][t + 1][i] = parent[1][t][parent[0][t][i]];
                dist[0][t + 1][i] = min({
                    dist[0][t][parent[0][t][i]] + dist[0][t][i],
                    dist[0][t][parent[1][t][i]] + dist[1][t][i],
                });
                dist[1][t + 1][i] = min({
                    dist[1][t][parent[0][t][i]] + dist[0][t][i],
                    dist[1][t][parent[1][t][i]] + dist[1][t][i],
                });
                if(dist[0][t + 1][i] > dist[1][t + 1][i] + 1) {
                    dist[0][t + 1][i] = dist[1][t + 1][i] + 1;
                } else if(dist[1][t + 1][i] > dist[0][t + 1][i] + 1) {
                    dist[1][t + 1][i] = dist[0][t + 1][i] + 1;
                }
            }
        }
    }

    LL ans = 0;
    for(int i = 0; i < Q; ++i) {
        ans += get(S[i], E[i]);
    }
    cout << ans << endl;
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
