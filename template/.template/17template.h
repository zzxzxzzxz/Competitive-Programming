//{{{
#pragma comment(linker, "/stack:200000000")
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

#include <bits/stdc++.h>
using namespace std;

#define putchar(x) cout << (x)
#define repeat(x) [[maybe_unused]] auto _: range(x)

template<typename T>
constexpr auto range(T start, T stop, T step) {
    struct iterator {
        T i, step;
        bool operator!=(const iterator& other) const { return i != other.i; }
        auto& operator++() { i += step; return *this; }
        auto& operator*() { return i; }
    };
    struct iterable_wrapper {
        T start, stop, step;
        auto begin() const { return iterator{start, step}; }
        auto end() const { return iterator{stop, step}; }
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

template<size_t ...Is, class Iter>
constexpr auto zip(index_sequence<Is...>, Iter be, Iter ed) {
    struct iterator {
        Iter iter;
        bool operator!=(const iterator& other) { return ((get<Is>(iter) != get<Is>(other.iter)) and ...); }
        auto& operator++() { ((++get<Is>(iter)), ...); return *this; }
        auto operator*() { return tie(*get<Is>(iter)...); }
    };
    struct iterable_wrapper {
        Iter be, ed;
        auto begin() const { return iterator{ be }; }
        auto end() const { return iterator{ ed }; }
    };
    return iterable_wrapper{ be, ed };
}
template<class ...Cs, class Iter = tuple<decltype(begin(declval<Cs>()))...>>
constexpr auto zip(Cs&& ...cs) {
    return zip(index_sequence_for<Cs...>{}, Iter{ begin(cs)... }, Iter{ end(cs)... });
}

template<typename T>
auto enumerate(T&& iterable) {
    return zip(range(iterable.size()), forward<T>(iterable));
}

template<typename T>
auto reversed(T&& iterable) {
    struct iterable_wrapper {
        T iterable;
        auto begin() const { return iterable.rbegin(); }
        auto end() const { return iterable.rend(); }
    };
    return iterable_wrapper{ forward<T>(iterable) };
}

template<typename T, typename TIter = decltype(begin(declval<T>())),
    typename = decltype(end(declval<T>()))>
constexpr auto printer(T&& iterable) {
    struct iterator {
        TIter iter, ed;
        auto operator!=(const iterator& other) {
            auto ret = (iter != other.iter);
            if(not ret) putchar('\n');
            return ret;
        }
        auto& operator++() { ++iter; if(iter != ed) cout << " "; return *this; }
        auto operator*() { return *iter; }
    };
    struct iterable_wrapper {
        T iterable;
        auto begin() const { return iterator{ iterable.begin(), iterable.end() }; }
        auto end() const { return iterator{ iterable.end(), iterable.end() }; }
    };
    return iterable_wrapper{ forward<T>(iterable) };
};

template <size_t ... Is, typename T>
auto subarr(const T& t) { return tie(get<Is>(t)...); }

template<class ...T> void read(T& ...args) { (cin >> ... >> args); }
template<class T> inline void print_1(const T& x) { cout << x; }
template<class T> inline void print_1(const vector<T>& v) {
    for(auto it = v.begin(); it != v.end(); ++it) {
        if(it != v.begin()) putchar(' '); print_1(*it);
    }
}
inline void print_n() {}
template<class T, class ...U> void print_n(const T& head, const U& ...args) {
    print_1(head); ((cout << ' ', print_1(args)), ...);
}
template<class ...T> inline void print(const T& ...args) { print_n(args...); putchar('\n'); }

static int fastio = [](){ ios_base::sync_with_stdio(false); cin.tie(0); cout.precision(17); return 0; }();

#define SELECT(_1, _2, _3, _4, _5, _6, _7, _8, NAME,...) NAME
#define showvar(x) print_n(#x, "=", x);
#define dbg1(a) showvar(a) cout << endl;
#define dbg2(a, b) showvar(a) cout << ", "; dbg1(b);
#define dbg3(a, b, c) showvar(a) cout << ", "; dbg2(b, c);
#define dbg4(a, b, c, d) showvar(a) cout << ", "; dbg3(b, c, d);
#define dbg5(a, b, c, d, e) showvar(a) cout << ", "; dbg4(b, c, d, e);
#define dbg6(a, b, c, d, e, f) showvar(a) cout << ", "; dbg5(b, c, d, e, f);
#define dbg7(a, b, c, d, e, f, g) showvar(a) cout << ", "; dbg6(b, c, d, e, f, g);
#define dbg8(a, b, c, d, e, f, g, h) showvar(a) cout << ", "; dbg7(b, c, d, e, f, g, h);
#define debug(...) SELECT(__VA_ARGS__, dbg8, dbg7, dbg6, dbg5, dbg4, dbg3, dbg2, dbg1)(__VA_ARGS__)
//}}}
using PII = pair<int, int>;
using LL = long long;

const int MOD = 1e9 + 7;
const int INF = 1e9 + 10;
const LL LLINF = 1e18 + 1e10;
const int MAX_N = 300005;

