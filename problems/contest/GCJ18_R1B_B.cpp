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
        if(line) cerr << format("LINE(%03d) -> ", line);
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

template<class T> struct TD;

void solve(int) {
    int S;
    cin >> S;
    vector<int> D(S), A(S), B(S);
    for(int i = 0; i < S; ++i) {
        cin >> D[i] >> A[i] >> B[i];
    }

    vector<int> M(S), N(S);
    for(int i = 0; i < S; ++i) {
        M[i] = D[i] + A[i];
        N[i] = D[i] - B[i];
    }
    debug(0) << endl;
    debug() << "[ ";
    for(int i = 0; i < S; ++i) {
        debug(0) << format("%3d ", M[i]);
    }
    debug(0) << "]" << endl;
    debug() << "[ ";
    for(int i = 0; i < S; ++i) {
        debug(0) << format("%3d ", N[i]);
    }
    debug(0) << "]" << endl;

    int ans = 0;
    set<pair<int, int>> itvs;
    auto update_ans = [&ans, &itvs](int l, int r) {
        if(r - l > ans) {
            ans = r - l;
            itvs.clear();
        }
        if(r - l == ans) {
            itvs.insert({l, r});
        }
    };

    unordered_map<int, set<pair<int, int>>> Ms;
    {
        int cur = M[0], l = 0;
        for(int i = 1; i < S; ++i) {
            if(M[i] != cur) {
                Ms[cur].insert({l, i});
                update_ans(l, i);
                cur = M[i];
                l = i;
            }
        }
        Ms[cur].insert({l, S});
        update_ans(l, S);
    }
    set<tuple<int, int, int>> Ns = {{-INF, -INF, -INF}};
    {
        int cur = N[0], l = 0;
        for(int i = 1; i < S; ++i) {
            if(N[i] != cur) {
                Ns.insert({l, i, cur});
                update_ans(l, i);
                cur = N[i];
                l = i;
            }
        }
        Ns.insert({l, S, cur});
        update_ans(l, S);
    }

    vector<tuple<int, int, int, int>> ops;

    auto insert_ns = [&](int l, int r, int v) {
        ops.emplace_back(1, l, r, v);
        Ns.insert({l, r, v});
    };
    auto erase_ns = [&](auto it) {
        int l, r, v;
        tie(l, r, v) = *it;
        ops.emplace_back(0, l, r, v);
        return Ns.erase(it);
    };

    debug() << imie(ans) imie(itvs) << endl;

    for(auto& m : Ms) {
        auto& ps = m.second;

        for(auto& p : ps) {
            int l, r, l1, r1, v1, l2, r2, v2;
            tie(l, r) = p;
            auto it1 = prev(Ns.upper_bound(make_tuple(l, -INF, -INF)));
            auto it2 = prev(Ns.upper_bound(make_tuple(r, INF, INF)));

            if(it1 == it2) {
                continue;
            }
            tie(l1, r1, v1) = *it1;
            tie(l2, r2, v2) = *it2;

            for(auto it = next(it1); it != it2;) {
                int ll, rr, vv;
                tie(ll, rr, vv) = *it;
                it = erase_ns(it);
            }

            bool itsl = l <= r1 and l1 < l;
            bool itsr = l2 <= r and r < r2;

            if(itsl and itsr and v1 == v2) {
                erase_ns(it1);
                erase_ns(it2);
                insert_ns(l1, r2, v1);
                update_ans(l1, r2);
            } else {
                if(itsl) {
                    erase_ns(it1);
                    insert_ns(l1, r, v1);
                    update_ans(l1, r);
                }
                if(itsr) {
                    erase_ns(it2);
                    insert_ns(l, r2, v2);
                    update_ans(l, r2);
                }
            }
        }

        reverse(all(ops));
        for(auto& t : ops) {
            int op, l, r, v;
            tie(op, l, r, v) = t;
            if(op == 1) {
                Ns.erase({l, r, v});
            } else {
                Ns.insert({l, r, v});
            }
        }
        ops.clear();
    }
    debug() << imie(itvs) << endl;
    cout << ans << " " << itvs.size() << endl;
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
