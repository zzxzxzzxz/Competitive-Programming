#include <bits/stdc++.h>
using namespace std;

const int MOD = 1000000007;
#define MAX_N 300005
using DTYPE = int;

DTYPE dat[MAX_N + 1];

struct BIT {
    int n;

    BIT(int n_) {
        n = n_;
        memset(dat, 0, sizeof(dat));
    }

    void _add(DTYPE& a, DTYPE b) {
        a += b;
    }

    void build() {
        for(int i = 1; i <= n; i++) {
            int j = i + (i & -i);
            if(j <= n) {
                _add(dat[j], dat[i]);
            }
        }
    }

    DTYPE sum(int i) {
        DTYPE s = 0;
        while (i > 0) {
            _add(s, dat[i]);
            i -= i & -i;
        }
        return s;
    }

    void add(int i, DTYPE x) {
        while (i <= n) {
            _add(dat[i], x);
            i += i & -i;
        }
    }
};

int main()
{
    vector<int> v = {1, 2, 3, 4, 5};
    int n = int(v.size());
    BIT bit(n);
    for(int i = 1; i <= n; ++i) {
        dat[i] = v[i - 1];
    }
    bit.build();

    for(int i = 1; i <= n; ++i) {
        cout << bit.sum(i) << " \n"[i == n];
    }

    vector<pair<int, int>> M = {{1, 2}, {4, 5}, {3, -1}};
    for(auto& m: M) {
        auto [idx, value] = m;
        bit.add(idx, value);
        cout << idx << " " << value << '\n';
        for(int j = 1; j <= n; ++j) {
            cout << bit.sum(j) << " \n"[j == n];
        }
    }
    return 0;
}
