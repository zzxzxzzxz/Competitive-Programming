#include <bits/stdc++.h>
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

#define MAX_N 1000000005
#define MAX_SQRT_N 31624

bool notp[MAX_SQRT_N];
vector<int> prime;

void genprime() {
    int cur = 2;
    prime.PB(2);
    notp[0] = true;
    notp[1] = true;
    while(cur < MAX_SQRT_N) {
        REP(i, cur+cur, MAX_SQRT_N, cur) {
            notp[i] = true;
        }
        cur++;
        while(notp[cur] and cur < MAX_SQRT_N) {
            cur++;
        }
        if(cur == MAX_SQRT_N) {
            break;
        }
        prime.PB(cur);
    }
}


int main()
{
    genprime();
    REP(i, prime.size()) {
        PIS(prime[i]);
    }
    PN();
    return 0;
}
