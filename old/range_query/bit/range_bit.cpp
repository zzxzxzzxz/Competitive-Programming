#include <bits/stdc++.h>
using namespace std;

#define REP(i,n) for(int i=0;i<(n);i++)
#define REPIT(i,c) for(__typeof((c).begin()) i=(c).begin();i!=(c).end();i++)
#define DRI(...) int __VA_ARGS__;RI(__VA_ARGS__)
#define PIS(x) printf("%d ",x)
#define PRINTIA(a,n) REP(i,n){PIS(*((a)+i));} putchar('\n');
#define MP make_pair
#define PB push_back

typedef pair<int,int> PII;
typedef long long LL;
typedef unsigned long long ULL;

int RI() {return 0;}
template<typename... T>
int RI( int& head, T&... tail ) {
    int ret = scanf("%d",&head);
    return ret + RI(tail...);
}
void PI() {putchar('\n');}
template<typename... T>
void PI( int& head, T&... tail ) {
    printf("%d ", head);
    PI(tail...);
}

#define MAX_N 50000

int n;
struct linear {
    int a;
    int b;
};
linear bit[MAX_N + 1];

int sum(int i) {
    int _i = i;
    int a = 0, b = 0;
    while (i > 0) {
        a += bit[i].a;
        b += bit[i].b;
        i -= i & -i;
    }
    return a * _i + b;
}

void _add(int i, int x, int y) {
    i += 1;
    while (i <= n) {
        bit[i].a += x;
        bit[i].b += y;
        i += i & -i;
    }
}

void add(int l, int r, int x) {
    _add(l, x, -x*l);
    _add(r, -x, x*r);
}


int main()
{
    int l, r, x;
    RI(n);
    vector<int> arr(n, 0);
    while (RI(l, r, x) > 0) {
        PI(l, r, x);
        for(int i = l; i < r; i++)
            arr[i] += x;
        add(l, r, x);
        PRINTIA(&arr[0], n);

        for(int j = 1; j < n+1; j++) {
            PIS(sum(j));
        }
        printf("\n");
    }

    return 0;
}
