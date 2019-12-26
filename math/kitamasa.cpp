#include<bits/stdc++.h>
using namespace std;

using LL = long long;

int m = 4;
vector<LL> x = {0, 1, 1, 1};
vector<LL> c = {1, 1, 2, 1};

void solve_n(int n) {
    auto dp = x;
    for(int j = 4; j <= n; ++j) {
        LL tmp = 0;
        for(int k = 0; k < 4; ++k) {
            tmp += c[k] * dp[(j - k + 4) % 4];
        }
        dp[j % 4] = tmp;
    }
    cout << dp[n % 4] << endl;
}

void mod(vector<LL>& a) {
    //x^4 = x^3 + x^2 + 2x^1 + 1
    int d = int(a.size()) - 1;
    for(int i = d; i >= m; --i) {
        for(int j = 0; j < m; ++j) {
            a[i - m + j] += c[j] * a[i];
        }
        a.pop_back();
    }
}

void mul(vector<LL>& a, vector<LL>& b) {
    vector<LL> ab(m * 2, 0);
    for(int i = 0; i < m; ++i) {
        for(int j = 0; j < m; ++j) {
            ab[i + j] += a[i] * b[j];
        }
    }
    mod(ab);
    a = ab;
}


void solve_logn(int n) {
    // x^n mod (x^4 = x^3 + x^2 + 2x^1 + 1)
    vector<LL> p = {1, 0, 0, 0};
    vector<LL> t = {0, 1, 0, 0};
    while(n > 0) {
        if(n & 1) {
            mul(p, t);
        }
        mul(t, t);
        n >>= 1;
    }
    LL ans = 0;
    for(int i = 0; i < m; ++i) {
        ans += p[i] * x[i];
    }
    cout << ans << endl;
}

/*
 *  solve linear recurrence in O(m^2 log(n)) time
 *  Example(m = 2):
 *  a_n = a_n-1 + 2 * a_n-2
 *
 *  a5 =    1 * (a5 - a4 - 2 * a3)
 *       +  1 * (a4 - a3 - 2 * a2)
 *       +  3 * (a3 - a2 - 2 * a1)
 *       +  5 * (a2 - a1 - 2 * a0)
 *       + (11 * a1 + 10 * a0)
 *
 *  => x^5 mod (x^2 - x - 2) = 11x + 10
 *
 *  find a12 (a0 = 2, a1 = 3)
 *  x = x
 *  x^2 = x + 2
 *  x^4 = (x + 2)^2 = 5x + 6
 *  x^8 = (5x + 6)^2 = 85x + 86
 *
 *  x^12 = x^4 * x^8 = 1365x + 1366
 *  a12 = 1365 * a1 + 1366 * a2 = 6827
 */

int main() {
    int n = 60;
    solve_n(n);
    solve_logn(n);
    return 0;
}
