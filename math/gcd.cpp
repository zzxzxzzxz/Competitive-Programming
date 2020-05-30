#include <bits/stdc++.h>
using namespace std;

template<class T>
T gcd(T a, T b) {
    while(b) {
        a = a % b;
        swap(a, b);
    }
    return a;
}

int main() {
    int a, b;
    scanf("%d%d", &a, &b);
    printf("%d\n", gcd(a, b));
    return 0;
}
