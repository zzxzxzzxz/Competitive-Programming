//{{{
#include<bits/stdc++.h>
using namespace std;
template<class T>
void print(vector<T>&& data) {
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

using PIS = pair<int, string>;

class Solution {
private:
    const int INF = 0x3f3f3f3f;
    int h_dist(string& s, string& t) {
        int ans = 0;
        for(size_t i = 0; i < s.size(); ++i) {
            int d = abs(s[i] - t[i]);
            ans += min(d, 10 - d);
        }
        return ans;
    }

public:
    int openLock(vector<string>& deadends, string target) {
        int n = target.size();
        unordered_set<string> dead_set(deadends.begin(), deadends.end());
        string s(n, '0');
        if(dead_set.count(s) > 0 or dead_set.count(target) > 0) {
            return -1;
        }

        unordered_map<string, int> g_dict, h_dict;
        auto h = [&](string& s) -> int {
            if(h_dict.count(s) == 0) h_dict[s] = h_dist(s, target);
            return h_dict[s];
        };

        auto g = [&](string& s) -> int& {
            if(g_dict.count(s) == 0) g_dict[s] = INF;
            return g_dict[s];
        };

        priority_queue<PIS, vector<PIS>, greater<PIS>> pq;
        g(s) = 0;
        pq.push({g(s) + h(s), s});

        while(pq.size()) {
            auto [dist, v] = pq.top();
            pq.pop();

            if(v == target) return dist;
            if(dist > g(v) + h(v)) continue;

            string u = v;
            for(int i = 0; i < n; ++i) {
                for(int j: vector<int>({1, 9})) {
                    u[i] = (v[i] - '0' + j) % 10 + '0';
                    if(dead_set.count(u) == 0 and g(u) > g(v) + 1) {
                        g(u) = g(v) + 1;
                        pq.push({g(u) + h(u), u});
                    }
                    u[i] = v[i];
                }
            }
        }
        return -1;
    }
};

/*
 * https://leetcode.com/problems/open-the-lock/
 */

int main() {
    vector<string> deadends = {"0201","0101","0102","1212","2002"};
    string target = "0202";
    Solution sol;
    auto ans = sol.openLock(deadends, target);
    print(ans);
    return 0;
}
