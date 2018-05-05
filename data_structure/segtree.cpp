#include <bits/stdc++.h>
using namespace std;

const int MOD = 1000000007;
#define MAX_N (1 << 20)

int N;
int dat[2 * MAX_N];

struct SegTree {
    int zero = INT_MAX;
    int func(const int a, const int b) {
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

    void update(int k, int a) {
        k += N;
        dat[k] = a;
        while(k > 1) {
            k >>= 1;
            dat[k] = func(dat[k * 2], dat[k * 2 + 1]);
        }
    }

    int query(int a, int b, int k = 1, int l = 0, int r = N) {
        if(r <= a or b <= l) {
            return zero;
        }
        if(a <= l and r <= b) {
            return dat[k];
        }
        int mid = l + (r - l) / 2;
        int vl = query(a, b, k * 2, l, mid);
        int vr = query(a, b, k * 2 + 1, mid, r);
        return func(vl, vr);
    }
};

int main()
{
    vector<int> v = {2, 3, 5, 1, 5, 6, 2};
    int n = v.size();
    SegTree t(n);
    for(int i = 0; i < v.size(); i++) {
        dat[i + N] = v[i];
    }
    t.build();
    printf("%d\n", t.query(0, 3));
    printf("%d\n", t.query(1, 3));
    printf("%d\n", t.query(0, 4));
    t.update(3, 6);
    printf("%d\n", t.query(0, 4));
    return 0;
}
