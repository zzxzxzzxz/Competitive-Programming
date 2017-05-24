#include <bits/stdc++.h>
using namespace std;

#define REP(i,n) for(int i=0;i<(n);i++)
#define REPIT(i,c) for(__typeof((c).begin()) i=(c).begin();i!=(c).end();i++)
#define DRI(...) int __VA_ARGS__;RI(__VA_ARGS__)
#define PI(x) printf("%d\n",x)
#define PIS(x) printf("%d ",x)
#define PRINTIA(a,n) REP(i,n){PIS(*((a)+i));} putchar('\n');
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

#define MAX_N 50000

int bit[MAX_N + 1], n;

int sum(int i) {
    int s = 0;
    while (i > 0) {
        s += bit[i];
        i -= i & -i;
    }
    return s;
}

void add(int i, int x) {
    i += 1;
    while (i <= n) {
        bit[i] += x;
        i += i & -i;
    }
}

int main()
{
    int i, x;
    RI(n);
    vector<int> arr(n, 0);
    while (scanf("%d%d", &i, &x) > 0) {
        printf("%d %d\n", i, x);
        arr[i] += x;
        add(i, x);
        REP(j, n) {
            printf("%d ", arr[j]);
        }
        printf("\n");
        for(int j = 1; j < n+1; j++) {
            printf("%d ", sum(j));
        }
        printf("\n");
    }

    return 0;
}
