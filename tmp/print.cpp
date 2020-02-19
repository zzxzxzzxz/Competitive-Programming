#include <bits/stdc++.h>
using namespace std;

template <typename T, typename = void> struct is_std_container : false_type {};
template <typename T> struct is_std_container<T, void_t<decltype(begin(declval<T>()))>> : true_type {};

template<class T> using IsC = typename enable_if<is_std_container<T>::value and
    not std::is_same<T, string>::value>::type;
template<class T> using NotC = typename enable_if<not is_std_container<T>::value or
    std::is_same<T, string>::value>::type;

inline void print_n() {}
template<class T, class ...U> void print_n(const T& head, const U& ...args);

template<class T> inline NotC<T> print_1(const T& x) { cout << x; }

template<class T> inline IsC<T> print_1(const T& v) {
    for(auto it = v.begin(); it != v.end(); ++it) {
        if(it != v.begin()) cout << ' '; print_1(*it);
    }
}

template<class ...T> inline void print_1(const tuple<T...>& x) {
    auto print_tuple = [](const auto& ...ts) { print_n(ts...); };
    apply(print_tuple, x);
}

template<class T, class U> inline void print_1(const pair<T, U>& p) {
    print_n(p.first, p.second);
}

template<class T, class ...U> void print_n(const T& head, const U& ...args) {
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
