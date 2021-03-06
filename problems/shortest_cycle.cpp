//{{{
#pragma comment(linker, "/stack:200000000")
#pragma GCC optimize("O2")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

#include <bits/stdc++.h>
using namespace std;

#define putchar(x) cout << (x)
#define repeat(x) int _ = 0; _ < (x); ++_

template<typename T> constexpr auto range(T start, T stop, T step) {
    struct iterator {
        using difference_type = T;
        using value_type = T;
        using pointer = T*;
        using reference = T&;
        using iterator_category = random_access_iterator_tag;
        T i, step;
        T operator-(const iterator& other) { return i - other.i; };
        bool operator!=(const iterator& other) const { return i != other.i; }
        auto& operator+=(const int& n) { i += step * n; return *this; }
        auto& operator++() { i += step; return *this; }
        auto& operator*() { return i; }
    };
    struct iterable_wrapper {
        T start, stop, step;
        auto begin() const { return iterator{ start, step }; }
        auto end() const { return iterator{ stop, step }; }
        size_t size() const { return (stop - start) / step; }

        iterable_wrapper(T start_, T stop_, T step_): start(start_), stop(stop_), step(step_) {
            stop = step > 0 ? max(start, stop) : min(start, stop);
            stop += (step - (stop - start) % step) % step;
        }
    };
    return iterable_wrapper(start, stop, step);
};
template<typename T> constexpr auto range(T start, T stop) { return range(start, stop, T(1)); }
template<typename T> constexpr auto range(T stop) { return range(T(0), stop, T(1)); }

template<typename T, typename Iter = decltype(rbegin(declval<T>()))>
auto reversed(T&& iterable) {
    struct iterable_wrapper {
        T iterable;
        auto begin() const { return std::rbegin(iterable); }
        auto end() const { return std::rend(iterable); }
        auto size() const { return std::size(iterable); }
    };
    return iterable_wrapper{ forward<T>(iterable) };
}

template<typename T, typename Iter = decltype(begin(declval<T>()))>
constexpr auto printer(T&& iterable) {
    struct iterator {
        Iter iter, ed;
        auto operator!=(const iterator& other) const {
            auto ret = (iter != other.iter);
            if(not ret) cout << '\n';
            return ret;
        }
        auto& operator++() { ++iter; if(iter != ed) cout << ' '; return *this; }
        auto& operator*() { return *iter; }
    };
    struct iterable_wrapper {
        T iterable;
        auto begin() const { return iterator{ std::begin(iterable), std::end(iterable) }; }
        auto end() const { return iterator{ std::end(iterable), std::end(iterable) }; }
    };
    return iterable_wrapper{ forward<T>(iterable) };
};

template<size_t ...Is, class T, class ...Cs,
    class Iter = tuple<decltype(begin(declval<Cs>()))...>,
    class Ref = tuple<decltype(*begin(declval<Cs>()))&...>
    >
constexpr auto zip(index_sequence<Is...>, T&& iterables, Cs&&...) {
    struct iterator {
        Iter iter;
        unique_ptr<Ref> tref = nullptr;
        bool operator!=(const iterator& other) const {
            return ((get<Is>(iter) != get<Is>(other.iter)) and ...);
        }
        auto& operator++() { ((++get<Is>(iter)), ...); return *this; }
        auto& operator*() { tref.reset(new Ref(tie(*get<Is>(iter)...))); return *tref; }
    };
    struct iterable_wrapper {
        T iterables;
        auto begin() const { return iterator { Iter{ std::begin(get<Is>(iterables))... } }; }
        auto end() const { return iterator { Iter{ std::end(get<Is>(iterables))... } }; }
        auto size() const { return min({ std::size(get<Is>(iterables))... }); }
    };
    return iterable_wrapper{ forward<T>(iterables) };
}
template<class ...Cs, class = tuple<decltype(begin(declval<Cs>()))...>>
constexpr auto zip(Cs&& ...cs) {
    return zip(index_sequence_for<Cs...>{}, tuple<Cs...>(forward<Cs>(cs)...), forward<Cs>(cs)...);
}

template<typename T, typename Iter = decltype(begin(declval<T>()))>
constexpr auto enumerate(T&& iterable) {
    return zip(range(std::size(iterable)), forward<T>(iterable));
}

template<size_t ...Is, typename T> auto getis(const T& t) { return tie(get<Is>(t)...); }
template<class T> void setmax(T& a, const T& b) { a = max(a, b); }
template<class T> void setmin(T& a, const T& b) { a = min(a, b); }

template<typename T, typename = void> struct is_container : false_type {};
template<typename T> struct is_container<T, void_t<decltype(begin(declval<T>()))>> : true_type {};
template<typename T> struct is_tuple : false_type {};
template<typename ...T> struct is_tuple<tuple<T...>> : true_type {};
template<typename T> struct is_pair : false_type {};
template<typename T, typename U> struct is_pair<pair<T, U>> : true_type {};
template<typename T> struct is_str_arr : false_type {};
template<size_t N> struct is_str_arr<array<char, N>> : true_type {};
template<typename T> struct is_const_char_arr_ref : false_type {};
template<size_t N> struct is_const_char_arr_ref<char const (&)[N]> : true_type {};

