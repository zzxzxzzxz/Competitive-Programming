#include <bits/stdc++.h>
using namespace std;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

template<class Iter, class Cmp = less<decltype(*declval<Iter>())>>
void quick_select(Iter b, Iter kth, Iter e, Cmp cmp = Cmp()) {
    shuffle(b, e, rng);

    while(b != e) {
        auto it = next(b), lt = it, eq = it;

        while(it != e) {
            if(cmp(*it, *b)) {
                swap(*it, *eq);
                swap(*(eq++), *(lt++));
            } else if(not cmp(*b, *it)) {
                swap(*it, *(eq++));
            }
            ++it;
        }
        swap(*b, *(--lt));

        if(kth < lt) {
            e = lt;
        } else if(eq <= kth) {
            b = eq;
        } else {
            break;
        }
    }
}

int main() {
    //vector<int> v = {20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    //vector<int> v = {2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1};
    vector<int> v = {3, 6, 2, 2, 1, 3, 5, 4, 5};

    for(int i = 0; i < int(v.size()); ++i) cout << v[i] << " ";
    cout << endl;

    //quick_select(v.begin(), v.begin() + 7, v.end(), greater<int>());
    //quick_select(v.begin(), v.begin(), v.end());
    quick_select(v.begin(), v.begin() + 3, v.end(), greater<int>());

    for(int i = 0; i < int(v.size()); ++i) cout << v[i] << " ";
    cout << endl;
    return 0;
}
