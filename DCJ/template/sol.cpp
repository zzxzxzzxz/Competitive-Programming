#include <bits/stdc++.h>
#include "message.h"
using namespace std;

#define GET_MACRO(_1,_2,_3,_4,NAME,...) NAME
#define REP2(i,n) for(int i=0;i<(int)(n);i++)
#define REP3(i,m,n) for(int i=m;i<(int)(n);i++)
#define REP4(i,m,n,s) for(int i=m;(s>0 and i<(int)(n)) or (s<0 and i>(int)(n));i+=s)
#define REP(...) GET_MACRO(__VA_ARGS__, REP4, REP3, REP2)(__VA_ARGS__)
#define REPIT(i,c) for(__typeof((c).begin()) i=(c).begin();i!=(c).end();i++)
#define PIS(x) printf("%d ",x)
#define PRINTIA(a,n) REP(i,n){printf("%d ", *((a)+i));}putchar('\n');
#define PN() putchar('\n')
#define MP make_pair
#define PB push_back

typedef pair<int,int> PII;
typedef long long LL;
typedef unsigned long long ULL;

void mput( int tar, char val ) { PutChar(tar,val); }
void mput( int tar, int val ) { PutInt(tar,val); }
void mput( int tar, LL val ) { PutLL(tar,val); }

template<typename T, typename... U>
void mput( int tar, T head, U... tail ) {
    mput(tar,head);
    mput(tar,tail...);
}

void mget( int src, char &val ) { val=GetChar(src); }
void mget( int src, int &val ) { val=GetInt(src); }
void mget( int src, LL &val ) { val=GetLL(src); }

template<typename T, typename... U>
void mget( int src, T &head, U&... tail ) {
    mget(src,head);
    mget(src,tail...);
}

LL get_worst_l(LL l, LL r) {
    LL worst = 0, cur = 0;
    REP(i, l, r) {
        cur += GetTaste(i);
        worst = min(worst, cur);
    }
    return worst;
}

LL get_worst_r(LL l, LL r) {
    LL worst = 0, cur = 0;
    REP(i, r-1, l-1, -1) {
        cur += GetTaste(i);
        worst = min(worst, cur);
    }
    return worst;
}

LL get_worst(LL l, LL r) {
    LL worst = 0, cur = 0;
    REP(i, l, r) {
        cur += GetTaste(i);
        if(cur > 0) {
            cur = 0;
        }
        worst = min(worst, cur);
    }
    return worst;
}

LL get_sum(LL l, LL r) {
    LL cur = 0;
    REP(i, l, r) {
        cur += GetTaste(i);
    }
    return cur;
}

int main()
{
    int id = MyNodeId();
    int nnodes = NumberOfNodes();
    LL n = GetN();

    LL cur = 0, cur0 = 0, cur1;
    LL l = n * id / nnodes;
    LL r = n * (id+1) / nnodes;

    LL worst = get_worst(l, r);
    LL worstl = get_worst_l(l, r);
    LL worstr = get_worst_r(l, r);
    LL sum = get_sum(l, r);

    mput(0, worst, worstl, worstr, sum);
    Send(0);

    if(id != 0)
        return 0;

    LL nodew[nnodes], nodewl[nnodes], nodewr[nnodes], nodesum[nnodes];
    REP(i, nnodes) {
        int src = Receive(-1);
        mget(src, nodew[src], nodewl[src], nodewr[src], nodesum[src]);
    }

    LL m = 0;

    REP(i, nnodes) {
        m = min(m, nodew[i]);
    }
    REP(i, nnodes) {
        LL s = 0;
        REP(j, i+1, nnodes) {
            LL cur = nodewr[i] + s + nodewl[j];
            m = min(m, cur);
            s += nodesum[j];
        }
    }
    LL sum_all = 0;
    REP(i, nnodes) {
        sum_all += nodesum[i];
    }
    printf("%lld\n", sum_all - m);
    return 0;
}
