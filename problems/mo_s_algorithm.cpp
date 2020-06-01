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

struct Query {
    int l, r, id;
    pair<int, int> ord;
    inline bool operator<(const Query& other) const {
        return ord < other.ord;
    }
};

void solve(int) {
    int n, m, k;
    cin >> n >> m >> k;
    vector<int> pref(n + 1, 0);
    for(int i = 0; i < n; ++i) {
        int a;
        cin >> a;
        pref[i + 1] = pref[i] ^ a;
    }

    const int block_size = 316;
    vector<Query> queries;
    for(int i = 0; i < m; ++i) {
        int l, r;
        cin >> l >> r;
        --l; ++r;
        queries.push_back({l, r, i, make_pair(l / block_size, r)});
    }
    sort(all(queries));

    vector<LL> cnt(1 << 21, 0);
    LL res = 0;

    auto add = [&](int i) {
        res += cnt[pref[i] ^ k];
        ++cnt[pref[i]];
    };

    auto del = [&](int i) {
        --cnt[pref[i]];
        res -= cnt[pref[i] ^ k];
    };

    int l = 0, r = 0;
    vector<LL> ans(m);

    for(auto& q : queries) {
		while (q.l < l) {
			add(--l);
		}
		while (r < q.r) {
            add(r++);
		}
		while (l < q.l) {
            del(l++);
		}
		while (q.r < r) {
			del(--r);
		}
        ans[q.id] = res;
    }
    for(auto i : ans) {
        cout << i << endl;
    }
}

// https://codeforces.com/contest/617/problem/E

int main() {
    int T = 1;
    //cin >> T;
    for(int i = 1; i <= T; ++i) {
        solve(i);
    }
    return 0;
}
