//{{{
#pragma comment(linker, "/stack:200000000")
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

#include <bits/stdc++.h>
using namespace std;

#define putchar(x) cout << (x)

template<typename T>
struct range {
    struct iterator {
        using difference_type = T;
        using value_type = T;
        using pointer = T*;
        using reference = T&;
        using iterator_category = random_access_iterator_tag;

        T i, step;
        bool operator!=(const iterator& other) const { return i != other.i; }
        auto& operator++() { i += step; return *this; }
        auto& operator*() const { return i; }
        auto& operator+=(const int& n) { i += step * n; return *this; }
        T operator-(const iterator& other) { return i - other.i; };
    };
    T start, stop, step;
    auto begin() const { return iterator{start, step}; }
    auto end() const { return iterator{stop, step}; }
    range(T start_, T stop_, T step_): start(start_), stop(stop_), step(step_) {
        stop = step > 0 ? max(start, stop) : min(start, stop);
        stop += (step - (stop - start) % step) % step;
    }
    range(T start_, T stop_): range(start_, stop_, T(1)) {}
    range(T stop_): range(T(0), stop_, T(1)) {}
};

template<typename T, typename TIter = decltype(begin(declval<T>())),
    typename = decltype(end(declval<T>()))>
struct enumerate {
    struct iterator {
        size_t i;
        TIter iter;
        bool operator!=(const iterator& other) const { return iter != other.iter; }
        auto& operator++() { ++i; ++iter; return *this; }
        auto operator*() const { return tie(i, *iter); }
    };
    T&& iterable;
    auto begin() const { return iterator{ 0, iterable.begin() }; }
    auto end() const { return iterator{ 0, iterable.end() }; }
    enumerate(T& iterable): iterable(forward<T>(iterable)) {}
    enumerate(T&& iterable): iterable(forward<T>(iterable)) {}
};

template<typename T, typename TIter = decltype(begin(declval<T>())),
    typename = decltype(end(declval<T>()))>
struct printer {
    struct iterator {
        size_t i;
        TIter iter, ed;
        bool operator!=(const iterator& other) const { return iter != other.iter; }
        auto& operator++() { ++i; ++iter; putchar(iter != ed ? ' ' : '\n'); return *this; }
        auto operator*() const { return *iter; }
    };
    T&& iterable;
    auto begin() const { return iterator{ 0, iterable.begin(), iterable.end() }; }
    auto end() const { return iterator{ 0, iterable.end(), iterable.end() }; }
    printer(T& iterable): iterable(forward<T>(iterable)) {}
    printer(T&& iterable): iterable(forward<T>(iterable)) {}
};

inline void read() {}
template<class T, class... U> inline void read(T& head, U&... tail) {
    cin >> head; read(tail...);
}
template<class T> inline void print_1(const T& x) { cout << x; }
template<class T> inline void print_1(const vector<T>& v) {
    for(auto it = v.begin(); it != v.end(); ++it) {
        if(it != v.begin()) putchar(' '); print_1(*it);
    }
}
inline void print_n() {}
template<class T, class... U> inline void print_n(const T& head, const U&... tail) {
    print_1(head); if(sizeof...(tail)) putchar(' '); print_n(tail...);
}
template<class... T> inline void print(const T&... args) { print_n(args...); putchar('\n'); }
static int fastio = [](){ ios_base::sync_with_stdio(false); cin.tie(0); return 0; }();

#define repeat(x) [[maybe_unused]] auto _: range(x)

// for c++14 (no template constructor deduction)
#define GET_MACRO(_1,_2,_3,NAME,...) NAME
#define range3(x,y,z) range<decltype(x)>(x,y,z)
#define range2(x,y) range<decltype(x)>(x,y)
#define range1(x) range<decltype(x)>(x)
#define range(...) GET_MACRO(__VA_ARGS__, range3, range2, range1)(__VA_ARGS__)
#define enumerate(x) enumerate<decltype(x)>(x)
#define printer(x) printer<decltype(x)>(x)
//}}}
using PII = pair<int, int>;
using LL = long long;

const int MOD = 1e9 + 7;
const int INF = 1e9 + 10;
const LL LLINF = 1e18 + 10;
const int MAX_N = 300005;


int main() {
    return 0;
}
