#include <bits/stdc++.h>
using namespace std;

random_device rd;
mt19937 g(rd());

template<class Iter, class Cmp>
void QuickSelectExcute(Iter start, Iter kth, Iter stop, Cmp cmp) {
    auto pivot = *start;
    Iter le = partition(start, stop, [&](auto& val){return not cmp(pivot, val);});
    Iter lt = partition(start, le, [&](auto& val){return cmp(val, pivot);});
    if(kth < lt) {
        QuickSelectExcute(start, kth, lt, cmp);
    } else if(le <= kth) {
        QuickSelectExcute(le, kth, stop, cmp);
    }
}

template<class Iter, class Cmp = less<>>
void QuickSelect(Iter start, Iter kth, Iter stop, Cmp cmp = Cmp()) {
    shuffle(start, stop, g);
    QuickSelectExcute(start, kth, stop, cmp);
}

int main() {
    //vector<int> v = {20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    //vector<int> v = {2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1};
    vector<int> v = {3, 6, 2, 2, 1, 3, 5, 4, 5};

    for(int i = 0; i < int(v.size()); ++i) cout << v[i] << " ";
    cout << endl;

    //QuickSelect(v.begin(), v.begin() + 7, v.end(), greater<int>());
    //QuickSelect(v.begin(), v.begin(), v.end());
    QuickSelect(v.begin(), v.begin() + 3, v.end(), greater<int>());

    for(int i = 0; i < int(v.size()); ++i) cout << v[i] << " ";
    cout << endl;
    return 0;
}
