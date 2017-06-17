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
#define PN() putchar('\n')
#define MP make_pair
#define PB push_back
#define EB emplace_back

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

int main()
{
    int id = MyNodeId();
    int nnodes = NumberOfNodes();
    LL n = GetN();

    if(n < nnodes) {
        nnodes = n;
    }

    LL l = n * id / nnodes;
    LL r = n * (id+1) / nnodes;

    LL Mnode = 0, cur = 0;
    REP(i, l, r) {
        cur += GetValue(i);
        if(cur < 0) {
            cur = 0;
        }
        Mnode = max(Mnode, cur);
    }

    mput(0, Mnode);
    Send(0);

    if(id != 0)
        return 0;

    LL M[nnodes], Mall = 0;
    REP(i, nnodes) {
        int src = Receive(-1);
        mget(src, M[src]);
    }
    REP(i, nnodes) {
        Mall = max(Mall, M[src]);
    }

    printf("%lld\n", Mall);

    return 0;
}
