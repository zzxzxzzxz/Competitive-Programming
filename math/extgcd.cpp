#include <bits/stdc++.h>
using namespace std;

const int MOD = 1000000007;
#define MAX_N 300005

tuple<long long, long long, long long> extgcd(long long a, long long b) {
    if(b == 0) {
        return {a, 1, 0};
    }
    long long d, x, y;
    tie(d, y, x) = extgcd(b, a % b);
    y -= (a / b) * x;
    return {d, x, y};
}

void minnnzx(long long a, long long &x, long long b, long long &y, long long d) {
    long long r = (x % (b/d) + (b/d)) % (b/d);
    long long m = (x - r) / (b/d);
    x -= b/d * m;
    y += a/d * m;
}

int main()
{
    long long n, a, b;
    scanf("%lld%lld%lld", &n, &a, &b);
    long long d, x, y;
    tie(d, x, y) = extgcd(a, b);
    if(n % d) {
        printf("No\n");
        return 0;
    }
    x *= n / d;
    y *= n / d;
    minnnzx(a, x, b, y, d);
    printf("%lld %lld %lld %lld %lld\n", a, x, b, y, d);
    printf("%lld\n", a * x + b * y);
    return 0;
}
