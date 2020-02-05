#include <bits/stdc++.h>
using namespace std;

random_device rd;
mt19937 mt(rd());
uniform_int_distribution<size_t> dist(0, SIZE_MAX);
size_t seed = dist(mt);

struct VecHash {
    size_t operator()(const vector<int>& vec) const {
        hash<int> h;
        auto hash_combine = [&h](size_t& hval, const int& v) {
            hval ^= h(v) + 0x9e3779b9 + (hval << 6) + (hval >> 2);
        };
        auto hval = seed;
        for(auto& val: vec) {
            hash_combine(hval, val);
        }
        return hval;
    }
};

unordered_set<vector<int>, VecHash> s;

int main()
{
    s.insert({1, 2, 3});
    s.insert({1, 2});
    s.insert({4});
    auto ii = s.find({1, 2});
    printf("%d\n", ii == s.end());
    ii = s.find({4, 5});
    printf("%d\n", ii == s.end());
    return 0;
}
