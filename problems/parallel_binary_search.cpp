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

struct DSU {
    int n, cnt;
    vector<int> parent, rnk, csz;
    DSU(int n): n(n), cnt(0) {
        rnk.resize(n, 0);
        csz.resize(n, 1);
        parent.resize(n);
        iota(all(parent), 0);
    }

    void clear() {
        cnt = 0;
        fill(all(rnk), 0);
        fill(all(csz), 1);
        iota(all(parent), 0);
    }

    int find(int x) {
        if(x == parent[x]) {
            return x;
        }
        return parent[x] = find(parent[x]);
    }

    void unite(int x, int y) {
        ++cnt;
        int px = find(x);
        int py = find(y);
        if(px == py) {
            return;
        }
        if(rnk[px] > rnk[py]) {
            swap(px, py);
        }
        parent[px] = py;
        csz[py] += csz[px];

        if(rnk[px] == rnk[py]) {
            ++rnk[py];
        }
    }
};

struct Query {
    int x, y, z, id;
};

void solve(int) {
    int N, M;
    cin >> N >> M;
    vector<int> a(M), b(M);
    for(int i = 0; i < M; ++i) {
        cin >> a[i] >> b[i];
    }
    int Q;
    cin >> Q;
    vector<Query> queries;
    for(int i = 0; i < Q; ++i) {
        int x, y, z;
        cin >> x >> y >> z;
        queries.push_back({x, y, z, i});
    }
    queue<tuple<int, int, vector<Query>>> que;
    que.emplace(0, M, queries);

    auto dsu = DSU(N + 1);

    vector<int> ans(Q);
    while(que.size()) {
        int l, r;
        vector<Query> qs;
        tie(l, r, qs) = que.front();
        que.pop();

        int mid = l + (r - l) / 2;
        if(dsu.cnt > mid) {
            dsu.clear();
        }
        for(int i = dsu.cnt; i < mid; ++i) {
            dsu.unite(a[i], b[i]);
        }
        assert(dsu.cnt == mid);

        if(l + 1 == r) {
            for(auto& q : qs) {
                ans[q.id] = r;
            }
            continue;
        }

        vector<Query> L, R;
        for(auto& q : qs) {
            int u = dsu.csz[dsu.find(q.x)];
            if(dsu.find(q.x) != dsu.find(q.y)) {
                u += dsu.csz[dsu.find(q.y)];
            }

            if(u >= q.z) {
                L.push_back(q);
            } else {
                R.push_back(q);
            }
        }
        que.emplace(l, mid, L);
        que.emplace(mid, r, R);
    }
    for(int i = 0; i < Q; ++i) {
        cout << ans[i] << endl;
    }
}

// https://atcoder.jp/contests/agc002/tasks/agc002_d

int main() {
    int T = 1;
    //cin >> T;
    for(int i = 1; i <= T; ++i) {
        solve(i);
    }
    return 0;
}
