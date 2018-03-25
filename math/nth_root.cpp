#include <bits/stdc++.h>
using namespace std;
using ULL =  unsigned long long;

ULL mypow_ullmax(ULL x, int p) {
    ULL ret = 1;
    while(p) {
        if(p & 1) {
            if(ret > ULLONG_MAX / x) {
                return ULLONG_MAX;
            }
            ret = ret * x;
        }
        if(x > ULLONG_MAX / x) {
            x = ULLONG_MAX;
        } else {
            x = x * x;
        }
        p >>= 1;
    }
    return ret;
}

ULL nth_root(ULL n, int p) {
    ULL x = exp(log(n) / p);
    if(mypow_ullmax(x + 1, p) <= n) {
        return x + 1;
    }
    return x;
}

int main()
{
    ULL x = 1e18;
    printf("%llu\n", nth_root(x, 3));
    return 0;
}
