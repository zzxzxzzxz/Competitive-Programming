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

template<typename T, size_t L, size_t I>
bool zip_it_ne(const T& t1, const T& t2) {
    if(not (get<I>(t1) != get<I>(t2))) return false;
    if(I + 1 == L) return true;
    return zip_it_ne<T, L, (I + 1) % L>(t1, t2);
}

template<class T, class TIter, size_t ...Is>
auto zip(T&& t, TIter, index_sequence<Is...>) {
    struct iterator {
        TIter iter;
        auto operator*() { return tie(*get<Is>(iter)...); }
        auto& operator++() { iter = tie(++get<Is>(iter)...); return *this; }
        bool operator!=(const iterator& other) {
            const size_t L = sizeof...(Is);
            return zip_it_ne<TIter, L, 0>(iter, other.iter);
        }
    };
    struct iterable_wrapper {
        T t;
        auto begin() const { return iterator{ TIter{std::begin(get<Is>(t))...} }; }
        auto end() const { return iterator{ TIter{std::end(get<Is>(t))...} }; }
    };
    return iterable_wrapper{ forward<T>(t) };
}
template<class ...Cs>
auto zip(Cs&& ...cs) {
    return zip(
            tuple<Cs...>{ forward<Cs>(cs)... },
            tuple<decltype(begin(declval<Cs>()))...>{ begin(cs)... },
            index_sequence_for<Cs...>{});
}

template<typename T>
auto enumerate(T&& iterable) {
    return zip(range(iterable.size()), forward<T>(iterable));
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
auto tuple_slice(const T& t) { return tie(get<Is>(t)...); }

inline void read() {}
template<class T, class ...U> inline void read(T& head, U&... tail) {
    cin >> head; read(tail...);
}
template<class T> inline void print_1(const T& x) { cout << x; }
template<class T> inline void print_1(const vector<T>& v) {
    for(auto it = v.begin(); it != v.end(); ++it) {
        if(it != v.begin()) putchar(' '); print_1(*it);
    }
}
inline void print_n() {}
template<class T, class ...U> inline void print_n(const T& head, const U&... tail) {
    print_1(head); if(sizeof...(tail)) putchar(' '); print_n(tail...);
}
template<class ...T> inline void print(const T& ...args) { print_n(args...); putchar('\n'); }

static int fastio = [](){ ios_base::sync_with_stdio(false); cin.tie(0); return 0; }();
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
