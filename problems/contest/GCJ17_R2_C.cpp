//{{{
#pragma comment(linker, "/stack:200000000")
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

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

template<typename T> struct is_const_char_arr_ref : false_type {};
template<size_t N> struct is_const_char_arr_ref<char const (&)[N]> : true_type {};
template<typename T, typename = void> struct is_container : false_type {};
template<typename T>
struct is_container<T, conditional_t<false, decltype(begin(declval<T>())), void>> : true_type {};
template<class T> using IsC = typename enable_if<is_container<T>::value and
    not is_same<T, string>::value>::type;
template<class T> using NotC = typename enable_if<not is_container<T>::value or
    is_same<T, string>::value>::type;
template<class T> inline IsC<T> print_1(const T& v);
template<class T> inline NotC<T> print_1(const T& x) { cout << x; }
template<size_t N> void print_1(const array<char, N>& x) { cout << &x[0]; };
inline void print_1(const tuple<>&) { cout << "()"; };
template<size_t L, size_t I, class T> void print_tuple(const T& t) {
    if(I != 0) cout << ", "; print_1(get<I>(t));
    if(I + 1 < L) print_tuple<L, (I + 1) % L>(t);
}
template<class ...T> inline void print_1(const tuple<T...>& x) {
    cout << "("; print_tuple<sizeof...(T), 0, tuple<T...>>(x); cout << ")";
}
inline void print_n() {}
template<class T, class ...U> inline void print_n(const T& head, const U&... tail);
template<class T, class U> inline void print_1(const pair<T, U>& p) {
    cout << "("; print_1(p.first); cout << ", "; print_1(p.second); cout << ")";
}
template<class T, class ...U> inline void print_n(const T& head, const U&... tail) {
    print_1(head); if(sizeof...(tail)) cout << " "; print_n(tail...);
}
template<class T> inline IsC<T> print_1(const T& v) {
    cout << "[";
    for(auto it = v.begin(); it != v.end(); ++it) { if(it != v.begin()) cout << ", "; print_1(*it); }
    cout << "]";
}
template<class ...T> inline void print(const T& ...args) { print_n(args...); putchar('\n'); }
inline void read() {}
template<class T, class ...U> inline void read(T& head, U&... tail) { cin >> head; read(tail...); }

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
static int fastio = [](){ ios_base::sync_with_stdio(false); cin.tie(0); cout.precision(17); return 0; }();

