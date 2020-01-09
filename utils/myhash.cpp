#include <bits/stdc++.h>
using namespace std;

struct VecHash {
    size_t operator()(const vector<int>& vec) const {
        hash<int> h;
        auto hash_combine = [&h](size_t& seed, const int& v) {
            seed ^= h(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        };
        size_t seed = 20200109;
        for(auto& val: vec) {
            hash_combine(seed, val);
        }
        return seed;
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
