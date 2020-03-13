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

inline void print_n(const string&) {}
template<class T, class ...U> void print_n(const string& sep, const T& head, const U& ...args);
template<class T> inline void print_1(const string& sep, const T& x) {
    if constexpr(is_same<T, string>::value) {
        cout << x;
    } else if constexpr(is_tuple<T>::value) {
        apply([sep](const auto& ...ts) { print_n(sep, ts...); }, x);
    } else if constexpr(is_pair<T>::value) {
        print_n(sep, x.first, x.second);
    } else if constexpr(is_container<T>::value) {
        for(auto it = x.begin(); it != x.end(); ++it) { if(it != x.begin()) cout << sep; print_1(sep, *it); }
    } else {
        cout << x;
    }
}
template<class T, class ...U> void print_n(const string& sep, const T& head, const U& ...args) {
    print_1(sep, head); ((cout << sep, print_1(sep, args)), ...); }
template<class ...T> inline void print_noln(const T& ...args) { print_n(" ", args...); }
template<class ...T> inline void print_brk(const T& ...args) {
    putchar('('); print_n(", ", args...); putchar(')'); }
template<class ...T> inline void print(const T& ...args) { print_n(" ", args...); putchar('\n'); }
template<class ...T> void read(T& ...args) { (cin >> ... >> args); }

void _dbg(const char*) { cout << '\n'; }
template<class T, class ...U> void _dbg(const char* sdbg, const T& head, const U& ...tail) {
    while(*sdbg and *sdbg != ',') cout << *sdbg++; print_n(" ", " =", head);
    if(sizeof...(U)) { cout << ", "; ++sdbg; } _dbg(sdbg + 1, tail...);
}
#define debug(...) _dbg(#__VA_ARGS__, __VA_ARGS__)

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
static int fastio = [](){ ios_base::sync_with_stdio(false); cin.tie(0); cout.precision(17); return 0; }();
//}}}
using PII = pair<int, int>;
using LL = long long;

const int MOD = 1e9 + 7;
const int INF = 0x3f3f3f3f;
const LL LLINF = 0x3f3f3f3f3f3f3f3f;
const int MAX_N = 300005;


void solve() {
}

int main() {
    int t = 1;
    //cin >> t;
    for(int i = 0; i < t; ++i) {
        solve();
    }
    return 0;
}