template<class T> void print_dbg(const string& s, T&& x) {
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
using PII = pair<int, int>;
using LL = long long;

const int MOD = 1e9 + 7;
const int INF = 0x3f3f3f3f;
const LL LLINF = 0x3f3f3f3f3f3f3f3f;
const int MAX_R = 55, MAX_C = 55;

struct SAT {//{{{
    vector<vector<int>> G;
    vector<int> vs;
    vector<char> color, visited;
    int V;
    SAT(int V): V(V) {
        G.resize((V + 1) * 2);
        color.resize((V + 1) * 2);
        visited.resize((V + 1) * 2);
    }

    void clear() {
        for(auto& es : G) {
            es.clear();
        }
    }

    void add(int i, bool b) {
        int v = i * 2 + b;
        G[v ^ 1].push_back(v);
    }

    void add(int i1, bool b1, int i2, bool b2) {
        int v1 = i1 * 2 + b1, v2 = i2 * 2 + b2;
        G[v1 ^ 1].push_back(v2);
        G[v2 ^ 1].push_back(v1);
    }

    void dfs(int v) {
        visited[v] = true;
        for(int u: G[v]) {
            if(not visited[u]) {
                dfs(u);
            }
        }
        vs.push_back(v);
    }

    bool assign(int v) {
        if(visited[v]) return color[v];
        visited[v] = true;
        color[v] = true;

        for(int u: G[v]) {
            if(not assign(u)) {
                return false;
            }
        }
        return true;
    }

    vector<char> solve() {
        vs.clear();
        fill(visited.begin(), visited.end(), false);
        for(int i = 0; i < int(G.size()); ++i) {
            if(not visited[i]) {
                dfs(i);
            }
        }
        reverse(vs.begin(), vs.end());

        fill(visited.begin(), visited.end(), false);
        for(auto i : vs) {
            if(not visited[i]) {
                visited[i] = true;
                color[i] = false;
                if(not assign(i ^ 1)) {
                    return {};
                }
            }
        }
        vector<char> res;
        for(int v = 0; v < V; ++v) {
            res.push_back(color[v * 2 + 1]);
        }
        return res;
    }
};//}}}

int R, C;
char room[MAX_R][MAX_C];

auto sat = SAT(MAX_R * MAX_C);

struct Solution {
    bool go(int r, int c, array<int, 2> d, vector<array<int, 2>>& epts) {
        r += d[0];
        c += d[1];
        while(r >= 0 and r < R and c >= 0 and c < C and room[r][c] != '#') {
            if(room[r][c] == '.') {
                epts.push_back({r, c});
            } else if(room[r][c] == '|' or room[r][c] == '-') {
                return false;
            } else if(room[r][c] == '/') {
                swap(d[0], d[1]);
                d[0] = -d[0];
                d[1] = -d[1];
            } else if(room[r][c] == '\\') {
                swap(d[0], d[1]);
            }
            r += d[0];
            c += d[1];
        }
        return true;
    }

    using VCondArr = array<array<vector<pair<int, bool>>, MAX_C>, MAX_R>;

    void explore(int r, int c, VCondArr& conds) {
        vector<array<int, 2>> epts;
        auto ok1 = go(r, c, {0, 1}, epts) and go(r, c, {0, -1}, epts);
        if(not ok1) {
            sat.add((r * C + c), false);
        } else {
            for(auto& p : epts) {
                int r1 = p[0], c1 = p[1];
                conds[r1][c1].emplace_back(r * C + c, true);
            }
        }

        epts.clear();
        auto ok2 = go(r, c, {1, 0}, epts) and go(r, c, {-1, 0}, epts);
        if(not ok2) {
            sat.add((r * C + c), true);
        } else {
            for(auto& p : epts) {
                int r1 = p[0], c1 = p[1];
                conds[r1][c1].emplace_back(r * C + c, false);
            }
        }
    }
    Solution(int) {
        sat.clear();
        read(R, C);
        VCondArr conds;

        for(int i : range(R)) {
            read(room[i]);
        }

        for(int r : range(R)) {
            for(int c : range(C)) {
                if(room[r][c] == '|' or room[r][c] == '-') {
                    explore(r, c, conds);
                }
            }
        }

        for(int r : range(R)) {
            for(int c : range(C)) {
                if(room[r][c] != '.') {
                    continue;
                }
                if(conds[r][c].size() == 0 or conds[r][c].size() >= 3) {
                    print("IMPOSSIBLE");
                    return;
                }
                if(conds[r][c].size() == 1) {
                    int i0, b0;
                    tie(i0, b0) = conds[r][c][0];
                    sat.add(i0, b0);
                } else {
                    int i0, b0, i1, b1;
                    tie(i0, b0) = conds[r][c][0];
                    tie(i1, b1) = conds[r][c][1];
                    sat.add(i0, b0, i1, b1);
                }
            }
        }
        auto res = sat.solve();
        if(res.empty()) {
            print("IMPOSSIBLE");
            return;
        }
        for(int r : range(R)) {
            for(int c : range(C)) {
                if(room[r][c] == '|' or room[r][c] == '-') {
                    room[r][c] = res[r * C + c] ? '-' : '|';
                }
            }
        }
        print("POSSIBLE");
        for(int i : range(R)) {
            print(room[i]);
        }
    }
};

int main() {
    int T;
    cin >> T;
    for(int i = 1; i <= T; ++i) {
        cout << "Case #" << i << ": ";
        ignore = Solution(i);
    }
    return 0;
}
