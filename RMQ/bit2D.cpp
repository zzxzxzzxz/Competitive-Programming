#include <bits/stdc++.h>
using namespace std;

const int MOD = 1000000007;
#define MAX_N 5005

int bit[MAX_N + 1][MAX_N + 1], n, m;

void build() {
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            int l = j + (j & -j);
            if(l <= m) {
                bit[i][l] += bit[i][j];
            }
        }
    }
    for(int i = 1; i <= n; i++) {
        int k = i + (i & -i);
        if(k <= n) {
            for(int j = 1; j <= m; j++) {
                bit[k][j] += bit[i][j];
            }
        }
    }
}


int sum(int i, int j) {
    int s = 0;
    while (i > 0) {
        int k = j;
        while(k > 0) {
            s += bit[i][k];
            k -= k & -k;
        }
        i -= i & -i;
    }
    return s;
}


void add(int i, int j, int x) {
    while (i <= n) {
        int k = j;
        while(k <= m) {
            bit[i][k] += x;
            k += k & -k;
        }
        i += i & -i;
    }
}

int main()
{
    /*
    4 4
    1 0 1 1
    1 0 1 0
    0 1 0 1
    1 0 0 1
    3
    1 1 -1
    2 3 1
    3 2 -1
    */

    scanf("%d%d", &n, &m);
    for(int i = 1; i <= n; ++i) {
        for(int j = 1; j <= m; ++j) {
            scanf("%d", &bit[i][j]);
        }
    }
    build();

    for(int i = 1; i <= n; ++i) {
        for(int j = 1; j <= m; ++j) {
            printf("%d%c", sum(i, j), " \n"[j == m]);
        }
    }
    putchar('\n');

    int q;
    scanf("%d", &q);
    for(int k = 0; k < q; ++k) {
        int row, col, value;
        scanf("%d%d%d", &row, &col, &value);
        add(row, col, value);
        printf("%d %d %d\n", row, col, value);
        for(int i = 1; i <= n; ++i) {
            for(int j = 1; j <= m; ++j) {
                printf("%d%c", sum(i, j), " \n"[j == m]);
            }
        }
        putchar('\n');
    }
    return 0;
}
