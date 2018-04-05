#include <bits/stdc++.h>
using namespace std;

const int MOD = 1000000007;
#define MAX_N 300005

class myHash {
public:
    size_t operator()(vector<int> const& vec) const {
        std::size_t seed = vec.size();
        for(auto& i : vec) {
            seed ^= i + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        }
        return seed;
    }
};

unordered_set<vector<int>, myHash> s;

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
