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
using ULL = unsigned long long;

const int INF = 0x3f3f3f3f;
struct MaxFlow {/*{{{*/
    struct edge {
        int to, cap, rev;
    };
    vector<vector<edge>> G;
    vector<int> level, iter;

    MaxFlow(int V) {
        G.resize(V + 1);
        level.resize(V + 1);
        iter.resize(V + 1);
    }

    void clear() {
        for(auto& es : G) {
            es.clear();
        }
    }

    void add(int from, int to, int cap) {
        int i = G[from].size();
        int j = G[to].size();
        G[from].push_back({to, cap, j});
        G[to].push_back({from, 0, i});
    }

    void bfs(int s) {
        fill(level.begin(), level.end(), -1);
        level[s] = 0;
        deque<int> que = {s};
        while(not que.empty()) {
            int v = que.front();
            que.pop_front();
            for(auto& e : G[v]) {
                if(e.cap > 0 and level[e.to] < 0) {
                    level[e.to] = level[v] + 1;
                    que.emplace_back(e.to);
                }
            }
        }
    }

    int dfs(int v, int t, int f) {
        if(v == t) {
            return f;
        }
        for(int& i = iter[v]; i < int(G[v].size()); i++) {
            auto& e = G[v][i];
            if(e.cap > 0 and level[v] < level[e.to]) {
                int d = dfs(e.to, t, min(f, e.cap));
                if(d > 0) {
                    e.cap -= d;
                    G[e.to][e.rev].cap += d;
                    return d;
                }
            }
        }
        return 0;
    }

    int solve(int s, int t) {
        int flow = 0;
        bfs(s);
        while(level[t] != -1) {
            fill(iter.begin(), iter.end(), 0);
            int f = dfs(s, t, INF);
            while(f > 0) {
                flow += f;
                f = dfs(s, t, INF);
            }
            bfs(s);
        }
        return flow;
    }
};/*}}}*/
struct MaxFlowLB {/*{{{*/
    int s1, t1;
    MaxFlow mf;
    vector<int> din, dout;
    MaxFlowLB(int V):
        s1(V + 1), t1(V + 2), mf(MaxFlow(V + 2)), din(V + 1, 0), dout(V + 1, 0) {}

    void clear() {
        mf.clear();
        fill(din.begin(), din.end(), 0);
        fill(dout.begin(), dout.end(), 0);
    }

    void add(int from, int to, int cap, int demand) {
        mf.add(from, to, cap - demand);
        dout[from] += demand;
        din[to] += demand;
    }

    bool solve(int s, int t) {
        for(int v = 0; v < int(din.size()); ++v) {
            if(din[v] > 0) {
                mf.add(s1, v, din[v]);
            }
            if(dout[v] > 0) {
                mf.add(v, t1, dout[v]);
            }
        }
        mf.add(t, s, INF);

        mf.solve(s1, t1);
        for(auto& e : mf.G[s1]) {
            if(e.to < int(din.size()) and e.cap != 0) {
                return false;
            }
        }
        return true;
    }
};/*}}}*/

const int MAX_N = 505;
ULL S[MAX_N], T[MAX_N], U[MAX_N], V[MAX_N];
ULL ans[MAX_N][MAX_N];

auto mflb = MaxFlowLB(MAX_N * 2);

struct Solution {
    int N;
    bool solve(int k) {
        mflb.clear();
        int s = N * 2, t = N * 2 + 1;

        for(int i : range(N)) {
            for(int j : range(N)) {
                mflb.add(i, j + N, 1, 0);
            }
        }

        for(int i : range(N)) {
            /*
             * 0: one 0
             * 1: all 1
             * 2: all 0
             * 3: one 1
             */
            int row = S[i] * 2 + ((U[i] >> k) & 1);
            int col = T[i] * 2 + ((V[i] >> k) & 1);

            if(row == 0) {
                mflb.add(s, i, N - 1, 0);
            } else if(row == 1) {
                mflb.add(s, i, N, N);
            } else if(row == 2) {
                mflb.add(s, i, 0, 0);
            } else {
                mflb.add(s, i, N, 1);
            }

            if(col == 0) {
                mflb.add(i + N, t, N - 1, 0);
            } else if(col == 1) {
                mflb.add(i + N, t, N, N);
            } else if(col == 2) {
                mflb.add(i + N, t, 0, 0);
            } else {
                mflb.add(i + N, t, N, 1);
            }
        }

        if(not mflb.solve(s, t)) {
            return false;
        }

        for(int i : range(N)) {
            for(auto& e : mflb.mf.G[i]) {
                if(e.to <= N * 2 and e.cap == 0) {
                    int j = e.to - N;
                    ans[i][j] |= (1ULL << k);
                }
            }
        }
        return true;
    }

    Solution(int) {
        read(N);
        for(int i : range(N)) {
            read(S[i]);
        }
        for(int i : range(N)) {
            read(T[i]);
        }
        for(int i : range(N)) {
            read(U[i]);
        }
        for(int i : range(N)) {
            read(V[i]);
        }

        for(int i = 0; i < 64; ++i) {
            if(not solve(i)) {
                print(-1);
                return;
            }
        }

        for(int i : range(N)) {
            for(int j : printer(range(N))) {
                print_1(ans[i][j]);
            }
        }
    }
};

// https://atcoder.jp/contests/abc164/tasks/abc164_f

int main() {
    int T = 1;
    //cin >> T;
    for(int i = 1; i <= T; ++i) {
        ignore = Solution(i);
    }
    return 0;
}
