/*{{{*/
#include "bits/stdc++.h"
using namespace std;

#define all(x) begin(x), end(x)
#define putchar(x) cout << (x)
static int fastio = [](){ ios_base::sync_with_stdio(false); cin.tie(0); cout.precision(17); return 0; }();
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

template<class T> struct rge { T b, e; };
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
#define imie(x) " [" << #x ": " << (x) << "] "
/*}}}*/
using PII = pair<int, int>;
using LL = long long;

const int MOD = 1e9 + 7;
const int INF = 0x3f3f3f3f;
const LL LLINF = 0x3f3f3f3f3f3f3f3f;
const int MAX_N = 200005;

struct DSU {
    vector<int> parent;
    DSU(int n) {
        parent.resize(n);
        iota(all(parent), 0);
    }

    int find(int x) {
        if(x == parent[x]) {
            return x;
        }
        return parent[x] = find(parent[x]);
    }

    void unite(int x, int y) {
        int px = find(x), py = find(y);
        if(px != py) {
            if(rng() & 1) {
                parent[px] = py;
            } else {
                parent[py] = px;
            }
        }
    }
};

void solve(int) {
    int C;
    cin >> C;
    vector<int> E(C * 2), L(C * 2), D(C * 2);
    for(int i = 0; i < C * 2; ++i) {
        cin >> E[i] >> L[i] >> D[i];
        --E[i];
    }

    vector<vector<int>> from(C);
    for(int i = 0; i < C * 2; ++i) {
        int v = E[i];
        from[v].push_back(i);
    }

    auto dsu = DSU(C * 2);

    int ans = accumulate(all(D), 0);
    vector<pair<int, int>> tmp;

    //debug() << endl;
    for(int i = 1; i < C; ++i) {
        int arrive0 = (L[from[i][0]] + D[from[i][0]]) % 24;
        int arrive1 = (L[from[i][1]] + D[from[i][1]]) % 24;
        int w0 = (L[i * 2] - arrive0 + 24) % 24 + (L[i * 2 + 1] - arrive1 + 24) % 24;
        int w1 = (L[i * 2] - arrive1 + 24) % 24 + (L[i * 2 + 1] - arrive0 + 24) % 24;

        //debug() << imie(L[i * 2]) << imie(L[i * 2 + 1]) << imie(arrive0) << imie(arrive1) << endl;
        //debug() << imie(i) << imie(w0) << imie(w1) << endl;

        if(w0 < w1) {
            dsu.unite(from[i][0], i * 2);
            dsu.unite(from[i][1], i * 2 + 1);
            tmp.emplace_back(w1 - w0, i);
            ans += w0;
        } else {
            dsu.unite(from[i][0], i * 2 + 1);
            dsu.unite(from[i][1], i * 2);
            tmp.emplace_back(w0 - w1, i);
            ans += w1;
        }
    }
    //debug() << imie(ans) << endl;

    auto dsu_tmp = dsu;

    sort(all(tmp));
    //debug() << tmp << endl;

    int best = INF;
    for(int k0 = 0; k0 < 2; ++k0) {
        for(int k1 = 0; k1 < 2; ++k1) {
            dsu.unite(from[0][k0], k1);

            int arrive = (L[from[0][k0]] + D[from[0][k0]]) % 24;
            int res = (L[k1] - arrive + 24) % 24 + L[1 - k1];

            for(auto& p : tmp) {
                int cost, i;
                tie(cost, i) = p;
                if(dsu.find(from[i][0]) != dsu.find(from[i][1])) {
                    dsu.unite(from[i][0], from[i][1]);
                    res += cost;
                }
            }
            //debug() << imie(k0) << imie(k1) << ans + res << endl;
            best = min(best, res);
            dsu = dsu_tmp;
        }
    }
    //debug() << imie(ans) << imie(best) << endl;
    ans += best;
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
