#include <bits/stdc++.h>
using namespace std;

vector<int> construct_sa(const string& s) {
    int n = int(s.size());
    vector<int> sa(n + 1), tmp(n + 1), rnk(n + 1);

    for(int i = 0; i <= n; i++) {
        sa[i] = i;
        rnk[i] = i < n ? s[i] : -1;
    }

    for(int k = 1; k <= n; k <<= 1) {
        auto cmp = [&](const int i, const int j) {
            if(rnk[i] != rnk[j]) {
                return rnk[i] < rnk[j];
            }
            int ri = (i + k <= n)? rnk[i + k] : -1;
            int rj = (j + k <= n)? rnk[j + k] : -1;
            return ri < rj;
        };
        sort(sa.begin(), sa.end(), cmp);

        tmp[sa[0]] = 0;
        for(int i = 1; i <= n; i++) {
            tmp[sa[i]] = tmp[sa[i - 1]] + int(cmp(sa[i-1], sa[i]));
        }
        swap(rnk, tmp);
    }
    return sa;
}

bool contain(const string& s, const string& t, const vector<int>& sa) {
    int l = 0, r = int(s.size());
    while(r - l > 1) {
        int mid = l + (r - l) / 2;
        if(s.compare(sa[mid], t.size(), t) >= 0) {
            r = mid;
        } else {
            l = mid;
        }
    }
    return s.compare(sa[r], t.length(), t) == 0;
}

vector<int> construct_lcp(const string& s, vector<int>& sa) {
    int n = s.size();
    vector<int> rnk(n + 1), lcp(n + 1);
    for(int i = 0; i <= n; i++) {
        rnk[sa[i]] = i;
    }
    int h = 0;
    lcp[0] = 0;
    for(int i = 0; i < n; i++) {
        h = max(0, h - 1);
        for(int j = sa[rnk[i] - 1]; j + h < n and i + h < n; h++) {
            if(s[j + h] != s[i + h]) {
                break;
            }
        }
        lcp[rnk[i] - 1] = h;
    }
    return lcp;
}

int main()
{
    string s = "abracadabra";
    vector<int> sa = construct_sa(s);
    for(int i = 0; i < int(sa.size()); i++) {
        printf("%d%c", sa[i], " \n"[i == int(sa.size()) - 1]);
    }
    printf("%d %d\n", contain(s, "brac", sa), contain(s, "bracb", sa));

    vector<int> lcp = construct_lcp(s, sa);
    for(int i = 0; i < int(lcp.size()); i++) {
        printf("%d%c", lcp[i], " \n"[i == int(lcp.size()) - 1]);
    }
    return 0;
}
