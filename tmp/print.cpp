#include <bits/stdc++.h>
using namespace std;

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

    } else if constexpr(is_container<T>::value) {
        for(auto it = x.begin(); it != x.end(); ++it) {
            if(it != x.begin()) cout << ' '; print_1(*it);
        }

    } else if constexpr(is_tuple<T>::value) {
        auto print_tuple = [](const auto& ...ts) { print_n(ts...); };
        apply(print_tuple, x);

    } else if constexpr(is_pair<T>::value) {
        print_n(x.first, x.second);

    } else {
        cout << x;
    }
}

template<class T, class ...U> inline void print_n(const T& head, const U& ...args) {
    print_1(head); ((cout << ' ', print_1(args)), ...);
}
template<class ...T> inline void print(const T& ...args) {
    print_n(args...); cout << '\n';
}

int main() {
    tuple<int, string> t = {1, "2 3"};
    int x = 4;
    set<int> s = {5, 6};
    string str = "9";
    pair<int, size_t> p = {10, 11};
    array<long long, 2> a = {12, 13};
    list<vector<int>> lv = {{14}, {15, 16}};

    print(t, x, s, 7, "8", str, p, a, lv);
    return 0;
}
