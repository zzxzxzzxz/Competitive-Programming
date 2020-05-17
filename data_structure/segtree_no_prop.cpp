#include <bits/stdc++.h>
using namespace std;

using DataType = int;

//const DataType zero_m = 0, zero_c = INT_MAX;
const DataType zero_m = 0, zero_c = 0;

DataType modify(const DataType& val1, const DataType& val2, int width = 1) {
    //DataType res = val1 + val2; ignore = width;
    DataType res = val1 + val2 * width;
    return res;
}
DataType combine(const DataType& val1, const DataType& val2) {
    //DataType res = min(val1, val2);
    DataType res = val1 + val2;
    return res;
}
struct Node {/*{{{*/
    DataType val, lazy;
    void add(DataType& x, int width) {
        val = modify(val, x, width);
        lazy = modify(lazy, x);
    }
    void pull(Node& a, Node& b, int width) {
        val = modify(combine(a.val, b.val), lazy, width);
    }
};/*}}}*/
struct SegTree {/*{{{*/
    int lg(int n) { return 31 - __builtin_clz(n); }

    int base;
    vector<Node> dat;

    SegTree(int n, DataType* ptr = nullptr): base(1) {
        while(base < n) base <<= 1;
        dat.resize(base * 2, {zero_c, zero_m});

        if(ptr != NULL) {
            for(int i = 0; i < n; i++) dat[i + base].val = ptr[i];
            for(int k = base - 1; k > 0; k--) {
                dat[k].pull(dat[k * 2], dat[k * 2 + 1], 1 << (lg(base) - lg(k)));
            }
        }
    }

    const int QUERY = 0, UPDATE = 1;
    void rec(int a, int b, DataType& val, int qtype, int l, int r, int k) {
        if(b <= l or r <= a) {
            return;
        } else if(a <= l and r <= b) {
            if(qtype == QUERY) {
                val = combine(val, dat[k].val);
            } else {
                dat[k].add(val, r - l);
            }
            return;
        }
        int mid = l + (r - l) / 2;
        rec(a, b, val, qtype, l, mid, k << 1);
        rec(a, b, val, qtype, mid, r, k << 1 | 1);

        if(qtype == QUERY) {
            val = modify(val, dat[k].lazy, min(r, b) - max(l, a));
        }
        dat[k].pull(dat[k << 1], dat[k << 1 | 1], r - l);
    }

    void update(int a, DataType val) {
        rec(a, a + 1, val, UPDATE, 0, base, 1);
    }
    void update(int a, int b, DataType val) {
        rec(a, b, val, UPDATE, 0, base, 1);
    }

    DataType query(int a, int b) {
        DataType val = zero_c;
        rec(a, b, val, QUERY, 0, base, 1);
        return val;
    }
};/*}}}*/

int main() {
    vector<int> v = {11, 15, 12, 13, 5, 6, 2, 8};
    int n = v.size();
    SegTree t(n, &v[0]);

    for(auto i: v) printf("%2d ", i); printf("\n\n");

    cout << "(0, 3): " << t.query(0, 3) << endl;
    cout << "(1, 3): " << t.query(1, 3) << endl;
    cout << "(0, 5): " << t.query(0, 5) << endl;

    cout << "\nadd 10 to (4, 8)" << endl;
    t.update(4, 8, 10);
    for(int i = 4; i < 8; ++i) v[i] = modify(v[i], 10);
    for(auto i: v) printf("%2d ", i); printf("\n");

    cout << "\nadd -10 to (0, 6)" << endl;
    t.update(0, 6, -10);
    for(int i = 0; i < 6; ++i) v[i] = modify(v[i], -10);
    for(auto i: v) printf("%2d ", i); printf("\n\n");

    cout << "(4, 8): " << t.query(4, 8) << endl;
    cout << "(3, 6): " << t.query(3, 6) << endl;
    cout << "(0, 4): " << t.query(0, 4) << endl;
    return 0;
}
