#include <bits/stdc++.h>
using namespace std;

const int MOD = 1000000007;
#define MAX_N 300005


int main()
{
    auto myhash = [](vector<int> vec)->size_t {
        size_t seed = vec.size();
        for(auto& i : vec) {
            seed ^= i + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        }
        return seed;
    };
    unordered_set<vector<int>, decltype(myhash)> s(0, myhash);
    s.insert({1, 2, 3});
    s.insert({1, 2});
    printf("%d\n", s.find({1, 2}) == s.end());
    printf("%d\n", s.find({1, 2, 4}) == s.end());
    return 0;
}
