#include <bits/stdc++.h>
using namespace std;

const int MOD = 1000000007;
#define MAX_N 300005

int bit[MAX_N + 1], n;

void build() {
    for(int i = 1; i <= n; i++) {
        int j = i + (i & -i);
        if(j <= n) {
            bit[j] += bit[i];
        }
    }
}


int sum(int i) {
    int s = 0;
    while (i > 0) {
        s += bit[i];
        i -= i & -i;
    }
    return s;
}


void add(int i, int x) {
    while (i <= n) {
        bit[i] += x;
        i += i & -i;
    }
}


int main()
{
/*
    5
    1 2 3 4 5
    3
    1 2
    4 5
    3 -1
*/
    scanf("%d", &n);
    for(int i = 1; i <= n; ++i) {
        scanf("%d", &bit[i]);
    }
    build();
    for(int i = 1; i <= n; ++i) {
        printf("%d%c", sum(i), " \n"[i == n]);
    }

    int m;
    scanf("%d", &m);
    for(int i = 0; i < m; ++i) {
        int idx, value;
        scanf("%d%d", &idx, &value);
        add(idx, value);
        printf("%d %d\n", idx, value);
        for(int j = 1; j <= n; ++j) {
            printf("%d%c", sum(j), " \n"[j == n]);
        }
    }
    return 0;
}
