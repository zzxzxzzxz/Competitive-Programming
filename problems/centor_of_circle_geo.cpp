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

template<class T> auto read(istringstream& iss) {
    if constexpr(is_same_v<T, string>) {
        char c; iss >> c;
        string res;
        getline(iss, res, '"');
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

template<class ...T, class U = tuple<remove_reference_t<T>...>>
optional<U> parse_input(types<T...>) {
    return read1<remove_reference_t<T>...>( remove_reference_t<T>()... );
}/*}}}*/
using PII = pair<int, int>;
using LL = long long;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

class Solution {
public:
    int numPoints(vector<vector<int>>& points, int r) {
        int n = points.size();
        int ans = 1;
        for(int i = 0; i < n; ++i) {
            for(int j = i + 1; j < n; ++j) {
                auto xi = points[i][0], yi = points[i][1];
                auto xj = points[j][0], yj = points[j][1];
                auto u2 = (xi - xj) * (xi - xj) + (yi - yj) * (yi - yj);
                if(r * r * 4 < u2) {
                    continue;
                }
                auto c = sqrt(double(r * r * 4 - u2) / (u2 * 4));
                auto x0 = double(xi + xj) / 2 + c * (yj - yi);
                auto y0 = double(yi + yj) / 2 + c * (xi - xj);
                auto x1 = double(xi + xj) / 2 - c * (yj - yi);
                auto y1 = double(yi + yj) / 2 - c * (xi - xj);

                for(auto [x, y] : {pair{x0, y0}, pair{x1, y1}}) {
                    int cnt = 0;
                    for(int k = 0; k < n; ++k) {
                        auto xk = points[k][0], yk = points[k][1];
                        auto d2 = (x - xk) * (x - xk) + (y - yk) * (y - yk);
                        if(d2 <= r * r + 1e-7) {
                            cnt++;
                        }
                    }
                    //debug() << imie(pair{x, y}) << imie(cnt) << endl;
                    ans = max(ans, cnt);
                }
            }
        }
        return ans;
    }
};

int numPoints(vector<vector<int>>& points, int r);
#define METHOD numPoints

// leetcode.com/contest/weekly-contest-189/problems/maximum-number-of-darts-inside-of-a-circular-dartboard

int main() {
    while(true) {
        auto input = parse_input(args_t<decltype(METHOD)>{});
        if(input == nullopt) break;
        auto sol = Solution();
        apply([&sol](auto ...args) { debug() << sol.METHOD(args...) << endl; }, input.value());
    }
    return 0;
}
