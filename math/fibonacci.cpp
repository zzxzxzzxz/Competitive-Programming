#include <bits/stdc++.h>
using namespace std;

using LL = long long;
using MAT = array<array<LL, 2>, 2>;

const int MOD = 1000000007;
#define MAX_N 300005

MAT mul(MAT& A, MAT& B) {
    MAT C = {{{{0, 0}}, {{0, 0}}}};
    for(int i = 0; i < 2; i++) {
        for(int j = 0; j < 2; j++) {
            for(int k = 0; k < 2; k++) {
                C[i][j] = (C[i][j] + A[i][k] * B[k][j]) % MOD;
            }
        }
    }
    return C;
}

long long fibonacci(LL a) {
    MAT T = {{{{1, 0}}, {{0, 1}}}};
    MAT F = {{{{1, 1}}, {{1, 0}}}};
    while(a) {
        if(a & 1) {
            T = mul(T, F);
        }
        F = mul(F, F);
        a >>= 1;
    }
    return T[0][0];
}

int main() {
    for(int i = 0; i < 15; i++) {
        printf("%lld ", fibonacci(i));
    }
    printf("\n");
    printf("%lld\n", fibonacci(1000000000));
    return 0;
}
