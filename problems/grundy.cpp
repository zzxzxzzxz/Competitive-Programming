//{{{
#include<bits/stdc++.h>
using namespace std;
template<class T>
void print(const vector<T>& data) {
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

class Solution {
private:
    unordered_map<int, int> dp;
    int grundy(int n) {
        if(n < 1) {
            return 0;
        }
        if(dp.count(n)) {
            return dp[n];
        }
        unordered_set<int> nxt;
        for(int i = 0; i < n / 2; ++i) {
            nxt.insert(grundy(i) ^ grundy(n - 2 - i));
        }
        int i = 0;
        while(nxt.count(i)) {
            ++i;
        }
        dp[n] = i;
        return i;
    }

public:
    bool canWin(string s) {
        int sg = 0;
        int cur = 0;
        for(int i = 0; i < int(s.size()); ++i) {
            if(s[i] == '+') {
                cur += 1;
            } else {
                sg ^= grundy(cur);
                cur = 0;
            }
        }
        sg ^= grundy(cur);
        return sg != 0;
    }
};

/*
 * https://leetcode.com/problems/flip-game-ii
 */

int main() {
    string s = "++++";
    Solution sol;
    auto ans = sol.canWin(s);
    print(ans);
    return 0;
}
