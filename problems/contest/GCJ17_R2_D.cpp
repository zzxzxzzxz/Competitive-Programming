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

const int MAX_N = 105;
array<int, 4> dr = {0, 1, 0, -1};
array<int, 4> dc = {1, 0, -1, 0};

struct MaxMatch {//{{{
    vector<vector<int>> G;
    vector<int> match;
    vector<char> used;

    MaxMatch(int V) {
        G.resize(V + 1);
        match.resize(V + 1);
        used.resize(V + 1);
    }

    void clear() {
        for(auto& es : G) {
            es.clear();
        }
    }

    void add(int u, int v) {
        G[u].push_back(v);
        G[v].push_back(u);
    }

    bool dfs(int v) {
        used[v] = true;
        for(int i = 0; i < (int)G[v].size(); i++) {
            int u = G[v][i], w = match[u];
            if(w < 0 or (not used[w] and dfs(w))) {
                match[v] = u;
                match[u] = v;
                return true;
            }
        }
        return false;
    }

    int solve() {
        int res = 0;
        fill(match.begin(), match.end(), -1);
        for(int v = 0; v < int(G.size()); v++) {
            if(match[v] < 0) {
                fill(used.begin(), used.end(), false);
                if(dfs(v)) {
                    ++res;
                }
            }
        }
        return res;
    }
};//}}}

int C, R, M;
int num[MAX_N][MAX_N];
char grid[MAX_N][MAX_N];
bool visited[MAX_N][MAX_N][2];

int nS, nT;
vector<PII> ss, ts;
vector<int> vs[MAX_N][MAX_N];
unordered_set<int> ok1[MAX_N], ok2[MAX_N];

auto mm = MaxMatch(MAX_N * 2 + 10);

void target(int id, int r0, int c0) {
    for(int i : range(4)) {
        int r = r0 + dr[i], c = c0 + dc[i];
        while(r >= 0 and r < R and c >= 0 and c < C and grid[r][c] != '#') {
            vs[r][c].push_back(id);
            r += dr[i];
            c += dc[i];
        }
    }
}

void bfs(int id, int r0, int c0) {
    memset(visited, 0, sizeof(visited));
    deque<tuple<int, int, int, bool>> dq = {{r0, c0, 0, false}};
    visited[r0][c0][0] = true;
    while(not dq.empty()) {
        int r, c, d;
        bool killed;
        tie(r, c, d, killed) = dq.front();
        dq.pop_front();
        if(not vs[r][c].empty()) {
            if(not killed) {
                ok1[id].insert(vs[r][c].begin(), vs[r][c].end());
            }
            ok2[id].insert(vs[r][c].begin(), vs[r][c].end());
            killed = true;
        }
        if(d == M) {
            continue;
        }
        for(int i : range(4)) {
            int r1 = r + dr[i];
            int c1 = c + dc[i];
            if(r1 >= 0 and r1 < R and c1 >= 0 and c1 < C and
                    grid[r1][c1] != '#' and not visited[r1][c1][killed]) {
                visited[r1][c1][killed] = true;
                dq.push_back({r1, c1, d + 1, killed});
            }
        }
    }
}

bool used[MAX_N * 2 + 10];

bool dfs(int v) {
    used[v] = true;
    for(int u : mm.G[v]) {
        int w = mm.match[u];
        if(w < 0 or (not used[w] and dfs(w))) {
            mm.match[v] = u;
            mm.match[u] = v;
            return true;
        }
    }
    return false;
};

bool augment(int v, int u) {
    memset(used, 0, sizeof(used));
    mm.match[mm.match[v]] = -1;
    int w = mm.match[u];
    if(w < 0 or (not used[w] and dfs(w))) {
        mm.match[v] = u;
        mm.match[u] = v;
        return true;
    }
    return false;
}

int solve1(vector<PII>& ans) {
    mm.clear();
    for(int i : range(R)) {
        for(int j : range(C)) {
            vs[i][j].clear();
        }
    }
    for(int i : range(MAX_N)) {
        ok1[i].clear();
        ok2[i].clear();
    }

    for(int i : range(R)) {
        for(int j : range(C)) {
            if(grid[i][j] == 'T') {
                target(num[i][j], i, j);
            }
        }
    }
    for(int i : range(R)) {
        for(int j : range(C)) {
            if(grid[i][j] == 'S') {
                bfs(num[i][j], i, j);
            }
        }
    }

    for(int i : range(nS)) {
        for(int j : ok2[i]) {
            mm.add(i, j + nS);
        }
    }

    int todo = mm.solve();
    if(todo == 0) {
        return 0;
    }

    bool found = false;
    vector<int> good;
    for(int i : range(nS)) {
        if(mm.match[i] != -1) {
            if(ok1[i].find(mm.match[i] - nS) != ok1[i].end()) {
                found = true;
                break;
            } else if(not ok1[i].empty()) {
                good.push_back(i);
            }
        }
    }
    if(not found) {
        bool ok = false;
        int s = -1, t = -1;
        for(int i : good) {
            for(int j : ok1[i]) {
                if(augment(i, j + nS)) {
                    ok = true;
                    s = i;
                    t = j;
                    break;
                }
            }
            if(ok) break;
        }
    }
    int nkill = 0;
    for(int i : range(nS)) {
        if(mm.match[i] == -1) continue;
        if(ok1[i].find(mm.match[i] - nS) != ok1[i].end()) {
            int s = i;
            int t = mm.match[i] - nS;
            nkill += 1;
            grid[ss[s].first][ss[s].second] = '.';
            grid[ts[t].first][ts[t].second] = '.';
            ans.emplace_back(s, t);
        }
    }
    return todo - nkill;
}

struct Solution {
    Solution(int) {
        read(C, R, M);
        for(int i : range(R)) {
            read(grid[i]);
        }
        nS = nT = 0;
        ss.clear();
        ts.clear();
        for(int i : range(R)) {
            for(int j : range(C)) {
                if(grid[i][j] == 'T') {
                    num[i][j] = nT++;
                    target(num[i][j], i, j);
                    ts.emplace_back(i, j);
                }
            }
        }
        for(int i : range(R)) {
            for(int j : range(C)) {
                if(grid[i][j] == 'S') {
                    num[i][j] = nS++;
                    bfs(num[i][j], i, j);
                    ss.emplace_back(i, j);
                }
            }
        }
        vector<pair<int, int>> ans;
        int ret = solve1(ans);
        while(ret > 0) {
            ret = solve1(ans);
        }
        print(ans.size());
        int s, t;
        for(auto& p : ans) {
            tie(s, t) = p;
            print(s + 1, t + 1);
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
