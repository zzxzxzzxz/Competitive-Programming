#include <bits/stdc++.h>
using namespace std;

using Data = int;
Data zero = 0;

vector<Data> dat;

struct BIT {
    int n;
    BIT(int n, Data* ptr = nullptr): n(n) {
        dat.assign(n + 1, 0);
        if(ptr) {
            for(int i = 1; i <= n; ++i) {
                _add(dat[i], ptr[i - 1]);
                int j = i + (i & -i);
                if(j <= n) {
                    _add(dat[j], dat[i]);
                }
            }
        }
    }

    void _add(Data& a, Data b) {
        a += b;
    }

    Data sum(int i) {
        Data s = zero;
        while (i > 0) {
            _add(s, dat[i]);
            i -= i & -i;
        }
        return s;
    }

    void add(int i, Data&& x) {
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
    BIT bit(n, &v[0]);

    bit.add(2, 3);
    for(int i = 1; i <= n; ++i) {
        cout << bit.sum(i) << " \n"[i == n];
    }
    return 0;
}
