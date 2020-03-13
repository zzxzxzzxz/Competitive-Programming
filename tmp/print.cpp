#include <bits/stdc++.h>
using namespace std;

template<typename T, typename = void> struct is_container : false_type {};
template<typename T> struct is_container<T, void_t<decltype(begin(declval<T>()))>> : true_type {};
template<typename T> struct is_tuple : false_type {};
template<typename ...T> struct is_tuple<tuple<T...>> : true_type {};
template<typename T> struct is_pair : false_type {};
template<typename T, typename U> struct is_pair<pair<T, U>> : true_type {};
template<typename T> struct is_str_arr : false_type {};
template<size_t N> struct is_str_arr<array<char, N>> : true_type {};

template<class T> inline void print_1(const T& x) {
    if constexpr(is_same<T, string>::value or is_same<T, string_view>::value) {
        cout << x;
    } else if constexpr(is_str_arr<T>::value) {
        cout << &x[0];
    } else if constexpr(is_tuple<T>::value) {
        auto print_tuple = [](const auto h, const auto& ...ts) {
            cout << "("; print_1(h); ((cout << ", ", print_1(ts)), ...); cout << ")";
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
template<class ...T> inline void print(const T& ...args) {
    print_n(args...); putchar('\n');
}

void _dbg(const char*) { cout << '\n'; }
template<class T, class ...U> void _dbg(const char* sdbg, const T& head, const U& ...tail) {
    while(*sdbg and *sdbg != ',') cout << *sdbg++; print_n(" =", head);
    if(sizeof...(U)) { cout << ", "; ++sdbg; } _dbg(sdbg + 1, tail...);
}
#define debug(...) _dbg(#__VA_ARGS__, __VA_ARGS__)


int main() {
    tuple<unsigned, int, string> t = {0, 1, "2, 3"};
    int x = 4;
    set<int> s = {5, 6};
    array<char, 2> ac = {'9', '\0'};
    pair<int, size_t> p = {10, 11};
    array<long long, 2> a = {12, 13};
    list<vector<int>> lv = {{14}, {15, 16}};

    print(t, x, s, 7, "8", ac, p, a, lv);
    debug(t, x, s, 7, "8", ac, p, a, lv);
    return 0;
}
