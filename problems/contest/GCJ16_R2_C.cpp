/*{{{*/
#include "bits/stdc++.h"
using namespace std;

#define all(x) begin(x), end(x)
#define putchar(x) cout << (x)
static int fastio = [](){ ios_base::sync_with_stdio(false); cin.tie(0); cout.precision(17); return 0; }();
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

template<class T> struct rge { T b, e; auto begin() const { return b; } auto end() const { return e; } };
template<class T> rge<T> range(T i, T j) { return rge<T>{i, j}; }
template<class T> auto dud(T* x) -> decltype(cerr << *x, 0);
template<class T> char dud(...);

template<class ...T> void absorb(T&& ...) {}
template<class OUT, size_t ...Is, class T>
void debug_tuple(OUT& out, index_sequence<Is...>, const T& t) {
    absorb((out << (Is != 0 ? ", " : "") << get<Is>(t))...);
}

struct debug {
#ifdef LOCAL
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
    debug& operator<<(ostream&(*pf)(std::ostream&)) {
        cerr << pf; return *this;
    }
#else
    template<class T> debug& operator<<(T&&) { return *this; }
    debug& operator<<(ostream&(*pf)(std::ostream&)) { return *this; }
#endif
};
#define imie(...) " [" << #__VA_ARGS__ ": " << (__VA_ARGS__) << "] "
/*}}}*/
using PII = pair<int, int>;
using LL = long long;

const int MOD = 1e9 + 7;
const int INF = 0x3f3f3f3f;
const LL LLINF = 0x3f3f3f3f3f3f3f3f;
const int MAX_N = 200005;

vector<pair<int, int>> dirs = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

auto extend(vector<string>& wall) {
    int R = wall.size(), C = wall[0].size();
    vector<string> res(R, string(C, 'o'));
    for(int i = 0; i < R; ++i) {
        for(int j = 0; j < C; ++j) {
            if(wall[i][j] != 'o') {
                res[i][j] = 'x';
            }
        }
    }
    for(int i = 0; i < R; ++i) {
        for(int j = 0; j < C; ++j) {
            if(wall[i][j] == '\\' or wall[i][j] == '/') {
                int di, dj;
                for(auto& dir : dirs) {
                    tie(di, dj) = dir;
                    int i1 = i + di, j1 = j + dj;
                    if(i1 >= 0 and i1 < R and j1 >= 0 and j1 < C and res[i1][j1] == 'o') {
                        res[i1][j1] = wall[i][j];
                    }
                }
            }
        }
    }
    return res;
}

auto merge(vector<string>& a, vector<string>& b, bool keep_old = false) {
    int R = a.size(), C = a[0].size();
    vector<string> res(R, string(C, 'o'));

    for(int i = 0; i < R; ++i) {
        for(int j = 0; j < C; ++j) {
            if(a[i][j] == 'o') {
                res[i][j] = b[i][j];
            } else if(b[i][j] == 'o') {
                res[i][j] = a[i][j];
            } else if(a[i][j] == 'x') {
                res[i][j] = b[i][j];
            } else if(b[i][j] == 'x') {
                res[i][j] = a[i][j];
            } else if(a[i][j] == b[i][j]) {
                if(keep_old) {
                    res[i][j] = a[i][j];
                } else {
                    res[i][j] = 'x';
                }
            } else {
                res.clear();
                return res;
            }
        }
    }
    return res;
}

void solve(int) {
    int R, C;
    cin >> R >> C;
    vector<int> nums((R + C) * 2);
    for(int i = 0; i < (R + C) * 2; ++i) {
        cin >> nums[i];
    }
    vector<int> cp((R + C) * 2 + 1);
    for(int i = 0; i < R + C; ++i) {
        cp[nums[i * 2]] = nums[i * 2 + 1];
        cp[nums[i * 2 + 1]] = nums[i * 2];
    }

    list<int> lst((R + C) * 2);
    iota(all(lst), 1);

    vector<pair<int, int>> tmp;
    while(lst.size()) {
        bool found = false;
        for(auto it = lst.begin(); it != lst.end(); ++it) {
            if(next(it) != lst.end() and cp[*it] == *next(it)) {
                tmp.emplace_back(*it, *next(it));
                lst.erase(next(it));
                lst.erase(it);
                found = true;
                break;
            } else if(next(it) == lst.end() and cp[*it] == *lst.begin()) {
                tmp.emplace_back(*it, *lst.begin());
                lst.erase(lst.begin());
                lst.erase(it);
                found = true;
                break;
            }
        }
        if(not found) {
            debug() << "sort ";
            cout << "\nIMPOSSIBLE" << endl;
            return;
        }
    }

    vector<string> ans(R, string(C, 'o'));
    list<pair<vector<string>, pair<int, int>>> dplst;
    for(size_t u = 0; u < tmp.size(); ++u) {
        int a, b;
        tie(a, b) = tmp[u];
        vector<string> wall(R, string(C, 'o'));

        if(a % ((R + C) * 2) == b - 1) {
            if(a == (R + C) * 2) {
                wall[0][0] = '/';
            } else if(a == C) {
                wall[0][C - 1] = '\\';
            } else if(a == R + C) {
                wall[R - 1][C - 1] = '/';
            } else if(a == R + C * 2) {
                wall[R - 1][0] = '\\';
            } else if(a < C) {
                wall[0][a - 1] = '\\';
                wall[0][a] = '/';
            } else if(a < R + C) {
                wall[a - C - 1][C - 1] = '/';
                wall[a - C][C - 1] = '\\';
            } else if(a < R + C * 2) {
                wall[R - 1][C - (a - R - C)] = '\\';
                wall[R - 1][C - (a - R - C) - 1] = '/';
            } else {
                wall[(R + C) * 2 - a][0] = '/';
                wall[(R + C) * 2 - a - 1][0] = '\\';
            }
        } else {
            vector<string> old;
            int a1 = -1, b1 = -1;
            for(auto it = dplst.begin(); it != dplst.end(); ++it) {
                tie(a1, b1) = it->second;
                if(a % ((R + C) * 2) == a1 - 1 and b1 % ((R + C) * 2) == b - 1) {
                    old = it->first;
                    break;
                }
            }
            assert(old.size() != 0);
            wall = extend(old);
        }

        for(auto it = dplst.begin(); it != dplst.end();) {
            int a1, b1;
            tie(a1, b1) = it->second;
            if(a1 - 1 == b % ((R + C) * 2) or a - 1 == b1 % ((R + C) * 2)) {
                if(a1 - 1 == b % ((R + C) * 2)) {
                    b = b1;
                } else {
                    a = a1;
                }

                wall = merge(wall, it->first);
                if(wall.empty()) {
                    debug() << "merge neighbor ";
                    cout << "\nIMPOSSIBLE" << endl;
                    return;
                }
                it = dplst.erase(it);
            } else {
                ++it;
            }
        }
        dplst.push_back({wall, {a, b}});

        ans = merge(ans, wall, true);
        if(ans.empty()) {
            debug() << "merge ans ";
            cout << "\nIMPOSSIBLE" << endl;
            return;
        }
    }
    for(int i = 0; i < R; ++i) {
        for(int j = 0; j < C; ++j) {
            if(ans[i][j] == 'o') {
                ans[i][j] = '/';
            }
        }
    }
    cout << endl;
    debug() << nums << endl;
    for(int i = 0; i < R; ++i) {
        cout << ans[i] << endl;
    }
}

int main() {
    int T;
    cin >> T;
    for(int i = 1; i <= T; ++i) {
        cout << "Case #" << i << ": ";
        solve(i);
    }
    return 0;
}
