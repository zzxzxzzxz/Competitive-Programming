//{{{
#pragma comment(linker, "/stack:200000000")
#pragma GCC optimize("O2")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

#include <bits/stdc++.h>
using namespace std;

#define putchar(x) cout << (x)
#define repeat(x) int _ = 0; _ < (x); ++_

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

template<typename T>
constexpr auto range(T start, T stop, T step) {
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

template<typename T, typename Iter = decltype(rbegin(declval<T>()))>
auto reversed(T&& iterable) {
    struct iterable_wrapper {
        Iter be, ed;
        auto begin() const { return be; }
        auto end() const { return ed; }
    };
    return iterable_wrapper{ rbegin(iterable), rend(iterable) };
}

template<typename T, typename Iter = decltype(begin(declval<T>()))>
constexpr auto printer(T&& iterable) {
    struct iterator {
        Iter iter, ed;
        auto operator!=(const iterator& other) {
            auto ret = (iter != other.iter);
            if(not ret) cout << '\n';
            return ret;
        }
        auto& operator++() { ++iter; if(iter != ed) cout << ' '; return *this; }
        auto operator*() { return *iter; }
    };
    struct iterable_wrapper {
        Iter be, ed;
        auto begin() const { return iterator{ be, ed }; }
        auto end() const { return iterator{ ed, ed }; }
    };
    return iterable_wrapper{ begin(iterable), end(iterable) };
};

template <size_t ...Is, typename T>
auto subarr(const T& t) { return tie(get<Is>(t)...); }

template<typename T, typename = void> struct is_container : false_type {};
template<typename T> struct is_container<T, void_t<decltype(begin(declval<T>()))>> : true_type {};
template<typename T> struct is_tuple : false_type {};
template<typename ...T> struct is_tuple<tuple<T...>> : true_type {};
template<typename T> struct is_pair : false_type {};
template<typename T, typename U> struct is_pair<pair<T, U>> : true_type {};

inline void print_n() {}
template<class T, class ...U> inline void print_n(const T& head, const U& ...args);

template<class T> inline void print_1(const T& x) {
    if constexpr(is_same<T, string>::value) {
        cout << x;
    } else if constexpr(is_tuple<T>::value) {
        apply([](const auto& ...ts) { print_n(ts...); }, x);
    } else if constexpr(is_pair<T>::value) {
        print_n(x.first, x.second);
    } else if constexpr(is_container<T>::value) {
        for(auto it = x.begin(); it != x.end(); ++it) { if(it != x.begin()) cout << ' '; print_1(*it); }
    } else {
        cout << x;
    }
}
template<class T, class ...U> void print_n(const T& head, const U& ...args) {
    print_1(head); ((cout << ' ', print_1(args)), ...);
}
template<class ...T> inline void print(const T& ...args) { print_n(args...); putchar('\n'); }
template<class ...T> void read(T& ...args) { (cin >> ... >> args); }

static int fastio = [](){ ios_base::sync_with_stdio(false); cin.tie(0); cout.precision(17); return 0; }();
//}}}

void solve() {
    array<array<int, 2005>, 20> a = {};

    int n, m;
    read(n, m);

    // n * m
    vector<int> col_max(m, 0), idx(m);
    for(int i : range(n)) {
        for(int j : range(m)) {
            read(a[i][j]);
            col_max[j] = max(col_max[j], a[i][j]);
        }
    }

    // n * 2^n
    vector<int> min_mask(1 << n);
    for(int i : range(1, 1 << n)) {
        min_mask[i] = i;
        for(int s : range(n)) {
            int j = (i >> s) + (i << (n - s)) & ((1 << n) - 1);
            min_mask[i] = min(min_mask[i], j);
        }
    }

    // m
    iota(idx.begin(), idx.end(), 0);
    m = min(n, m);
    nth_element(idx.begin(), idx.begin() + m - 1, idx.end(),
            [&col_max](int i, int j) { return col_max[i] > col_max[j]; });

    // min(n, m) * (2^n + 3^n)
    array<int, 5000> dp = {}, tmp = {}, mask_max = {};
    for(int u : range(m)) {
        mask_max = {};
        tmp[0] = 0;
        for(int i : range(1, 1 << n)) {
            int l = (31 - __builtin_clz(i));
            tmp[i] = a[l][idx[u]] + tmp[i ^ (1 << l)];

            int k = min_mask[i];
            mask_max[k] = max(mask_max[k], tmp[i]);
        }

        tmp = dp;
        for(int i : range(1, 1 << n)) {
            for(int j = i; j > 0; j = (j - 1) & i){
                int k = min_mask[j];
                dp[i] = max(dp[i], mask_max[k] + tmp[i - j]);
            }
        }
    }
    print(dp[(1 << n) - 1]);
}

// https://codeforces.com/contest/1209/problem/E2

int main() {
    int t;
    read(t);
    for(repeat(t)) {
        solve();
    }
    return 0;
}
