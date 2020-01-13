#include <bits/stdc++.h>
using namespace std;

#define IGNORE(x) static_assert(is_same<decltype(x), decltype(x)>::value);

const int MOD = 1000000007;
#define MAX_N (1 << 20)

using DTYPE = int;
DTYPE dat[2 * MAX_N];
DTYPE lazy[2 * MAX_N];

//const DTYPE zero_m = INT_MIN, zero_c = 0;
//const DTYPE zero_m = 0, zero_c = 0;
const DTYPE zero_m = 0, zero_c = INT_MAX;

DTYPE modify(const DTYPE& val1, const DTYPE& val2, int width = 1) {
    //IGNORE(val1); return val2 * width;
    //return val1 + val2 * width;
    IGNORE(width); return val1 + val2;
}
DTYPE combine(const DTYPE& val1, const DTYPE& val2) {
    //return val1 + val2;
    //return val1 + val2;
    return min(val1, val2);
}

struct SegTree {
    int N;
    SegTree(int n_, DTYPE *a = NULL) {
        N = 1;
        while(N < n_) {
            N <<= 1;
        }
        fill(dat, dat + 2 * N, zero_c);
        fill(lazy, lazy + 2 * N, zero_m);

        if(a != NULL) {
            for(int i = 0; i < n_; i++) dat[i + N] = a[i];
            for(int k = N - 1; k >= 0; k--) {
                dat[k] = combine(dat[k << 1], dat[k << 1 | 1]);
            }
        }
    }

    void pull(int k, int l, int r) {
        int lc = (k << 1), rc = (k << 1) | 1;
        dat[k] = combine(
            modify(dat[lc], lazy[lc], (r - l) / 2),
            modify(dat[rc], lazy[rc], (r - l) / 2)
        );
    }

    void push(int k, int l, int r) {
        int lc = (k << 1), rc = (k << 1) | 1;
        if(lazy[k] != zero_m) {
            dat[k] = modify(dat[k], lazy[k], r - l);
            if(l != r - 1) {
                lazy[lc] = modify(lazy[lc], lazy[k]);
                lazy[rc] = modify(lazy[rc], lazy[k]);
            }
            lazy[k] = zero_m;
        }
    }

    void update(int a, const DTYPE& val, int l = 0, int r = -1, int k = 1) {
        r = (r < 0)? N : r;

        if(r <= a or a < l) {
            return;
        }
        if(l == r - 1) {
            dat[k] = modify(dat[k], val);
            return;
        }
        int mid = l + (r - l) / 2;
        push(k, l, r);
        update(a, val, l, mid, k << 1);
        update(a, val, mid, r, k << 1 | 1);
        pull(k, l, r);
    }

    void update_range(int a, int b, const DTYPE& val, int l = 0, int r = -1, int k = 1) {
        r = (r < 0)? N : r;

        if(r <= a or b <= l) {
            return;
        }
        if(a <= l and r <= b) {
            lazy[k] = modify(lazy[k], val);
            push(k, l, r);
            return;
        }

        int mid = l + (r - l) / 2;
        push(k, l, r);
        update_range(a, b, val, l, mid, k << 1);
        update_range(a, b, val, mid, r, k << 1 | 1);
        pull(k, l, r);
    }

    DTYPE query(int a, int b, int l = 0, int r = -1, int k = 1) {
        r = (r < 0)? N : r;

        if(r <= a or b <= l) {
            return zero_c;
        }
        push(k, l, r);

        if(a <= l and r <= b) {
            return dat[k];
        }
        int mid = l + (r - l) / 2;
        DTYPE vl = query(a, b, l, mid, k << 1);
        DTYPE vr = query(a, b, mid, r, k << 1 | 1);
        return combine(vl, vr);
    }
};

int main()
{
    vector<int> v = {11, 15, 12, 13, 5, 6, 2, 8};
    int n = v.size();
    SegTree t(n, &v[0]);

    for(auto i: v) printf("%2d ", i); printf("\n\n");

    cout << "(0, 3): " << t.query(0, 3) << endl;
    cout << "(1, 3): " << t.query(1, 3) << endl;
    cout << "(0, 5): " << t.query(0, 5) << endl;

    cout << "\nadd 10 to (4, 8)" << endl;
    t.update_range(4, 8, 10);
    for(int i = 4; i < 8; ++i) v[i] = modify(v[i], 10);
    for(auto i: v) printf("%2d ", i); printf("\n");

    cout << "\nadd -10 to (0, 6)" << endl;
    t.update_range(0, 6, -10);
    for(int i = 0; i < 6; ++i) v[i] = modify(v[i], -10);
    for(auto i: v) printf("%2d ", i); printf("\n\n");

    cout << "(4, 8): " << t.query(4, 8) << endl;
    cout << "(3, 6): " << t.query(3, 6) << endl;
    cout << "(0, 4): " << t.query(0, 4) << endl;

    cout << "\nadd 10 to idx=0" << endl;
    t.update(0, 10);
    v[0] = modify(v[0], 10);
    for(auto i: v) printf("%2d ", i); printf("\n\n");

    cout << "(0, 4): " << t.query(0, 4) << endl;
    return 0;
}
