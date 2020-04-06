#include <bits/stdc++.h>
using namespace std;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
size_t seed = rng();

struct Hash {
    size_t operator()(const pair<int, int>& p) const {
        hash<int> h;
        auto hval = seed;
        auto [fi, se] = p;
        hval ^= h(fi) + 0x9e3779b9 + (hval << 6) + (hval >> 2);
        hval ^= h(se) + 0x9e3779b9 + (hval << 6) + (hval >> 2);
        return hval;
    }
};

int main() {
    unordered_set<pair<int, int>, Hash> s;
    s.insert({1, 3});
    s.insert({1, 2});
    s.insert({100, 101});

    cout << (s.find({2, 1}) == s.end() ? "not found" : "found") << endl;
    cout << (s.find({1, 2}) == s.end() ? "not found" : "found") << endl;
    return 0;
}
