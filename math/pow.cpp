#include <bits/stdc++.h>
using namespace std;

const int MOD = 1000000007;
#define MAX_N 300005

long long mypow(long long x, long long p) {
    long long ret = 1;
    while(p) {
        if(p & 1) {
            ret = (ret * x) % MOD;
        }
        x = (x * x) % MOD;
        p >>= 1;
    }
    return ret;
}

int main()
{
    int a;
    a = 5231423;
    printf("%lld\n", a * mypow(a, MOD - 2) % MOD);
    a = 1;
    printf("%lld\n", a * mypow(a, MOD - 2) % MOD);
    a = 10000009;
    printf("%lld\n", a * mypow(a, MOD - 2) % MOD);
    return 0;
}
