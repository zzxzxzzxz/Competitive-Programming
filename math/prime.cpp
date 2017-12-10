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
#define MAX_N 1000000005
#define MAX_SQRT_N 31624

bool notprime[MAX_SQRT_N];
vector<int> prime;

void genprime() {
    notprime[0] = true;
    notprime[1] = true;
    int cur = 2;

    while(cur < MAX_SQRT_N) {
        prime.push_back(cur);
        for(int i = cur * 2; i < MAX_SQRT_N; i += cur) {
            notprime[i] = true;
        }
        cur++;
        while(cur < MAX_SQRT_N and notprime[cur]) {
            cur++;
        }
    }
}

int main()
{
    genprime();
    for(int i = 0; i < (int)prime.size(); i++) {
        printf("%d ", prime[i]);
    }
    printf("\n");
    return 0;
}
