#include <bits/stdc++.h>
using namespace std;

int extgcd(int a, int b, int& x, int& y) {
    if(b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    int d = extgcd(b, a % b, y, x);
    y -= (a / b) * x;
    return d;
}

void min_nnzx(int a, int& x, int b, int& y, int d) {
    int r = (x % (b / d) + (b / d)) % (b / d);
    int m = (x - r) / (b / d);
    x -= b / d * m;
    y += a / d * m;
}

int main() {
    int n = 100, a = 13, b = 11;
    int x, y;
    int d = extgcd(a, b, x, y);
    if(n % d) {
        printf("No solutions\n");
        return 0;
    }
    x *= n / d;
    y *= n / d;
    min_nnzx(a, x, b, y, d);

    printf("gcd = %d\n", d);
    printf("%d x %d + %d x %d = %d\n",
            a, x, b, y, a * x + b * y);
    return 0;
}
