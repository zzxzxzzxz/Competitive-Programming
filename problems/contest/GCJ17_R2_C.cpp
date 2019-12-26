#pragma comment(linker, "/stack:200000000")
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

#include <bits/stdc++.h>
using namespace std;

#define GET_MACRO(_1,_2,_3,_4,NAME,...) NAME
#define REP2(i,n) for(int i=0;i<(int)(n);i++)
#define REP3(i,m,n) for(int i=m;i<(int)(n);i++)
#define REP4(i,m,n,s) for(int i=m;(s>0 and i<(int)(n)) or (s<0 and i>(int)(n));i+=s)
#define REP(...) GET_MACRO(__VA_ARGS__, REP4, REP3, REP2)(__VA_ARGS__)
#define REPIT(i,c) for(__typeof((c).begin()) i=(c).begin();i!=(c).end();i++)
#define PIS(x) printf("%d ",x)
#define PN() putchar('\n')
#define MP make_pair
#define PB push_back
#define EB emplace_back
#define MT make_tuple

using PII = pair<int, int>;
using TI3 = tuple<int, int, int>;
using LL = long long;
using ULL =  unsigned long long;
using MAT = array<array<LL, 2>, 2>;

template<class T> void _read( T &x ) { cin>>x; }
void _read(int &x) { scanf("%d", &x); }
void _read(LL &x) { scanf("%lld", &x); }
void _read(double &x) { scanf("%lf", &x); }
void _read(char &x) { scanf(" %c", &x); }
void _read(char *x) { scanf("%s", x); }
void read() {}
template<class T, class... U>
void read( T& head, U&... tail ) {
    _read(head);
    read(tail...);
}

template<class T> void _print( const T &x ) { cout << x; }
void _print( const int &x ) { printf("%d", x); }
void _print( const LL &x ) { printf("%lld", x); }
void _print( const double &x ) { printf("%.16lf",x); }
void _print( const char &x ) { putchar(x); }
void _print( const char *x ) { printf("%s",x); }
template<class T> void _print( const vector<T> &x ) { for (auto i = x.begin(); i != x.end(); _print(*i++)) if (i != x.cbegin()) putchar(' '); }
void print() {}
template<class T, class... U> void print( const T& head, const U&... tail ) {
    _print(head);
    putchar(sizeof...(tail) ? ' ' : '\n');
    print(tail...);
}

const int MOD = 1000000007;
#define MAX_N 55
#define MAX_V (MAX_N * MAX_N * 2 + 10)
vector<int> G[MAX_V];
vector<int> rG[MAX_V];
vector<int> vs;
bool used[MAX_V];
int cmp[MAX_V];
int offset = MAX_N * MAX_N;

void add_edge(int from, int to) {
    G[from].push_back(to);
    rG[to].push_back(from);
}

void dfs(int v) {
    used[v] = true;
    REPIT(ii, G[v]) {
        if(not used[*ii]) {
            dfs(*ii);
        }
    }
    vs.push_back(v);
}

void rdfs(int v, int k) {
    used[v] = true;
    cmp[v] = k;
    REPIT(ii, rG[v]) {
        if(not used[*ii]) {
            rdfs(*ii, k);
        }
    }
}

void ssc() {
    memset(used, 0, sizeof(used));
    vs.clear();
    REP(i, MAX_V) {
        if(not used[i]) {
            dfs(i);
        }
    }
    memset(used, 0, sizeof(used));
    int k = 0;
    REP(i, MAX_V-1, -1, -1) {
        if(not used[vs[i]]) {
            rdfs(vs[i], k++);
        }
    }
}

PII cond[MAX_N * MAX_N][4];
char room[MAX_N][MAX_N];
int R, C;

bool OK(int r, int c) {
    if(r < 0 or c < 0 or r >= R or c >= C or room[r][c] == '#') {
        return false;
    }
    return true;
}

PII turn(int r, int c, int dr, int dc) {
    if(room[r][c] == '/') {
        swap(dr, dc);
        dr *= -1;
        dc *= -1;
    } else if(room[r][c] == '\\') {
        swap(dr, dc);
    }
    return {dr, dc};
}

void go(int r, int c, int dr, int dc, int mode) {
    int r0 = r, c0 = c;
    while(OK(r + dr, c + dc)) {
        r += dr;
        c += dc;

        int k = (dr == 0)? max(dc, 0) : 2 + max(dr, 0);
        if(room[r][c] == '|' or room[r][c] == '-') {
            cond[r*C + c][k] = {1 + r0*C + c0, mode};
            break;
        } else if(room[r][c] == '.') {
            assert(cond[r*C + c][k].first == 0);
            if(cond[r*C + c][k^1].first > 0) {
                cond[r*C + c][k^1] = {0, 0};
            } else {
                cond[r*C + c][k] = {1 + r0*C + c0, mode};
            }
        }
        tie(dr, dc) = turn(r, c, dr, dc);
    }
}

void solve() {
    REP(i, MAX_V) {
        G[i].clear();
        rG[i].clear();
    }
    memset(cond, 0, sizeof(cond));
    read(R, C);
    REP(r, R) {
        read(room[r]);
    }

    REP(r, R) {
        REP(c, C) {
            if(room[r][c] == '-' or room[r][c] == '|') {
                go(r, c, 0, 1, 0);
                go(r, c, 0, -1, 0);
                go(r, c, 1, 0, 1);
                go(r, c, -1, 0, 1);
            }
        }
    }

    REP(r, R) {
        REP(c, C) {
            vector<PII> conds;
            REP(k, 4) {
                if(cond[r*C + c][k].first > 0) {
                    conds.push_back(cond[r*C + c][k]);
                }
            }
            if(room[r][c] == '|' or room[r][c] == '-') {
                REPIT(ii, conds) {
                    int v = ii->first;
                    int mode = ii->second;
                    add_edge(v + offset * mode, v + offset * (1-mode));
                }
            } else if(room[r][c] == '.') {
                if(conds.size() == 1) {
                    int v = conds[0].first;
                    int mode = conds[0].second;
                    add_edge(v + offset * (1-mode), v + offset * mode);
                } else if(conds.size() == 2) {
                    int v = conds[0].first, u = conds[1].first;
                    int modev = conds[0].second, modeu = conds[1].second;
                    add_edge(v + offset * (1-modev), u + offset * modeu);
                    add_edge(u + offset * (1-modeu), v + offset * modev);
                } else {
                    print("IMPOSSIBLE");
                    return;
                }
            }
        }
    }
    ssc();

    REP(i, 1, R * C + 1) {
        int r = (i - 1) / C;
        int c = (i - 1) % C;
        if(cmp[i] == cmp[i + offset]) {
            print("IMPOSSIBLE");
            return;
        }
        if(room[r][c] == '|' or room[r][c] == '-') {
            if(cmp[i] > cmp[i + offset]) {
                room[r][c] = '-';
            } else {
                room[r][c] = '|';
            }
        }
    }
    print("POSSIBLE");
    REP(r, R) {
        print(room[r]);
    }
}

int main()
{
    int T;
    scanf("%d", &T);
    for(int i = 0; i < T; i++) {
        printf("Case #%d: ", i+1);
        solve();
    }

    return 0;
}
