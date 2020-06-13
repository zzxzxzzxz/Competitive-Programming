#include<bits/stdc++.h>
using namespace std;

class Solution {
private:
    const int INF = 1e9 + 10;
    vector<vector<int>> dp, cost;
    void divide_and_conquer(int t, int l, int r, int optl, int optr) {
        if(l + 1 == r) {
            return;
        }

        int mid = l + (r - l) / 2;
        pair<int, int> best = {INF, -1};

        for(int u = optl; u <= min(mid, optr); ++u) {
            best = min(best, make_pair(dp[t - 1][u] + cost[u][mid], u));
        }

        int opt;
        tie(dp[t][mid], opt) = best;

        divide_and_conquer(t, l, mid, optl, opt);
        divide_and_conquer(t, mid, r, opt, optr);
    }

public:
    int minDistance(vector<int>& houses, int k) {
        int n = houses.size();
        dp.assign(k + 1, vector<int>(n + 1, 0));
        cost.assign(n + 1, vector<int>(n + 1, 0));

        sort(houses.begin(), houses.end());

        for(int mid = 0; mid < n; ++mid) {
            for(auto [l, r] : { pair{mid, mid + 1}, pair{mid, mid + 2} }) {
                while(l >= 0 and r < n) {
                    cost[l][r + 1] = cost[l + 1][r] + houses[r] - houses[l];
                    --l, ++r;
                }
            }
        }

        for(int i = 1; i <= n; ++i) {
            dp[1][i] = cost[0][i];
        }

        for(int t = 2; t <= k; ++t) {
            divide_and_conquer(t, 1, n + 1, 1, n);
        }
        return dp[k][n];
    }
};

// https://leetcode.com/problems/allocate-mailboxes/

int main() {
    vector<int> houses = {1, 4, 8, 10, 20};
    int k = 3;
    cout << Solution().minDistance(houses, k) << endl;
    return 0;
}
