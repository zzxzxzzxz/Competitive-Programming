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
#define PRINTARR(a,b) for(int i=0;(a+i)!=(b);i++){cout << *(a+i) << " ";}PN();
#define MP make_pair
#define PB push_back
#define EB emplace_back
#define MT make_tuple

typedef pair<int, int> PII;
typedef tuple<int, int, int> T3I;
typedef long long LL;
typedef unsigned long long ULL;

void RI() {}
template<typename... T>
void RI( int& head, T&... tail ) {
    scanf("%d", &head);
    RI(tail...);
}
void RLL() {}
template<typename... T>
void RLL( LL& head, T&... tail ) {
    scanf("%lld", &head);
    RLL(tail...);
}
void print() {putchar('\n');}
template<typename T, typename... U>
void print(T head, U... tail) {
    cout << head << " ";
    print(tail...);
}

const int MOD = 1000000007;
#define MAX_N 200005

int n;  // array size
vector<int> t[2 * MAX_N];

vector<int> operate(vector<int>& a, vector<int>& b) {
    vector<int> c;
    auto ia = a.begin();
    auto ib = b.begin();
    while(ia != a.end() or ib != b.end()) {
        if(ia == a.end()) {
            c.PB(*ib);
            ib++;
        } else if(ib == b.end()) {
            c.PB(*ia);
            ia++;
        } else if(*ia < *ib) {
            c.PB(*ia);
            ia++;
        } else {
            c.PB(*ib);
            ib++;
        }
    }
    return move(c);
}
const vector<int> NIL = {};

void build() {  // build the tree
    for (int i = n - 1; i > 0; --i) {
        t[i] = operate(t[i<<1], t[i<<1|1]);
    }
}

int count(vector<int>& v, int q, int th) {
    int d;
    if(q == 0) {
        auto s = lower_bound(v.begin(), v.end(), th);
        d = s - v.begin();
    } else {
        auto s = upper_bound(v.begin(), v.end(), th);
        d = v.end() - s;
    }
    return d;
}

int query(int l, int r, int q, int th) {  // sum on interval [l, r)
    int resl = 0, resr = 0;
    for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
        if (l&1) {
            resl += count(t[l++], q, th);
        }
        if (r&1) {
            resr += count(t[--r], q, th);
        }
    }
    return resl + resr;
}

LL C2(int m) {
    return ((LL)m) * (m - 1) / 2;
}

int main()
{
    //CF 433 Div1C
    int q;
    RI(n, q);
    REP(i, n) {
        int p;
        RI(p);
        t[i + n].PB(p-1);
    }
    build();
    REP(i, q) {
        int l, d, r, u;
        RI(l, d, r, u);
        l--, d--, r--, u--;
        LL ans = C2(n);
        LL ll = C2(l);
        ans -= ll;
        LL rr = C2(n-r-1);
        ans -= rr;
        LL dd = C2(d);
        ans -= dd;
        LL uu = C2(n-u-1);
        ans -= uu;
        LL ld = C2(query(0, l, 0, d));
        ans += ld;
        LL lu = C2(query(0, l, 1, u));
        ans += lu;
        LL rd = C2(query(r+1, n, 0, d));
        ans += rd;
        LL ru = C2(query(r+1, n, 1, u));
        ans += ru;

        printf("%lld\n", ans);
    }
    return 0;
}
