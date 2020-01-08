//{{{
#include<bits/stdc++.h>
using namespace std;
template<class T>
void print(const vector<T>& data) {
    int n = int(data.size());
    for(int i = 0; i < n; ++i) { cout << data[i] << ((i == n - 1)? '\n' : ' '); }
}
inline void print() {putchar('\n');}
template<class T, class... U> inline void print(const T& head, const U&... tail) {
    cout << head;
    if(sizeof...(tail)) putchar(' ');
    print(tail...);
}
//}}}

class MajorityChecker {
private:
    int B = 1;
    vector<int> arr, maj;
    unordered_map<int, vector<int>> pos;

public:
    MajorityChecker(vector<int>& arr): arr(arr) {
        int n = arr.size();
        for(int i = 0; i < n; ++i) {
            pos[arr[i]].push_back(i);
        }
        B = floor(sqrt(n));
        maj.resize(ceil(n / B));
        for(int i = 0; i < int(maj.size()); ++i) {
            int maxval = 0, best = -1;
            unordered_map<int, int> cnt;
            for(int j = i * B; j < min((i + 1) * B, n); ++j) {
                cnt[arr[j]] += 1;
                if(maxval < cnt[arr[j]]) {
                    maxval = cnt[arr[j]];
                    best = arr[j];
                }
            }
            maj[i] = best;
        }
    }

    int count(int left, int right, int num) {
        auto it1 = lower_bound(pos[num].begin(), pos[num].end(), left);
        auto it2 = upper_bound(pos[num].begin(), pos[num].end(), right);
        return it2 - it1;
    }

    int query(int left, int right, int threshold) {
        int l = left, r = right + 1;
        while(l < r and l % B != 0) {
            if(count(left, right, arr[l]) >= threshold) {
                return arr[l];
            }
            ++l;
        }
        while(l < r and r % B != 0) {
            --r;
            if(count(left, right, arr[r]) >= threshold) {
                return arr[r];
            }
        }
        while(l < r) {
            if(count(left, right, maj[l / B]) >= threshold) {
                return maj[l / B];
            }
            l += B;
        }
        return -1;
    }
};

/*
 * https://leetcode.com/problems/online-majority-element-in-subarray/
 */

int main() {
    vector<int> arr = {2,2,1,2,1,2,2,1,1,2};
    MajorityChecker m(arr);
    cout << m.query(2, 5, 4) << endl;
    cout << m.query(0, 5, 6) << endl;
    cout << m.query(0, 1, 2) << endl;
    cout << m.query(2, 3, 2) << endl;
    cout << m.query(6, 6, 1) << endl;
    cout << m.query(0, 3, 3) << endl;
    cout << m.query(4, 9, 6) << endl;
    cout << m.query(4, 8, 4) << endl;
    cout << m.query(5, 9, 5) << endl;
    cout << m.query(0, 1, 2) << endl;
    return 0;
}
