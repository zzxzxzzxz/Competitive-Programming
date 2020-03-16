#include <bits/stdc++.h>
using namespace std;

using Data = int;
vector<Data> dat;

const Data zero_c = INT_MAX;
Data modify(const Data& val1, const Data& val2) {
    ignore = val1; return val2;
}
Data combine(const Data& val1, const Data& val2) {
    return min(val1, val2);
}

struct SegTree {//{{{
    int N;
    SegTree(int n_, Data *ptr = nullptr) {
        N = 1;
        while(N < n_) N <<= 1;
        dat.assign(N * 2, zero_c);

        if(ptr != NULL) {
            for(int i = 0; i < n_; i++) dat[i + N] = ptr[i];
            for(int k = N - 1; k >= 0; k--) {
                dat[k] = combine(dat[k * 2], dat[k * 2 + 1]);
            }
        }
    }

    void update(int a, const Data& val, int l = 0, int r = -1, int k = 1) {
        r = (r < 0)? N : r;

        if(r <= a or a < l) {
            return;
        }
        if(l == r - 1) {
            dat[k] = modify(dat[k], val);
            return;
        }
        int mid = l + (r - l) / 2;
        update(a, val, l, mid, k * 2);
        update(a, val, mid, r, k * 2 + 1);
        dat[k] = combine(dat[k * 2], dat[k * 2 + 1]);
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
        Data vl = query(a, b, l, mid, k * 2);
        Data vr = query(a, b, mid, r, k * 2 + 1);
        return combine(vl, vr);
    }
};//}}}

int main() {
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
