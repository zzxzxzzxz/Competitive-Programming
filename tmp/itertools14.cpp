//{{{
#pragma comment(linker, "/stack:200000000")
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

#include <bits/stdc++.h>
using namespace std;

#define putchar(x) cout << (x)
#define repeat(x) [[maybe_unused]] auto _: range(x)

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
        T operator-(const iterator& other) { return i - other.i; };
        auto& operator++() { i += step; return *this; }
        auto& operator+=(const int& n) { i += step * n; return *this; }
        auto& operator*() { return i; }
    };
    T start, stop, step;
    auto begin() const { return iterator{start, step}; }
    auto end() const { return iterator{stop, step}; }
    size_t size() const { return (stop - start) / step; }
    range(T start_, T stop_, T step_): start(start_), stop(stop_), step(step_) {
        stop = step > 0 ? max(start, stop) : min(start, stop);
        stop += (step - (stop - start) % step) % step;
    }
    range(T start_, T stop_): range(start_, stop_, T(1)) {}
    range(T stop_): range(T(0), stop_, T(1)) {}
};
// for c++14 (no template constructor deduction)
#define GET_MACRO(_1,_2,_3,NAME,...) NAME
#define range3(x,y,z) range<decltype(x)>(x,y,z)
#define range2(x,y) range<decltype(x)>(x,y)
#define range1(x) range<decltype(x)>(x)
#define range(...) GET_MACRO(__VA_ARGS__, range3, range2, range1)(__VA_ARGS__)

template<typename T, size_t L, size_t I>
bool zip_it_ne(const T& t1, const T& t2) {
    if(not (get<I>(t1) != get<I>(t2))) return false;
    if(I + 1 == L) return true;
    const size_t I1 = I + 1 < L ? I + 1 : I;
    return zip_it_ne<T, L, I1>(t1, t2);
}

template<class T, class TIter, size_t ...Is>
auto zip(T&& t, TIter, index_sequence<Is...>) {
    struct iterator {
        TIter iter;
        bool operator!=(const iterator& other) {
            const size_t L = sizeof...(Is);
            return zip_it_ne<TIter, L, 0>(iter, other.iter);
        }
        iterator& operator++() { iter = tie(++get<Is>(iter)...); return *this; }
        auto operator*() { return tie(*get<Is>(iter)...); }
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
            index_sequence_for<Cs...>{}
        );
}

template<typename T>
auto enumerate(T&& iterable) {
    return zip(range(iterable.size()), forward<T>(iterable));
}

template<typename T, typename TIter = decltype(begin(declval<T>())),
    typename = decltype(end(declval<T>()))>
constexpr auto printer(T&& iterable) {
    struct iterator {
        size_t i;
        TIter iter, ed;
        bool operator!=(const iterator& other) { return iter != other.iter; }
        auto& operator++() { ++i; ++iter; putchar(iter != ed ? ' ' : '\n'); return *this; }
        auto operator*() { return *iter; }
    };
    struct iterable_wrapper {
        T iterable;
        auto begin() const { return iterator{ 0, iterable.begin(), iterable.end() }; }
        auto end() const { return iterator{ 0, iterable.end(), iterable.end() }; }
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
    vector<int> v1 = {1, 2, 3};
    vector<int> v2 = {4, 5, 6};
    vector<int> v3 = {11, 12, 13, 14};
    for(const auto& t : zip(v1, v2, v3)) {
        int k1, k2, k3;
        tie(k1, k2, k3) = t;
        print(k1, k2, k3);
    }
    for(const auto& p : enumerate(v2)) {
        int i, k;
        tie(i, k) = p;
        print(i, k);
    }
    for(const auto& p : printer(enumerate(range(5, 20, 4)))) {
        int i, k;
        tie(i, k) = p;
        print_n(i, ",", k, "|");
    }
    auto r = range(5, 50, 7);
    print(*lower_bound(r.begin(), r.end(), 20));
    return 0;
}
