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
using TI3 = tuple<int, int, int>;
using PII = pair<int, int>;

const int INF = 0x3f3f3f3f;
const int MAX_N = 200005;

int a[MAX_N];
TI3 trap[MAX_N];

/*
 * https://codeforces.com/problemset/problem/1260/D
 */

int main()
{
    int m, n, k, t;
    cin >> m >> n >> k >> t;
    for(int i = 0; i < m; ++i) {
        cin >> a[i];
    }

    for(int i = 0; i < k; ++i) {
        int l, r, d;
        cin >> l >> r >> d;
        trap[i] = {l - 1, r, d};
    }

    sort(trap, trap + k,
         [&](const TI3 t1, const TI3 t2) {
            int l1, r1, d1, l2, r2, d2;
            tie(l1, r1, d1) = t1;
            tie(l2, r2, d2) = t2;
            return d1 > d2;
         }
    );

    int extra = 0, remove = -1;
    set<PII> S = {{INT_MIN, INT_MIN}};

    for(int i = 0; i < k; ++i) {
        int l, r, d;
        tie(l, r, d) = trap[i];

        auto it = prev(S.upper_bound(PII(l, INT_MIN)));
        while(it != S.end() and it->first < r) {
            int l1, r1;
            tie(l1, r1) = *it;
            if(l1 < r and l < r1) {
                extra -= r1 - l1;
                l = min(l, l1);
                r = max(r, r1);
                it = S.erase(it);
            } else {
                ++it;
            }
        }
        extra += r - l;
        S.insert({l, r});

        if(t < n + 1 + extra * 2) {
            break;
        }
        remove = i;
    }
    int M = 0;
    if(remove < k - 1) {
        int l, r, d;
        tie(l, r, d) = trap[remove + 1];
        M = d;
    }

    int ans = 0;
    for(int i = 0; i < m; ++i) {
        if(a[i] >= M) {
            ans += 1;
        }
    }
    cout << ans << endl;
    return 0;
}
