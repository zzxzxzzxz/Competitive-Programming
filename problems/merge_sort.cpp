#include <bits/stdc++.h>
using namespace std;

void merge_list(list<int>& l1, list<int>& l2) {
    auto it = l1.begin();
    while(not l2.empty()) {
        if(it == l1.end() or l2.front() < *it) {
            l1.splice(it, l2, l2.begin(), next(l2.begin()));
        } else {
            ++it;
        }
    }
}

void test_list(list<int>&& lst) {
    auto get_n = [](list<int>& from, auto& it, list<int>& to, int n) {
        auto start = it;
        for(int i = 0; i < n; ++i) if(it != from.end()) ++it;
        to.splice(to.begin(), from, start, it);
    };

    int n = lst.size();
    for(int i = 1; i < n; i <<= 1) {
        auto it = lst.begin();
        while(it != lst.end()) {
            list<int> lst1, lst2;
            get_n(lst, it, lst1, i);
            get_n(lst, it, lst2, i);
            merge_list(lst1, lst2);
            lst.splice(it, lst1, lst1.begin(), lst1.end());
        }
    }
    for(int i : lst) cout << i << " "; cout << endl;
}

template<class Iter>
void merge_(Iter start, Iter mid, Iter stop) {
    vector tmp(start, mid);
    auto it = start, it1 = tmp.begin(), it2 = mid;
    while(it1 != tmp.end() or it2 != stop) {
        if(it2 == stop or (it1 != tmp.end() and *it1 < *it2)) {
            *(it++) = *(it1++);
        } else {
            *(it++) = *(it2++);
        }
    }
}

void test_vector(vector<int>& v) {
    int n = v.size();
    for(int i = 1; i < n; i <<= 1) {
        for(int j = 0; j < n; j += i * 2) {
            int k1 = min(n, j + i), k2 = min(n, j + i * 2);
            merge_(v.begin() + j, v.begin() + k1, v.begin() + k2);
        }
    }
    for(int i : v) cout << i << " "; cout << endl;
}

int main() {
    int n = 28;
    vector<int> v(n);
    for(int i = 0; i < n; ++i) {
        int k = (i + 12) % n;
        v[i] = (k - k % 7) + (k % 7 + 5) % 7;
    }
    for(int i : v) cout << i << " "; cout << endl;

    test_list(list(v.begin(), v.end()));
    test_vector(v);
    return 0;
}
