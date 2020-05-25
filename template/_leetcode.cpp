#include <bits/stdc++.h>/*{{{*/
using namespace std;
template<class T> struct rge { T b, e; };
template<class T> rge<T> range(T i, T j) { return rge<T>{i, j}; }
template<class T> auto dud(T* x) -> decltype(cerr << *x, 0);
template<class T> char dud(...);
template<class ...T> void absorb(...) {}

struct debug {
    template<class T> typename enable_if<sizeof dud<T>(0) != 1, debug&>::type operator<<(T i) {
        cerr << boolalpha << i; return * this;
    }
    template<class T> typename enable_if<sizeof dud<T>(0) == 1, debug&>::type operator<<(T i) {
        return *this << range(begin(i), end(i));
    }
    template<class T, class U> debug& operator<<(pair<T, U> d) {
        return *this << "(" << d.first << ", " << d.second << ")";
    }
    template<class ...T> debug& operator<<(tuple<T...> d) {
        *this << "(";
        debug_tuple(*this, index_sequence_for<T...>{}, d);
        return *this << ")";
    }
    template<class T> debug & operator <<(rge<T> d) {
        *this << "[";
        for(auto it = d.b; it != d.e; ++it)
            *this << (it != d.b ?  ", " : "") << *it;
        return * this << "]";
    }
    debug& operator<<(string d) {
        cerr << '"' << d << '"'; return *this;
    }
    debug& operator<<(ostream&(*pf)(std::ostream&)) {
        cerr << pf; return *this;
    }
    template<size_t ...Is, class T> void debug_tuple(index_sequence<Is...>, const T& t) {
        absorb((*this << (Is != 0 ? ", " : "") << get<Is>(t))...);
    }
};
#define imie(...) " [" << #__VA_ARGS__ << ": " << (__VA_ARGS__) << "] "

template<class...> struct types { using type = types; };
template<class Sig> struct args;
template<class R, class... Args> struct args<R(Args...)> : types<Args...> {};
template<class Sig> using args_t = typename args<Sig>::type;

template<typename T> struct is_vector : false_type {};
template<typename T> struct is_vector<vector<T>> : true_type {};
template<class T> using IsV = typename enable_if<is_vector<T>::value>::type;
template<class T> using NotV = typename enable_if<!is_vector<T>::value>::type;

auto read(istringstream& iss, string&&) {
    char c; iss >> c;
    string res;
    getline(iss, res, '"');
    return res;
}

template<class T, class = NotV<T>>
auto read(istringstream& iss, T&&) {
    T res; iss >> res;
    return res;
}

template<class T, class = IsV<T>, class VT = typename T::value_type>
auto read(istringstream& iss, T&&) {
    T res;
    char c; iss >> c;
    while(c != ']') {
        auto tmp = read<VT>(iss, VT());
        res.push_back(tmp);
        iss >> c;
    }
    return res;
}

unique_ptr<tuple<>> read1() { return make_unique<tuple<>>(tuple<>{}); }
template<class T, class ...U> unique_ptr<tuple<T, U...>> read1(T, U ...tail) {
    string s;
    getline(cin, s);
    if(cin.eof()) return nullptr;
    auto iss = istringstream(s);
    auto t1 = make_tuple(read<T>(iss, T()));
    auto t2_ptr = read1(tail...);
    return make_unique<tuple<T, U...>>(tuple_cat(t1, *t2_ptr));
}

template<class ...T, class U = tuple<remove_reference_t<T>...>>
unique_ptr<U> parse_input(types<T...>) {
    return read1<remove_reference_t<T>...>( remove_reference_t<T>()... );
}

template<size_t ...Is, class F, class T> void apply(index_sequence<Is...>, F f, T&& t) { f(get<Is>(t)...); }
template<class F, class ...T> void apply(F f, tuple<T...> t) { apply(index_sequence_for<T...>{}, f, t); }
/*}}}*/
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
#define all(x) begin(x), end(x)
using LL = long long;

#define METHOD //

int main() {
    while(true) {
        auto input = parse_input(args_t<decltype(METHOD)>{});
        if(input == nullptr) break;
        auto sol = Solution();
        apply([&sol](auto ...args) { debug() << sol.METHOD(args...) << endl; }, *input);
    }
    return 0;
}