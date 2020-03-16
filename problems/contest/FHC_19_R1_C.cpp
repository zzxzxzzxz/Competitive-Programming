//{{{
#pragma comment(linker, "/stack:200000000")
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

#include <bits/stdc++.h>
using namespace std;

using PII = pair<int, int>;
using TI3 = tuple<int, int, int>;
using LL = long long;
using ULL = unsigned long long;
using MAT = array<array<LL, 2>, 2>;

template<class T> constexpr inline T begin(const T&) {return 0;}
template<class T> constexpr inline T end(const T& x) {return max(T(0), x);}

#define SZ(x) int((x).size())
#define PB push_back
#define EB emplace_back
#define GET_MACRO(_1,_2,_3,_4,NAME,...) NAME
#define CHECK(a,b) static_assert(std::is_same<decltype(a), decltype(b)>::value, "REP diff types");

#define REPPP(i,s,c,t) for(i; ((s) and (c)) or (putchar("\n "[c]) and (c)); (t))
#define REPP2(i,n) REPPP(auto i=begin(n),i==begin(n),i!=end(n),++i)
#define REPP3(i,m,n) CHECK(m,n) REPPP(auto i=(m),i==(m),i<(n),++i)
#define REPP4(i,m,n,s) CHECK(m,n) REPPP(auto i=(m),i==(m),((s)>0 and i<(n)) or ((s)<0 and i>(n)),i+=(s))
#define REPP(...) GET_MACRO(__VA_ARGS__, REPP4, REPP3, REPP2)(__VA_ARGS__)

#define REP2(i,n) for(auto i=begin(n);i!=end(n);++i)
#define REP3(i,m,n) CHECK(m,n) for(auto i=(m);i<(n);++i)
#define REP4(i,m,n,s) CHECK(m,n) for(auto i=(m);((s)>0 and i<(n)) or ((s)<0 and i>(n));i+=(s))
#define REP(...) GET_MACRO(__VA_ARGS__, REP4, REP3, REP2)(__VA_ARGS__)

template<class T> void _read(T &x) {cin >> x;}
void _read(size_t &x) {scanf("%zu", &x);}
void _read(int &x) {scanf("%d", &x);}
void _read(LL &x) {scanf("%lld", &x);}
void _read(ULL &x) {scanf("%llu", &x);}
void _read(double &x) {scanf("%lf", &x);}
void _read(char &x) {scanf(" %c", &x);}
void _read(char *x) {scanf("%s", x);}
void read() {}
template<class T, class... U>
void read(T& head, U&... tail) {
    _read(head);
    read(tail...);
}

template<class T> void _print(const T &x) {cout << x;}
void _print(const size_t &x) {printf("%zu", x);}
void _print(const int &x) {printf("%d", x);}
void _print(const LL &x) {printf("%lld", x);}
void _print(const ULL &x) {printf("%llu", x);}
void _print(const double &x) {printf("%.16lf", x);}
void _print(const char &x) {putchar(x);}
void _print(const char *x) {printf("%s", x);}
void _print(const string &x) {printf("%s", x.c_str());}
template<class T> void _print(const vector<T> &x) {
    for(auto i = x.begin(); i != x.end(); _print(*i++)) {
        if (i != x.cbegin()) putchar(' ');
    }
}
void print() {putchar('\n');}
template<class T, class... U> void print(const T& head, const U&... tail) {
    _print(head);
    if(sizeof...(tail)) putchar(' ');
    print(tail...);
}


#define LLINF 0x3f3f3f3f3f3f3f3f
#define INF 0x3f3f3f3f

const int MOD = 1000000007;

//}}}
#define MAX_N 55

struct edge {
    int to, cap, rev;
};

vector<edge> G[MAX_N];
int level[MAX_N];
int iter[MAX_N];

void add_edge(int from, int to, int cap) {
    int i = G[from].size();
    int j = G[to].size();
    G[from].push_back((edge){to, cap, j});
    G[to].push_back((edge){from, 0, i});
}

void bfs(int s) {
    memset(level, -1, sizeof(level));
    queue<int> que;
    level[s] = 0;
    que.push(s);
    while(!que.empty()) {
        int v = que.front();
        que.pop();
        for(int i = 0; i < int(G[v].size()); i++) {
            edge &e = G[v][i];
            if(e.cap > 0 and level[e.to] < 0) {
                level[e.to] = level[v] + 1;
                que.push(e.to);
            }
        }
    }
}

int dfs(int v, int t, int f) {
    if(v == t) {
        return f;
    }
    for(int &i = iter[v]; i < int(G[v].size()); i++) {
        edge &e = G[v][i];
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

int max_flow(int s, int t) {
    int flow = 0;
    while(true) {
        bfs(s);
        if(level[t] < 0) {
            return flow;
        }
        memset(iter, 0, sizeof(iter));
        int f = dfs(s, t, INF);
        while(f > 0) {
            flow += f;
            f = dfs(s, t, INF);
        }
    }
}

void solve() {
    REP(i, MAX_N) {
        G[i].clear();
    }

    int N, H;
    read(N, H);

    vector<tuple<int, int, int, int>> L;
    REP(i, N) {
        int X, A, B;
        read(X, A, B);
        L.push_back({X, A, B, i});
        if(A == 0) {
            add_edge(N, i, INF);
        }
        if(B == H) {
            add_edge(i, N + 1, INF);
        }
    }
    sort(L.begin(), L.end());

    vector<TI3> cur;
    vector<TI3> tmp;
    REP(l, L) {
        int X, A, B, ID;
        tie(X, A, B, ID) = *l;

        REP(ii, cur) {
            int a, b, id;
            tie(a, b, id) = *ii;

            if(a <= A and B <= b) {
                if(a != A) {
                    tmp.push_back({a, A, id});
                }
                if(A != B) {
                    tmp.push_back({A, B, ID});
                }
                if(B != b) {
                    tmp.push_back({B, b, id});
                }
                int cap = B - A;
                add_edge(id, ID, cap);
                add_edge(ID, id, cap);
                A = -1;
                B = -1;

            } else if(a <= A and A <= b and b <= B) {
                if(a != A) {
                    tmp.push_back({a, A, id});
                }
                if(A != b) {
                    tmp.push_back({A, b, ID});
                }
                int cap = b - A;
                add_edge(id, ID, cap);
                add_edge(ID, id, cap);
                A = b;

            } else if(A <= a and a <= B and B <= b) {
                if(A != B) {
                    tmp.push_back({A, B, ID});
                }
                if(B != b) {
                    tmp.push_back({B, b, id});
                }
                int cap = B - a;
                add_edge(id, ID, cap);
                add_edge(ID, id, cap);
                A = -1;
                B = -1;

            } else if(A <= a and b <= B) {
                if(A != b) {
                    tmp.push_back({A, b, ID});
                }
                int cap = b - a;
                add_edge(id, ID, cap);
                add_edge(ID, id, cap);
                A = b;

            } else {
                tmp.push_back(*ii);
            }
        }
        if(A != B) {
            tmp.push_back({A, B, ID});
        }
        sort(tmp.begin(), tmp.end());
        swap(cur, tmp);
        tmp.clear();
    }
    int ans = max_flow(N, N + 1);

    if(ans >= INF) {
        print(-1);
    } else {
        print(ans);
    }
}

int main() {
    int T;
    scanf("%d", &T);
    for(int i = 0; i < T; i++) {
        printf("Case #%d: ", i+1);
        solve();
    }

    return 0;
}
