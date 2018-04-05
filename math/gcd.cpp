#include <bits/stdc++.h>
using namespace std;

const int MOD = 1000000007;
#define MAX_N 300005

int gcd(int a, int b) {
    while(b) {
        a = a % b;
        swap(a, b);
    }
    return a;
}

int main()
{
    int a, b;
    scanf("%d%d", &a, &b);
    printf("%d\n", gcd(a, b));
    return 0;
}
