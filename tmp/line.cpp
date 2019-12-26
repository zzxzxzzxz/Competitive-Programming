#include <bits/stdc++.h>
using namespace std;

template<class T>
struct Line {
    struct iterator {
        using difference_type = int;
        using value_type = T;
        using pointer = T*;
        using reference = T&;
        using iterator_category = random_access_iterator_tag;

        int val;
        iterator(): val(numeric_limits<T>::max()) {}
        iterator(int val_): val(val_) {}

        reference operator*() { return val; }
        pointer operator->() { return &val; }

        iterator& operator++() { ++val; return *this; }
        iterator operator++(int) { iterator tmp(val); operator++(); return tmp; }
        iterator& operator--() { --val; return *this; }
        iterator operator--(int) { iterator tmp(val); operator--(); return tmp; }
        iterator& operator+=(const int& n) { val += n; return *this; }
        iterator& operator-=(const int& n) { return operator+=(-n); }
        friend iterator operator+(iterator lhs, const int& n) { lhs += n; return lhs; };
        friend iterator operator-(iterator lhs, const int& n) { lhs -= n; return lhs; };
        friend int operator-(iterator lhs, const iterator& rhs) { return lhs.val - rhs.val; };
        friend bool operator==(const iterator& lhs, const iterator& rhs) { return lhs.val == rhs.val; }
        friend bool operator!=(const iterator& lhs, const iterator& rhs) { return not operator==(lhs, rhs); }

    };
    using const_iterator = const iterator;

    iterator begin() { return iterator(0); };
    iterator end() { return iterator(numeric_limits<T>::max()); }
    const_iterator begin() const { return begin(); }
    const_iterator end() const { return end(); }
};


class Solution {
    private:
        int kth(vector<int>& a, vector<int>& b, int k) {
            int n = a.size(), m = b.size();
            if(n > m) {
                swap(a, b);
                swap(n, m);
            }

            auto check = [&](const int i) {
                return k - i - 1 >= 0 and a[i] < b[k - i - 1];
            };
            Line<int> line;
            int i = *partition_point(line.begin(), line.begin() + n, check);

            if(i == n) {
                return b[k - n];
            }
            int j = upper_bound(b.begin(), b.end(), a[i]) - b.begin();
            if(i + j == k) {
                return a[i];
            }
            return b[k - i];
        }

    public:
        double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
            int n = nums1.size(), m = nums2.size();
            int m1 = kth(nums1, nums2, (n + m - 1) / 2);
            int m2 = kth(nums1, nums2, (n + m) / 2);
            return double(m1 + m2) / 2.0;
        }
};

int main() {
    vector<int> a = {1, 3, 5, 6, 10, 12, 13, 14, 15, 16};
    vector<int> b = {2, 4, 7, 8, 9, 11, 17, 18, 19, 20};
    Solution sol;
    cout << sol.findMedianSortedArrays(a, b) << endl;
    return 0;
}
