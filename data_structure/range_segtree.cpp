#include <bits/stdc++.h>
using namespace std;

const int MOD = 1000000007;
#define MAX_N (1 << 20)

using DTYPE = int;
DTYPE dat[2 * MAX_N];
DTYPE lazy[2 * MAX_N];

void modify(DTYPE& val1, DTYPE val2, int width = 1) {
    //val1 = val2 * width;
    val1 += val2; width += 0;
}

struct SegTree {
    //const DTYPE zero_m = INT_MIN;
    //const DTYPE zero_c = 0;
    const DTYPE zero_m = 0;
    const DTYPE zero_c = INT_MAX;
    DTYPE combine(DTYPE val1, DTYPE val2) {
        //return val1 + val2;
        return min(val1, val2);
    }

    int N;
    SegTree(int n_, DTYPE *a = NULL) {
        N = 1;
        while(N < n_) {
            N <<= 1;
        }
        fill(dat, dat + 2 * N, zero_c);
        fill(lazy, lazy + 2 * N, zero_m);

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

    void push_down(DTYPE& val, int l, int r, int k) {
        if(val != zero_m) {
            modify(dat[k], val, r - l);
            if(l != r - 1) {
                modify(lazy[k * 2], val);
                modify(lazy[k * 2 + 1], val);
            }
            val = zero_m;
        }
    }

    void update(int a, DTYPE val, int l = 0, int r = -1, int k = 1) {
        r = (r < 0)? N : r;

        push_down(lazy[k], l, r, k);
        if(r <= a or a < l) {
            return;
        }
        if(l == r - 1) {
            push_down(val, l, r, k);
            return;
        }
        int mid = l + (r - l) / 2;
        update(a, val, l, mid, k * 2);
        update(a, val, mid, r, k * 2 + 1);
        dat[k] = combine(dat[k * 2], dat[k * 2 + 1]);
    }

    void update_range(int a, int b, DTYPE val, int l = 0, int r = -1, int k = 1) {
        r = (r < 0)? N : r;

        push_down(lazy[k], l, r, k);
        if(r <= a or b <= l) {
            return;
        }
        if(a <= l and r <= b) {
            push_down(val, l, r, k);
            return;
        }

        int mid = l + (r - l) / 2;
        update_range(a, b, val, l, mid, k * 2);
        update_range(a, b, val, mid, r, k * 2 + 1);
        dat[k] = combine(dat[k * 2], dat[k * 2 + 1]);
    }

    DTYPE query(int a, int b, int l = 0, int r = -1, int k = 1) {
        r = (r < 0)? N : r;

        if(r <= a or b <= l) {
            return zero_c;
        }
        push_down(lazy[k], l, r, k);

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
    cout << "(0, 5): " << t.query(0, 5) << endl;
    t.update_range(0, 4, 10);
    for(int i = 0; i < 4; ++i) modify(v[i], 10);
    for(auto i: v) cout << i << " "; cout << endl;
    cout << "(0, 5): " << t.query(0, 5) << endl;
    cout << "(0, 4): " << t.query(0, 4) << endl;
    cout << "(3, 6): " << t.query(3, 6) << endl;
    modify(v[2], 1); cout << "v[2] = 1" << endl;
    t.update(2, 1);
    for(auto i: v) cout << i << " "; cout << endl;
    cout << "(0, 5): " << t.query(0, 5) << endl;
    cout << "(0, 4): " << t.query(0, 4) << endl;
    return 0;
}
