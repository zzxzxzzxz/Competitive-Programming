#include "bits/stdc++.h"
using namespace std;

template<class T> struct IterMask {/*{{{*/
    int n;
    vector<T> ds;
    T mx;
    IterMask(vector<T>& v): n(v.size()), ds({1}), mx(1) {
        for(int i = 0; i < n; ++i) {
            ds.emplace_back(ds.back() * (1 + v[i]));
        }
        mx = ds.back();
    }

    auto and_(T i, T m) {
        auto res = i;
        for(int l = n - 1; l >= 0; --l) {
            auto i2 = i % ds[l], m2 = m % ds[l];
            auto diff = i - i2 - m + m2;
            if(diff > 0) res -= diff;
            i = i2, m = m2;
        }
        return res;
    }

    auto decode(T m) {
        vector<T> res(n);
        for(int l = n - 1; l >= 0; --l) {
            res[l] = m / ds[l];
            m %= ds[l];
        }
        return res;
    };
};/*}}}*/

template<class T, class = decltype(*begin(declval<T>()))>
ostream& operator<<(ostream& out, T&& v) {
    out << '[';
    for(auto it = begin(v); it != end(v); ++it) {
        if(it != begin(v)) out << ',' << ' ';
        out << *it;
    }
    return out << ']';
}

int main() {
    vector<int> v = {1, 0, 2};
    auto im = IterMask<int>(v);
    for(int mask = 0; mask < im.mx; ++mask) {
        cout << im.decode(mask) << endl;
        for(int s = mask; s > 0; s = im.and_(s - 1, mask)) {
            cout << '\t' << im.decode(s) << endl;
        }
    }
    return 0;
}
