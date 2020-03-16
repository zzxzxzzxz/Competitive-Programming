#include <bits/stdc++.h>
using namespace std;

using LL = long long;
const int MOD = 1000000007;

LL mypow(LL x, LL p) {
    LL ret = 1;
    while(p > 0) {
        if(p & 1) {
            ret = (ret * x) % MOD;
        }
        x = (x * x) % MOD;
        p >>= 1;
    }
    return ret;
}

LL inv(LL x) {
    assert(x != 0);
    return mypow(x, MOD - 2);
}

int main() {
    int a;
    a = 5231423;
    printf("%lld\n", a * inv(a) % MOD);
    a = 1;
    printf("%lld\n", a * inv(a) % MOD);
    a = 10000009;
    printf("%lld\n", a * inv(a) % MOD);
    return 0;
}