template<class T> inline void print_1(const T& x) {
    if constexpr(is_same<T, string>::value or is_same<T, string_view>::value) {
        cout << x;
    } else if constexpr(is_str_arr<T>::value) {
        cout << &x[0];
    } else if constexpr(is_tuple<T>::value) {
        auto print_tuple = [](const auto& ...ts) {
            size_t idx = 0;
            cout << "("; ((cout << (idx++ ? ", " : ""), print_1(ts)), ...); cout << ")";
        };
        apply(print_tuple, x);
    } else if constexpr(is_pair<T>::value) {
        cout << "("; print_1(x.first); cout << ", "; print_1(x.second); cout << ")";
    } else if constexpr(is_container<T>::value) {
        cout << "[";
        for(auto it = x.begin(); it != x.end(); ++it) { if(it != x.begin()) cout << ", "; print_1(*it); }
        cout << "]";
    } else {
        cout << x;
    }
}
inline void print_n() {}
template<class T, class ...U> void print_n(const T& head, const U& ...args) {
    print_1(head); ((cout << " ", print_1(args)), ...); }
template<class ...T> inline void print(const T& ...args) { print_n(args...); putchar('\n'); }
template<class ...T> void read(T& ...args) { (cin >> ... >> args); }

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
static int fastio = [](){ ios_base::sync_with_stdio(false); cin.tie(0); cout.precision(17); return 0; }();

template<class T> void print_dbg(string_view s, T&& x) {
    if(is_const_char_arr_ref<T>::value) { print_n(x); } else { print_n(s, "=", x); } }
#define SELECT(_1, _2, _3, _4, _5, _6, _7, _8, NAME,...) NAME
#define dbg1(a) print_dbg(#a, a); cout << endl;
#define dbg2(a, b) print_dbg(#a, a); cout << ", "; dbg1(b);
#define dbg3(a, b, c) print_dbg(#a, a); cout << ", "; dbg2(b, c);
#define dbg4(a, b, c, d) print_dbg(#a, a); cout << ", "; dbg3(b, c, d);
#define dbg5(a, b, c, d, e) print_dbg(#a, a); cout << ", "; dbg4(b, c, d, e);
#define dbg6(a, b, c, d, e, f) print_dbg(#a, a); cout << ", "; dbg5(b, c, d, e, f);
#define dbg7(a, b, c, d, e, f, g) print_dbg(#a, a); cout << ", "; dbg6(b, c, d, e, f, g);
#define dbg8(a, b, c, d, e, f, g, h) print_dbg(#a, a); cout << ", "; dbg7(b, c, d, e, f, g, h);
#define debug(...) SELECT(__VA_ARGS__, dbg8, dbg7, dbg6, dbg5, dbg4, dbg3, dbg2, dbg1)(__VA_ARGS__)
//}}}
using PII = pair<int, int>;
using LL = long long;

const int MOD = 1e9 + 7;
const int INF = 0x3f3f3f3f;
const LL LLINF = 0x3f3f3f3f3f3f3f3f;
const int MAX_A = 1000005;

size_t seed = rng();

struct Hash {
    size_t operator()(const pair<int, int>& p) const {
        hash<int> h;
        auto hash_combine = [&h](size_t& hval, const int& v) {
            hval ^= h(v) + 0x9e3779b9 + (hval << 6) + (hval >> 2);
        };
        auto hval = seed;
        hash_combine(hval, p.first);
        hash_combine(hval, p.second);
        return hval;
    }
};

vector<vector<int>> G;
vector<int> dist;
unordered_set<pair<int, int>, Hash> ss;

int decompose(int a) {
    vector<int> ps;
    for(int i = 2; i * i <= a; ++i) {
        if(a % i == 0) {
            a /= i;
            int cnt = 1;
            while(a % i == 0) {
                a /= i;
                ++cnt;
            }
            if(cnt & 1) {
                ps.push_back(i);
            }
        }
    }
    if(a != 1) {
        ps.push_back(a);
    }

    if(ps.size() == 0) {
        return 1;
    } else if(ps.size() == 2) {
        int x = ps[0], y = ps[1];
        if(not ss.insert({x, y}).second) {
            return 2;
        }
        G[x].push_back(y);
        G[y].push_back(x);
    } else {
        int x = ps[0];
        G[x].push_back(1);
        G[1].push_back(x);
    }
    return INF;
}

int shortest_cycle(int i) {
    queue<tuple<int, int, int>> que;
    que.push({0, i, -1});
    fill(dist.begin(), dist.end(), INF);

    while(not que.empty()) {
        auto [d, v, p] = que.front();
        que.pop();

        int best = INF;
        for(int u : G[v]) {
            if(u == p) {
                continue;
            }
            if(dist[u] == INF) {
                dist[u] = d + 1;
                que.push({d + 1, u, v});
            } else {
                setmin(best, dist[u] + d + 1);
            }
        }
        if(best != INF) {
            return best;
        }
    }
    return INF;
}

void solve() {
    G.resize(MAX_A);
    dist.resize(MAX_A);

    int n;
    read(n);
    vector<int> a(n);
    for(int i : range(n)) {
        read(a[i]);
    }
    int x = INF;
    for(int i : a) {
        setmin(x, decompose(i));
    }
    if(x != INF) {
        print(x);
        return;
    }

    int best = INF;
    for(int i = 1; i * i <= MAX_A; ++i) {
        if(G[i].empty()) {
            continue;
        }
        setmin(best, shortest_cycle(i));
    }
    if(best == INF) {
        print(-1);
        return;
    }
    print(best);
}

// https://codeforces.com/contest/1325/problem/E

int main() {
    int t = 1;
    //cin >> t;
    for(int i = 0; i < t; ++i) {
        solve();
    }
    return 0;
}
