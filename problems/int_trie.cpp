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
template<class T> constexpr inline T end(const T& x) {return x;}

#define PN() putchar('\n')
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

template<class T> void _read(T &x) {cin>>x;}
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
void _print(const double &x) {printf("%.16lf",x);}
void _print(const char &x) {putchar(x);}
void _print(const char *x) {printf("%s",x);}
template<class T> void _print(const vector<T> &x) {
    for(auto i = x.begin(); i != x.end(); _print(*i++)) {
        if (i != x.cbegin()) putchar(' ');
    }
}
void print() {}
template<class T, class... U> void print(const T& head, const U&... tail) {
    _print(head);
    putchar(sizeof...(tail) ? ' ' : '\n');
    print(tail...);
}

#define LLINF 0x3f3f3f3f3f3f3f3f
#define INF 0x3f3f3f3f

const int MOD = 1000000007;
#define MAX_N 100005

struct TrieNode {
    TrieNode *next[2];
    int m;

    TrieNode() {
        memset(next, 0, sizeof(next));
        m = INF;
    }
};

struct Trie {
    TrieNode *root;

    Trie() {
        root = new TrieNode();
    }

    void insert(const int num)
    {
        TrieNode *p = root;
        REP(k, 17, -1, -1) {
            bool b = (num >> k) & 1;
            if(p->next[b] == NULL) {
                p->next[b] = new TrieNode();
            }
            p = p->next[b];
            p->m = min(p->m, num);
        }
    }

    int search(const int num, int s)
    {
        int cur = 0;
        TrieNode *p = root;
        REP(k, 17, -1, -1) {
            bool b = (num >> k) & 1;
            if(p->next[!b] and p->next[!b]->m <= s) {
                p = p->next[!b];
                cur |= (int(!b) << k);
            } else if(p->next[b] and p->next[b]->m <= s){
                p = p->next[b];
                cur |= (int(b) << k);
            } else {
                return -1;
            }
        }
        return cur;
    }
};

unordered_set<int> S;

int main()
{
    const int MAGIC = 100;
    Trie trie[MAGIC + 1];
    int q;
    read(q);
    REP(i, q) {
        int t;
        read(t);
        if(t == 1) {
            int u;
            read(u);
            S.insert(u);
            REP(j, 1, MAGIC + 1) {
                if(u % j == 0) {
                    trie[j].insert(u);
                }
            }
        } else {
            int x, k, s;
            read(x, k, s);
            if(x % k != 0) {
                print(-1);
                continue;
            }
            if(k <= MAGIC) {
                int ans = trie[k].search(x, s - x);
                print(ans);
            } else {
                int M = -1, vM = -1;
                REP(v, k, 100001, k) {
                    if(x + v <= s and S.find(v) != S.end()) {
                        if((v ^ x) > M) {
                            vM = v;
                            M = v ^ x;
                        }
                    }
                }
                print(vM);
            }
        }
    }
    return 0;
}
