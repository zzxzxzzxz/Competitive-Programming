#include <bits/stdc++.h>
using namespace std;

struct SparseTable {//{{{
    vector<vector<int>> st;
    int __lg(int n) { return 31 - __builtin_clz(n); }

    SparseTable(const vector<int>& a) {
        int n = a.size();
        int logn = __lg(n);
        st.assign(logn + 1, vector<int>(n));

        for(int i = 0; i < n; ++i) {
            st[0][i] = a[i];
        }
        for(int k = 1; (1 << k) <= n; ++k) {
            for(int i = 0; i + (1 << k) <= n; ++i) {
                st[k][i] = max(st[k - 1][i], st[k - 1][i + (1 << (k - 1))]);
            }
        }
    }

    int get(int l, int r) {
        if(l >= r) {
            return 0;
        }
        int k = __lg(r - l);
        return max(st[k][l], st[k][r - (1 << k)]);
    }
};//}}}

int main() {
    vector<int> a = {3, 7, 4, 5, 6, 2, 9, 8, 1};
    for(int i: a) cout << i << " "; cout << endl;

    auto st = SparseTable(a);
    cout << "(0, 4): " << st.get(0, 4) << endl;
    cout << "(2, 4): " << st.get(2, 4) << endl;
    cout << "(2, 5): " << st.get(2, 5) << endl;
    cout << "(2, 6): " << st.get(2, 6) << endl;
    cout << "(2, 7): " << st.get(2, 7) << endl;
    cout << "(0, 9): " << st.get(0, 9) << endl;
    cout << "(7, 9): " << st.get(7, 9) << endl;
    cout << "(8, 9): " << st.get(8, 9) << endl;
    return 0;
}
