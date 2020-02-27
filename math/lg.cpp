#include <bits/stdc++.h>
using namespace std;

template<typename T> struct TD;

using LL = long long;

int lg(int n) { return 31 - __builtin_clz(n); }
int lg(LL n) { return 63 - __builtin_clzll(n); }

int main() {
    cout << lg(5) << endl;
    cout << lg(5LL) << endl;
    return 0;
}
