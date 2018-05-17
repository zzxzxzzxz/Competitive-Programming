#include <bits/stdc++.h>
using namespace std;

using LL = long long;

size_t seed;

auto myhash = [](pair<int, LL> p)->size_t {
    size_t ret = seed;
    ret ^= p.first + 0x9e3779b9 + (ret << 6) + (ret >> 2);
    ret ^= p.second + 0x9e3779b9 + (ret << 6) + (ret >> 2);
    return ret;
};

unordered_map<pair<int, LL>, int, decltype(myhash)> dp(0, myhash);

int grundyNumber(int k, LL used) {
    pair<int, LL> p = {k, used};
    auto ii = dp.find(p);
    if(ii != dp.end()) {
        return ii->second;
    }
    set<int> s;
    for(int i = 1; i < k + 1; i++) {
        if(((1ULL << i) & used) == 0) {
            int sg = grundyNumber(k - i, (1ULL << i) | used);
            s.insert(sg);
        }
    }
    if(s.empty()) {
        dp[p] = 0;
        return 0;
    }
    int ret = 0;
    while(s.find(ret) != s.end()) {
        ++ret;
    }
    dp[p] = ret;
    return ret;
}

int main()
{
    srand(time(0));
    seed = rand();

    int n, y = 0;
    scanf("%d", &n);
    for(int i = 0; i < n; i++) {
        int x;
        scanf("%d", &x);
        y ^= grundyNumber(x, 0);
    }
    if(y == 0) {
        printf("YES\n");
    } else {
        printf("NO\n");
    }
    return 0;
}
