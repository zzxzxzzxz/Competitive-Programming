#include <bits/stdc++.h>
using namespace std;

const int MOD = 1000000007;
#define MAX_N (1 << 20)

using DTYPE = int;
DTYPE dat[2 * MAX_N];

struct SegTree {
    const DTYPE zero_c = INT_MAX;
    void modify(DTYPE& val1, DTYPE val2) {
        val1 = val2;
    }
    DTYPE combine(DTYPE val1, DTYPE val2) {
        return min(val1, val2);
    }

    int N;
    SegTree(int n_, DTYPE *a = NULL) {
        N = 1;
        while(N < n_) {
            N <<= 1;
        }
        fill(dat, dat + 2 * N, zero_c);

        if(a != NULL) {
            for(int i = 0; i < n_; i++) {
                dat[i + N] = a[i];
            }
            build();
        }
    }

    void build() {
        for(int k = N - 1; k >= 0; k--) {
            dat[k] = combine(dat[k * 2], dat[k * 2 + 1]);
        }
    }

    void update(int a, DTYPE val, int l = 0, int r = -1, int k = 1) {
        r = (r < 0)? N : r;

        if(r <= a or a < l) {
            return;
        }
        if(l == r - 1) {
            modify(dat[k], val);
            return;
        }
        int mid = l + (r - l) / 2;
        update(a, val, l, mid, k * 2);
        update(a, val, mid, r, k * 2 + 1);
        dat[k] = combine(dat[k * 2], dat[k * 2 + 1]);
    }

    DTYPE query(int a, int b, int l = 0, int r = -1, int k = 1) {
        r = (r < 0)? N : r;

        if(r <= a or b <= l) {
            return zero_c;
        }

        if(a <= l and r <= b) {
            return dat[k];
        }
        int mid = l + (r - l) / 2;
        DTYPE vl = query(a, b, l, mid, k * 2);
        DTYPE vr = query(a, b, mid, r, k * 2 + 1);
        return combine(vl, vr);
    }
};

int main()
{
    vector<int> v = {2, 3, 5, 1, 5, 6, 2};
    int n = v.size();
    SegTree t(n, &v[0]);

    for(auto i: v) cout << i << " "; cout << endl;
    cout << "(0, 3): " << t.query(0, 3) << endl;
    cout << "(1, 3): " << t.query(1, 3) << endl;
    cout << "(0, 4): " << t.query(0, 4) << endl;
    v[3] = 6; cout << "v[3] = 6" << endl;
    t.update(3, 6);
    for(auto i: v) cout << i << " "; cout << endl;
    cout << "(0, 4): " << t.query(0, 4) << endl;
    return 0;
}
