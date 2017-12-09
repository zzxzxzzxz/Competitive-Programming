#include <bits/stdc++.h>
using namespace std;

#define GET_MACRO(_1,_2,_3,_4,NAME,...) NAME
#define REP2(i,n) for(int i=0;i<(int)(n);i++)
#define REP3(i,m,n) for(int i=m;i<(int)(n);i++)
#define REP4(i,m,n,s) for(int i=m;(s>0 and i<(int)(n)) or (i>(int)(n));i+=s)
#define REP(...) GET_MACRO(__VA_ARGS__, REP4, REP3, REP2)(__VA_ARGS__)
#define REPIT(i,c) for(__typeof((c).begin()) i=(c).begin();i!=(c).end();i++)
#define PIS(x) printf("%d ",x)
#define PRINTIA(a,n) REP(i,n){printf("%d ", *((a)+i));} putchar('\n');
#define PN() putchar('\n')
#define MP make_pair
#define PB push_back

typedef pair<int,int> PII;
typedef long long LL;
typedef unsigned long long ULL;

void RI() {}
template<typename... T>
void RI( int& head, T&... tail ) {
    scanf("%d",&head);
    RI(tail...);
}
void PI() {putchar('\n');}
template<typename... T>
void PI(const int head, T... tail ) {
    printf("%d ", head);
    PI(tail...);
}

#define MAX_N 50000

int n;  // array size
int t[2 * MAX_N];

int operate(int a, int b) {return a + b;}
const int NIL = 0;
//const int& (*operate)(const int&, const int&) = min<int>;
//const int NIL = INT_MAX;


void build() {  // build the tree
    for (int i = n - 1; i > 0; --i) {
        t[i] = operate(t[i<<1], t[i<<1|1]);
    }
}


void modify(int p, int value) {  // set value at position p
    for (t[p += n] = value; p > 1; p >>= 1)
        t[p>>1] = operate(t[p], t[p^1]);
}


int query(int l, int r) {  // sum on interval [l, r)
    int resl = NIL, resr = NIL;
    for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
        if (l&1)
            resl = operate(resl, t[l++]);
        if (r&1)
            resr = operate(t[--r], resr);
    }
    return operate(resl, resr);
}


int main()
{
    fill(t, t+2*MAX_N, -100);
    RI(n);
    REP(i,n) {
        RI(t[i + n]);
    }
    PRINTIA(t + n, n);
    build();

    int q, a, b;
    while(scanf("%d%d%d", &q, &a, &b) != EOF) {
        if (q == 0)
            printf("q(%d, %d) = %d\n", a, b, query(a, b));
        else {
            printf("%d := %d\n", a, b);
            modify(a, b);
            PRINTIA(t + n, n);
        }
    }

    return 0;
}
