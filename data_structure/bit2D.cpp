#include <bits/stdc++.h>
using namespace std;

const int MOD = 1000000007;
#define MAX_N 5005

using DTYPE = int;
DTYPE dat[MAX_N + 1][MAX_N + 1];

struct BIT2D {
    int n, m;

    BIT2D(int n_, int m_) {
        n = n_;
        m = m_;
    }
    void _add(DTYPE& a, DTYPE b) {
        a += b;
    }

    void build() {
        for(int i = 1; i <= n; i++) {
            for(int j = 1; j <= m; j++) {
                int l = j + (j & -j);
                if(l <= m) {
                    _add(dat[i][l], dat[i][j]);
                }
            }
        }
        for(int i = 1; i <= n; i++) {
            int k = i + (i & -i);
            if(k <= n) {
                for(int j = 1; j <= m; j++) {
                    _add(dat[k][j], dat[i][j]);
                }
            }
        }
    }


    DTYPE sum(int i, int j) {
        DTYPE s = 0;
        while (i > 0) {
            int k = j;
            while(k > 0) {
                _add(s, dat[i][k]);
                k -= k & -k;
            }
            i -= i & -i;
        }
        return s;
    }


    void add(int i, int j, DTYPE x) {
        while (i <= n) {
            int k = j;
            while(k <= m) {
                _add(dat[i][k], x);
                k += k & -k;
            }
            i += i & -i;
        }
    }
};

int main()
{
    int n = 4, m = 4;
    vector<vector<int>> v = {
        {1, 0, 1, 1},
        {1, 0, 1, 0},
        {0, 1, 0, 1},
        {1, 0, 0, 1}
    };
    BIT2D bit(n, m);
    for(int i = 1; i <= n; ++i) {
        for(int j = 1; j <= m; ++j) {
            dat[i][j] = v[i-1][j-1];
        }
    }
    bit.build();

    for(int i = 1; i <= n; ++i) {
        for(int j = 1; j <= m; ++j) {
            cout << bit.sum(i, j) << " \n"[j == m];
        }
    }
    putchar('\n');

    vector<tuple<int, int, int>> Q = {
        {1, 1, -1},
        {2, 3, 1},
        {3, 2, -1}
    };
    for(auto& q: Q) {
        auto [row, col, value] = q;
        bit.add(row, col, value);
        cout << row << " " << col << " " << value << "\n";
        for(int i = 1; i <= n; ++i) {
            for(int j = 1; j <= m; ++j) {
                cout << bit.sum(i, j) << " \n"[j == m];
            }
        }
        putchar('\n');
    }
    return 0;
}
