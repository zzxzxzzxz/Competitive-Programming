//{{{
#pragma comment(linker, "/stack:200000000")
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

#include <bits/stdc++.h>
using namespace std;

#define putchar(x) cout << (x)
#define repeat(x) int _ = 0; _ < (x); ++_

template<typename T> constexpr auto range(T start, T stop, T step) {
    struct iterator {
        T i, step;
        bool operator!=(const iterator& other) const { return i != other.i; }
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
    print_1(head); ((cout << " ", print_1(args)), ...);
}
template<class ...T> inline void print(const T& ...args) { print_n(args...); putchar('\n'); }
template<class ...T> void read(T& ...args) { (cin >> ... >> args); }

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
static int fastio = [](){ ios_base::sync_with_stdio(false); cin.tie(0); cout.precision(17); return 0; }();

template<class T> void print_dbg(string_view s, T&& x) {
    if(is_const_char_arr_ref<T>::value) { print_n(x); } else { print_n(s, "=", x); }
}
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
const int MAX_N = 300005;

struct Solution {
    Solution(int) {
        LL n;
        read(n);
        --n;

        array<array<int, 4>, 3> p = {{
            {0, 1, 2, 3},
            {0, 2, 3, 1},
            {0, 3, 1, 2},
        }};

        int r = n % 3;
        LL m = n / 3;
        LL s = 0, k = 0;
        while(m >= s + (1LL << (k << 1))) {
            s += (1LL << (k << 1));
            k += 1;
        }

        LL x = 1LL << (k << 1), y = m - s;
        LL z = x * (r + 1);

        while(x > 1) {
            x /= 4;
            int i = y / x;
            y %= x;
            z += x * p[r][i];
        }
        print(z);
    }
};

// https://codeforces.com/contest/1338/problem/C

int main() {
    int T = 1;
    cin >> T;
    for(int i = 1; i <= T; ++i) {
        ignore = Solution(i);
    }
    return 0;
}
