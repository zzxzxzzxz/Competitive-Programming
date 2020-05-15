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

template<class T> struct IterMask {/*{{{*/
    int n;
    vector<T> ds;
    T mx;
    IterMask(vector<T>& v): n(v.size()), ds({1}), mx(0) {
        for(int i = 0; i < n; ++i) {
            ds.push_back(ds.back() * (1 + v[i]));
        }
        mx = ds.back();
    }

    auto and_mask(T i, T m) {
        for(int l = 0; l < int(ds.size()) - 1; ++l) {
            auto j = i % ds[l + 1] / ds[l];
            auto k = m % ds[l + 1] / ds[l];
            if(j > k) i -=  (j - k) * ds[l];
        }
        return i;
    }

    auto decode(T m) {
        struct iterator {
            const T m;
            const vector<T>& ds;
            int i;
            auto operator!=(const iterator& other) const { return i != other.i; }
            auto& operator++() { ++i; return *this; }
            auto operator*() { return m % ds[i + 1] / ds[i]; }
        };
        struct iterable_wrapper {
            const T m;
            const vector<T>& ds;
            auto begin() const { return iterator{ m, ds, 0 }; }
            auto end() const { return iterator{ m, ds, int(ds.size()) - 1 }; }
        };
        return iterable_wrapper{ m, ds };
    };
};/*}}}*/

void solve(int) {
    int N;
    cin >> N;
    vector<string> can(N);
    for(int i = 0; i < N; ++i) {
        cin >> can[i];
    }

    int cnt = 0;
    vector<vector<int>> G(N * 2);
    for(int i = 0; i < N; ++i) {
        for(int j = 0; j < N; ++j) {
            if(can[i][j] == '1') {
                ++cnt;
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

    vector<array<int, 2>> groups;
    vector<int> nums;
    for(auto& p : dict) {
        groups.push_back(p.first);
        nums.push_back(p.second);
    }

    auto im = IterMask<int>(nums);

    vector<int> dp(im.mx);
    for(auto mask = 0; mask < im.mx; ++mask) {

        int l = 0, r = 0, j = 0;
        for(auto i : im.decode(mask)) {
            l += groups[j][0] * i;
            r += groups[j][1] * i;
            ++j;
        }
        if(l != r) {
            dp[mask] = INF;
            continue;
        }

        dp[mask] = l * l;
        for(auto subm = mask; subm > 0; subm = im.and_mask(subm - 1, mask)) {
            dp[mask] = min(dp[mask], dp[subm] + dp[mask - subm]);
        }
    }
    cout << dp[im.mx - 1] - cnt << endl;
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
