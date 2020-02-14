#include <bits/stdc++.h>
using namespace std;

struct SparseTable {
    vector<vector<vector<vector<int>>>> st;
    int __lg(int n) { return 31 - __builtin_clz(n); }

    SparseTable(const vector<vector<int>>& a) {
        int n = a.size(), m = a[0].size();
        int logn = __lg(n), logm = __lg(m);

        st.resize(logn + 1);
        for(int i = 0; i <= logn; ++i) {
            st[i].resize(logm + 1);
            for(int j = 0; j <= logm; ++j) {
                st[i][j].assign(n, vector<int>(m, -1));
            }
        }

        for(int i = 0; i < n; ++i) {
            for(int j = 0; j < m; ++j) {
                st[0][0][i][j] = a[i][j];
            }
        }

        for(int i = 0; i < n; ++i) {
            for(int k = 1; (1 << k) <= m; ++k) {
                for(int j = 0; j + (1 << k) <= m; ++j) {
                    st[0][k][i][j] = max(
                        st[0][k - 1][i][j],
                        st[0][k - 1][i][j + (1 << (k - 1))]
                    );
                }
            }
        }

        for(int k = 0; (1 << k) <= m; ++k) {
            for(int l = 1; (1 << l) <= n; ++l) {
                for(int j = 0; j < m; ++j) {
                    for(int i = 0; i + (1 << l) <= n; ++i) {
                        st[l][k][i][j] = max(
                            st[l - 1][k][i][j],
                            st[l - 1][k][i + (1 << (l - 1))][j]
                        );
                    }
                }
            }
        }
    }

    int get(int r1, int c1, int r2, int c2) {
        if(r1 >= r2 or c1 >= c2) {
            return 0;
        }
        int l = __lg(r2 - r1);
        int k = __lg(c2 - c1);

        return max(
            max(st[l][k][r1][c1], st[l][k][r1][c2 - (1 << k)]),
            max(st[l][k][r2 - (1 << l)][c1], st[l][k][r2 - (1 << l)][c2 - (1 << k)])
        );
    }
};

int main() {
    vector<vector<int>> a = {
        {3, 0, 4, 6, 3},
        {4, 5, 3, 0, 2},
        {1, 5, 9, 2, 1},
        {5, 7, 5, 8, 0},
    };
    for(auto& v: a) {
        for(int i: v) cout << i << " "; cout << endl;
    }

    auto st = SparseTable(a);
    cout << "(0, 0, 4, 5): " << st.get(0, 0, 4, 5) << endl;
    cout << "(0, 0, 2, 5): " << st.get(0, 0, 2, 5) << endl;
    cout << "(0, 0, 4, 2): " << st.get(0, 0, 4, 2) << endl;
    cout << "(0, 3, 4, 5): " << st.get(0, 3, 4, 5) << endl;
    cout << "(1, 0, 2, 5): " << st.get(1, 0, 2, 5) << endl;
    cout << "(0, 4, 4, 5): " << st.get(0, 4, 4, 5) << endl;
    return 0;
}
