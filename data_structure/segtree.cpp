#include <bits/stdc++.h>
using namespace std;

const int MOD = 1000000007;
#define MAX_N (1 << 20)

using DTYPE = int;
DTYPE dat[2 * MAX_N];

struct SegTree {
    int N;
    DTYPE zero = INT_MAX;  //identity of (DTYPE, func)
    DTYPE func(const DTYPE a, const DTYPE b) {
        return min(a, b);
    }

    SegTree(int n_) {
        N = 1;
        while(N < n_) {
            N <<= 1;
        }
        fill(dat, dat + 2 * N, zero);
    }

    void build() {
        for(int k = N - 1; k >= 0; k--) {
            dat[k] = func(dat[k * 2], dat[k * 2 + 1]);
        }
    }

    void update(int k, DTYPE a) {
        k += N;
        dat[k] = a;
        while(k > 1) {
            k >>= 1;
            dat[k] = func(dat[k * 2], dat[k * 2 + 1]);
        }
    }

    DTYPE query(int a, int b, int k = 1, int l = 0, int r = -1) {
        if(r < 0) {
            r = N;
        }
        if(r <= a or b <= l) {
            return zero;
        }
        if(a <= l and r <= b) {
            return dat[k];
        }
        int mid = l + (r - l) / 2;
        DTYPE vl = query(a, b, k * 2, l, mid);
        DTYPE vr = query(a, b, k * 2 + 1, mid, r);
        return func(vl, vr);
    }
};

int main()
{
    vector<int> v = {2, 3, 5, 1, 5, 6, 2};
    int n = v.size();
    SegTree t(n);
    for(int i = 0; i < int(v.size()); i++) {
        dat[i + t.N] = v[i];
    }
    t.build();
    cout << t.query(0, 3) << endl;
    cout << t.query(1, 3) << endl;
    cout << t.query(0, 4) << endl;
    t.update(3, 6);
    cout << t.query(0, 4) << endl;
    return 0;
}
