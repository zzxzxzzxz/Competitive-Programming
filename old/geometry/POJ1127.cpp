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

typedef pair<int,int> PII;
typedef long long LL;
typedef unsigned long long ULL;

void RI() {}
template<typename... T>
void RI( int& head, T&... tail ) {
    scanf("%d",&head);
    RI(tail...);
}
void print() {putchar('\n');}
template<typename T, typename... U>
void print(T head, U... tail) {
    cout << head << " ";
    print(tail...);
}

const int MOD = 1000000007;
#define MAX_N 100005

double EPS = 1e-10;
double dbl_add(double a, double b) {
    if(fabs(a + b) < EPS * (fabs(a) + fabs(b)))
        return 0;
    return a + b;
}

struct P {
    double x, y;
    P() {}
    P(double x, double y) : x(x), y(y) {}
    P operator + (P p) {
        return P(dbl_add(x, p.x), dbl_add(y, p.y));
    }
    P operator - (P p) {
        return P(dbl_add(x, -p.x), dbl_add(y, -p.y));
    }
    P operator * (double d) {
        return P(x * d, y * d);
    }
    double dot(P p) {
        return dbl_add(x * p.x, y * p.y);
    }
    double det(P p) {
        return dbl_add(x * p.y, -y * p.x);
    }
};

int main()
{

    return 0;
}
