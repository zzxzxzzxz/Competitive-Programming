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
    debug& operator<<(string d) {
        *this << '"'; cerr << d; return *this << '"';
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
using DataType = pair<LL, LL>;

const DataType zero_m = {0, 0}, zero_c = {0, 0};
DataType modify(const DataType& val1, const DataType& val2) {
    ignore = val1; return val2;
}
DataType combine(const DataType& val1, const DataType& val2, int width) {
    DataType res = {};
    res.first = val1.first + val2.first;
    res.second = val1.second + val2.second + val2.first * width;
    return res;
}
struct Node {/*{{{*/
    DataType val, lazy;
    void add(DataType& x) {
        val = modify(val, x);
        lazy = modify(lazy, x);
    }
    void pull(Node& a, Node& b, int width) {
        val = combine(a.val, b.val, width);
    }
    void push(Node& a, Node& b) {
        if(lazy != zero_m) {
            a.add(lazy);
            b.add(lazy);
        }
        lazy = zero_m;
    }
};/*}}}*/
struct SegTree {/*{{{*/
    int lg(int n) { return 31 - __builtin_clz(n); }

    int base;
    vector<Node> dat;

    SegTree(int n): base(1) {
        while(base < n) base <<= 1;
        dat.resize(base * 2, {zero_c, zero_m});
    }

    const int QUERY = 0, UPDATE = 1;
    void rec(int a, int b, DataType& val, int qtype, int l, int r, int k) {
        if(b <= l or r <= a) {
            return;
        } else if(a <= l and r <= b) {
            if(qtype == QUERY) {
                val = combine(val, dat[k].val, l - a);
            } else {
                dat[k].add(val);
            }
            return;
        }

        dat[k].push(dat[k << 1], dat[k << 1 | 1]);
        int mid = l + (r - l) / 2;
        rec(a, b, val, qtype, l, mid, k << 1);
        rec(a, b, val, qtype, mid, r, k << 1 | 1);
        dat[k].pull(dat[k << 1], dat[k << 1 | 1], mid - l);
    }

    void update(int a, DataType val) {
        rec(a, a + 1, val, UPDATE, 0, base, 1);
    }
    DataType query(int a, int b) {
        DataType val = zero_c;
        rec(a, b, val, QUERY, 0, base, 1);
        return val;
    }
};/*}}}*/

void solve(int) {
    int N, Q;
    cin >> N >> Q;
    vector<int> A(N);
    for(int i = 0; i < N; ++i) {
        cin >> A[i];
    }

    array<SegTree, 2> st = { SegTree(N), SegTree(N) };

    for(int i = 0; i < N; ++i) {
        st[i & 1].update(i, {A[i], A[i]});
    }

    LL ans = 0;
    while(Q--) {
        string q;
        cin >> q;
        if(q == "Q") {
            int L, R;
            cin >> L >> R;
            --L;
            if(L & 1) {
                ans += st[1].query(L, R).second - st[0].query(L, R).second;
            } else {
                ans += st[0].query(L, R).second - st[1].query(L, R).second;
            }
        } else {
            int X, V;
            cin >> X >> V;
            --X;
            st[X & 1].update(X, {V, V});
        }
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
