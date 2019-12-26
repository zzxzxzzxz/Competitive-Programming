#include <bits/stdc++.h>
using namespace std;

const int MOD = 1000000007;
#define MAX_N 300005

vector<int> build_sa(const string& s) {
    int n = s.size();
    vector<int> rnk(n + 1), idx(n + 1), tmp(n + 1);
    iota(idx.begin(), idx.end(), 0);

    for(int i = 0; i <= n; ++i) {
        rnk[i] = (i < n)? s[i] : -1;
    }
    for(int k = 1; k < n; k <<= 1) {
        auto cmp = [&](const int i, const int j) {
            int ri2 = (i + k <= n)? rnk[i + k] : -1;
            int rj2 = (j + k <= n)? rnk[j + k] : -1;
            return make_pair(rnk[i], ri2) < make_pair(rnk[j], rj2);
        };
        sort(idx.begin(), idx.end(), cmp);

        tmp[idx[0]] = 0;
        for(int i = 1; i <= n; ++i) {
            tmp[idx[i]] = tmp[idx[i - 1]] + int(cmp(idx[i - 1], idx[i]));
        }
        swap(rnk, tmp);
    }
    return idx;
}

vector<int> build_lcp(const string& s, const vector<int>& sa) {
    int n = s.size();
    vector<int> lcp(n + 1, 0), rnk(n + 1);
    for(int i = 0; i < n; ++i) {
        rnk[sa[i]] = i;
    }
    int h = 0;
    for(int i = 0; i < n; ++i) {
        h = max(0, h - 1);
        int j = sa[rnk[i] - 1];
        while(j + h < n and i + h < n and s[i + h] == s[j + h]) {
            ++h;
        }
        lcp[rnk[i] - 1] = h;
    }
    return lcp;
}


int main()
{
    string s = "abracadabra";
    int n = s.size();
    auto sa = build_sa(s);
    auto lcp = build_lcp(s, sa);
    for(int i = 0; i <= n; ++i) {
        printf("%2d%c", sa[i], (i == n)? '\n' : ' ');
    }
    for(int i = 0; i <= n; ++i) {
        printf("%2d%c", lcp[i], (i == n)? '\n' : ' ');
    }
    return 0;
}
