#include <bits/stdc++.h>
using namespace std;

template<typename T> struct TD;

using LL = long long;

int __lg(int n) { return 31 - __builtin_clz(n); }
int __lg(LL n) { return 63 - __builtin_clzll(n); }

int main() {
    cout << __lg(5) << endl;
    cout << __lg(5LL) << endl;
    return 0;
}
