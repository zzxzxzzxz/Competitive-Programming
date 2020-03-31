#include <bits/stdc++.h>
using namespace std;

namespace pyprint {//{{{
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
        print_1(head); ((cout << " ", print_1(args)), ...); }
    template<class ...T> inline void print(const T& ...args) { print_n(args...); putchar('\n'); }

    template<class T> void print_dbg(string_view s, T&& x) {
        if(is_const_char_arr_ref<T>::value) { print_n(x); } else { print_n(s, "=", x); }
    }
};
using namespace pyprint;
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
namespace itertools {//{{{
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
};
using namespace itertools;
#define repeat(x) int _ = 0; _ < (x); ++_
//}}}
namespace parser {//{{{
    template<class...>struct types{using type=types;};
    template<class Sig> struct args;
    template<class R, class...Args>
        struct args<R(Args...)>:types<Args...>{};
    template<class Sig> using args_t=typename args<Sig>::type;

    template<typename T> struct is_vector : false_type {};
    template<typename T> struct is_vector<vector<T>> : true_type {};

    template<class T> auto read(istringstream&& iss) {
        if constexpr(is_same_v<T, string>) {
            char c;
            string res;
            iss >> c >> c;
            while(c != '"') {
                res.push_back(c);
                iss >> c;
            }
            return res;
        } else if constexpr(is_vector<T>::value) {
            T res;
            char c; iss >> c;
            while(c != ']') {
                auto tmp = read<typename T::value_type>(static_cast<istringstream&&>(iss));
                res.push_back(tmp);
                iss >> c;
            }
            return res;
        } else {
            T res; iss >> res; return res;
        }
    }
    string readline() { string s; getline(cin, s); return s; }
    template <class ...Ts> auto parse_input(types<Ts...>) {
        return make_tuple(read<remove_reference_t<Ts>>(istringstream(readline()))...);
    }
};
using namespace parser;
//}}}

using PII = pair<int, int>;
using LL = long long;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());





#define METHOD //FIXME

int main() {
    auto input = parse_input(args_t<decltype(METHOD)>{});
    auto sol = Solution();
    apply([&sol](auto ...args) { print(sol.METHOD(args...)); }, input);
    return 0;
}
