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
        } else if constexpr(is_same<T, bool>::value) {
            cout << (x ? "true" : "false");
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

    template<typename T, typename Iter = decltype(rbegin(declval<T>()))>
        constexpr auto reversed(T&& iterable) {
            struct iterable_wrapper {
                T iterable;
                auto begin() const { return std::rbegin(iterable); }
                auto end() const { return std::rend(iterable); }
                auto size() const { return std::size(iterable); }
            };
            return iterable_wrapper{ forward<T>(iterable) };
        }

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
};
using namespace itertools;
#define repeat(x) int _ = 0; _ < (x); ++_
//}}}
namespace parser {//{{{
    template<class...>struct types{ using type = types; };
    template<class Sig> struct args;
    template<class R, class...Args>
        struct args<R(Args...)>:types<Args...>{};
    template<class Sig> using args_t=typename args<Sig>::type;

    template<typename T> struct is_vector : false_type {};
    template<typename T> struct is_vector<vector<T>> : true_type {};

    template<class T> auto read(istringstream& iss) {
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
                auto tmp = read<typename T::value_type>(iss);
                res.push_back(tmp);
                iss >> c;
            }
            return res;
        } else {
            T res; iss >> res; return res;
        }
    }

    optional<tuple<>> read1() { return {{}}; }
    template<class T, class ...U> optional<tuple<T, U...>> read1(T, U ...tail) {
        string s;
        getline(cin, s);
        if(cin.eof()) return {};
        auto iss = istringstream(s);
        auto t1 = make_tuple(read<T>(iss));
        auto t2 = read1(tail...);
        return { tuple_cat(t1, t2.value()) };
    }

    template<class ...Ts, class T = tuple<remove_reference_t<Ts>...>>
        optional<T> parse_input(types<Ts...>) {
            return read1<remove_reference_t<Ts>...>( remove_reference_t<Ts>()... );
        }
};
using namespace parser;
//}}}

using PII = pair<int, int>;
using LL = long long;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());


#define METHOD //FIXME

int main() {
    while(true) {
        auto input = parse_input(args_t<decltype(METHOD)>{});
        if(input == nullopt) break;
        auto sol = Solution();
        apply([&sol](auto ...args) { print(sol.METHOD(args...)); }, input.value());
    }
    return 0;
}
