//{{{
#include <bits/stdc++.h>
using namespace std;

#define putchar(x) cout << (x)
#define repeat(x) int _ = 0; _ < (x); ++_

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

template<typename T, typename Iter = decltype(begin(declval<T>()))>
constexpr auto printer(T&& iterable) {
    struct iterator {
        Iter iter, ed;
        auto operator!=(const iterator& other) const {
            auto ret = (iter != other.iter);
            if(not ret) cout << '\n';
            return ret;
        }
        auto& operator++() { ++iter; if(iter != ed) cout << ' '; return *this; }
        auto& operator*() { return *iter; }
    };
    struct iterable_wrapper {
        T iterable;
        auto begin() const { return iterator{ std::begin(iterable), std::end(iterable) }; }
        auto end() const { return iterator{ std::end(iterable), std::end(iterable) }; }
    };
    return iterable_wrapper{ forward<T>(iterable) };
};

template<size_t ...Is, typename T> auto getis(const T& t) { return tie(get<Is>(t)...); }
template<class T> void setmax(T& a, const T& b) { a = max(a, b); }
template<class T> void setmin(T& a, const T& b) { a = min(a, b); }

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
    print_1(head); ((cout << " ", print_1(args)), ...);
}
template<class ...T> inline void print(const T& ...args) { print_n(args...); putchar('\n'); }
template<class ...T> void read(T& ...args) { (cin >> ... >> args); }

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
static int fastio = [](){ ios_base::sync_with_stdio(false); cin.tie(0); cout.precision(17); return 0; }();

template<class T> void print_dbg(string_view s, T&& x) {
    if(is_const_char_arr_ref<T>::value) { print_n(x); } else { print_n(s, "=", x); }
}
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
const int INF = 0x3f3f3f3f;
const int MAX_N = 500005;

int default_value(int idx) {
    return idx;
}

struct PersistentArray {/*{{{*/
    int version;
    vector<vector<pair<int, int>>> values;
    unordered_map<int, int> tmp;

    PersistentArray(int n): version(1), values(n) {}

    struct wrapper {
        int ver;
        vector<vector<pair<int, int>>>& values;
        unordered_map<int, int>& tmp;

        int operator[](int idx) {
            //if(ver == version and tmp.find(idx) != tmp.end()) {
            if(tmp.find(idx) != tmp.end()) {
                return tmp[idx];
            }
            auto it = upper_bound(values[idx].begin(), values[idx].end(), make_pair(ver, INF));
            if(it == values[idx].begin()) {
                return default_value(idx);
            }
            return prev(it)->second;
        }
    };

    auto operator()(int ver) {
        if(ver == -1) {
            ver = version;
        }
        return wrapper{ ver, values, tmp };
    }

    auto& operator[](int idx) {
        return tmp[idx];
    }

    int commit() {
        for(auto [idx, value] : tmp) {
            values[idx].emplace_back(version, value);
        }
        tmp.clear();
        return version++;
    }

    void rollback() {
        tmp.clear();
    }
};/*}}}*/
struct DSU {/*{{{*/
    PersistentArray parent, rnk;
    DSU(int n): parent(n), rnk(n) {}

    int find(int idx, int ver = -1) {
        if(parent(ver)[idx] == idx) {
            return idx;
        }
        return find(parent(ver)[idx], ver);
    }

    void unite(int x, int y, int ver = -1) {
        auto px = find(x, ver);
        auto py = find(y, ver);
        if(px == py) return;
        if(rnk(ver)[px] < rnk(ver)[py]) {
            parent[px] = py;
        } else {
            parent[py] = px;
            if(rnk(ver)[px] == rnk(ver)[py]) {
                ++rnk[px];
            }
        }
    }

    int commit() {
        return parent.commit(), rnk.commit();
    }

    void rollback() {
        parent.rollback();
        rnk.rollback();
    }
};/*}}}*/

struct Solution {
    Solution(int) {
        int n, m;
        read(n, m);
        vector<pair<int, int>> E(m + 1);
        vector<int> cost(m + 1), idx(m + 1);
        for(int i : range(1, m + 1)) {
            int u, v;
            read(u, v, cost[i]);
            E[i] = {u, v};
        }
        iota(idx.begin(), idx.end(), 0);
        sort(idx.begin() + 1, idx.end(),
            [&](int i, int j) { return cost[i] < cost[j]; });

        auto dsu = DSU(n + 1);

        array<int, MAX_N> cost2ver = {};
        {
            int i = 1;
            while(i <= m) {
                int j = idx[i];
                while(i <= m and cost[idx[i]] == cost[j]) {
                    auto [u, v] = E[idx[i]];
                    dsu.unite(u, v);
                    ++i;
                }
                cost2ver[cost[j]] = dsu.commit();
            }
        }

        int q;
        read(q);
        for(repeat(q)) {
            int k;
            read(k);
            vector<int> es(k);
            for(int j : range(k)) {
                read(es[j]);
            }
            sort(es.begin(), es.end(),
                [&](int i, int j) { return cost[i] < cost[j]; });

            size_t i = 0;
            auto ok = true;
            while(i < es.size()) {
                size_t j = i;
                int ver = cost2ver[cost[es[j]]] - 1;
                while(i < es.size() and cost[es[i]] == cost[es[j]]) {
                    auto [u, v] = E[es[i]];
                    if(dsu.find(u, ver) == dsu.find(v, ver)) {
                        ok = false;
                        break;
                    }
                    dsu.unite(u, v, ver);
                    ++i;
                }
                dsu.rollback();
                if(not ok) {
                    break;
                }
            }

            if(ok) {
                print("YES");
            } else {
                print("NO");
            }
        }
    }
};

// https://codeforces.com/contest/891/problem/C

int main() {
    int T = 1;
    //cin >> T;
    for(int i = 1; i <= T; ++i) {
        ignore = Solution(i);
    }
    return 0;
}
