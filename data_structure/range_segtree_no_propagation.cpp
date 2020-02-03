#include <bits/stdc++.h>
using namespace std;

using Data = int;
vector<Data> dat, lazy;

//const Data zero_m = 0, zero_c = INT_MAX;
const Data zero_m = 0, zero_c = 0;

Data modify(const Data& val1, const Data& val2, int width = 1) {
    //ignore = width; return val1 + val2;
    return val1 + val2 * width;
}
Data combine(const Data& val1, const Data& val2) {
    //return min(val1, val2);
    return val1 + val2;
}

struct SegTree {
    int N;
    SegTree(int n_, Data *a = NULL) {
        N = 1;
        while(N < n_) {
            N <<= 1;
        }
        dat.assign(N * 2, zero_c);
        lazy.assign(N * 2, zero_m);

        if(a != NULL) {
            for(int i = 0; i < n_; i++) dat[i + N] = a[i];
            for(int k = N - 1; k >= 0; k--) {
                dat[k] = combine(dat[k << 1], dat[k << 1 | 1]);
            }
        }
    }

    void pull(int k, int l, int r) {
        int lc = (k << 1), rc = (k << 1) | 1;
        dat[k] = modify(combine(dat[lc], dat[rc]), lazy[k], r - l);
    }

    void update_range(int a, int b, const Data& val, int l = 0, int r = -1, int k = 1) {
        r = (r < 0)? N : r;

        if(r <= a or b <= l) {
            return;
        }
        if(a <= l and r <= b) {
            lazy[k] = modify(lazy[k], val);
            dat[k] = modify(dat[k], val, r - l);
            return;
        }

        int mid = l + (r - l) / 2;
        update_range(a, b, val, l, mid, k << 1);
        update_range(a, b, val, mid, r, k << 1 | 1);
        pull(k, l, r);
    }

    Data query(int a, int b, int l = 0, int r = -1, int k = 1) {
        r = (r < 0)? N : r;

        if(r <= a or b <= l) {
            return zero_c;
        }
        if(a <= l and r <= b) {
            return dat[k];
        }
        int mid = l + (r - l) / 2;
        Data vl = query(a, b, l, mid, k << 1);
        Data vr = query(a, b, mid, r, k << 1 | 1);
        Data ret = modify(combine(vl, vr), lazy[k], min(r, b) - max(l, a));
        return ret;
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
    return 0;
}
