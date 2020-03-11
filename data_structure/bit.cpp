#include <bits/stdc++.h>
using namespace std;

using Data = int;
Data zero = 0;

vector<Data> dat;
void _add(Data& a, Data b) {
    a += b;
}


struct BIT {
    int lg(int n) { return 31 - __builtin_clz(n); }

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

    int lower_bound(int v) {
        int sum = 0, pos = 0;

        for(int i = lg(n); i >= 0; --i) {
            if(pos + (1 << i) < n and sum + dat[pos + (1 << i)] < v) {
                sum += dat[pos + (1 << i)];
                pos += (1 << i);
            }
        }
        return pos + 1;
    }
};

int main()
{
    vector<int> v = {2, 2, 2, 3, 3};
    int n = int(v.size());
    BIT bit(n, &v[0]);

    for(int i = 1; i <= n; ++i) {
        cout << v[i - 1] << " \n"[i == n];
    }
    for(int i = 1; i <= n; ++i) {
        cout << bit.sum(i) << " \n"[i == n];
    }
    bit.add(3, 10);
    cout << "add(3, 10)" << endl;
    for(int i = 1; i <= n; ++i) {
        cout << bit.sum(i) << " \n"[i == n];
    }

    cout << "lower_bound:" << endl;
    for(int v = 1; v <= 7; ++v) {
        int idx = bit.lower_bound(v);
        cout << v << ": " << idx << " (" << bit.sum(idx) << ")" << endl;
    }
    return 0;
}
