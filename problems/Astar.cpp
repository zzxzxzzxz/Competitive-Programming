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
    template<class F> struct DefaultDict {
        DefaultDict(F f): f(f) {}
        F f;
        unordered_map<string, int> dict;
        int& operator[](const string& s) {
            if(dict.find(s) == dict.end()) {
                dict[s] = f(s);
            }
            return dict[s];
        }
    };

public:
    int openLock(vector<string>& deadends, string target) {
        int n = target.size();
        unordered_set<string> dead_set(deadends.begin(), deadends.end());
        string s(n, '0');
        if(dead_set.count(s) > 0 or dead_set.count(target) > 0) {
            return -1;
        }

        auto h_dist = [&](const string& s) {
            int ans = 0;
            for(size_t i = 0; i < s.size(); ++i) {
                int d = abs(s[i] - target[i]);
                ans += min(d, 10 - d);
            }
            return ans;
        };

        auto h = DefaultDict(h_dist);
        auto g = DefaultDict([](const string&) { return 1e9 + 10; });

        priority_queue<PIS, vector<PIS>, greater<PIS>> pq;
        g[s] = 0;
        pq.push({g[s] + h[s], s});

        while(pq.size()) {
            auto [dist, v] = pq.top();
            pq.pop();

            if(v == target) return dist;
            if(dist > g[v] + h[v]) continue;

            string u = v;
            for(int i = 0; i < n; ++i) {
                for(int j: vector<int>({1, 9})) {
                    u[i] = (v[i] - '0' + j) % 10 + '0';
                    if(dead_set.count(u) == 0 and g[u] > g[v] + 1) {
                        g[u] = g[v] + 1;
                        pq.push({g[u] + h[u], u});
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
