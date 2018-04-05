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
    vector<int> v = {1, 2, 3, 4, 5};
    n = v.size();
    for(int i = 1; i <= n; ++i) {
        bit[i] = v[i - 1];
    }
    build();

    for(int i = 1; i <= n; ++i) {
        printf("%d%c", sum(i), " \n"[i == n]);
    }

    vector<pair<int, int>> M = {{1, 2}, {4, 5}, {3, -1}};
    for(auto& m: M) {
        int idx, value;
        tie(idx, value) = m;
        add(idx, value);
        printf("%d %d\n", idx, value);
        for(int j = 1; j <= n; ++j) {
            printf("%d%c", sum(j), " \n"[j == n]);
        }
    }
    return 0;
}
