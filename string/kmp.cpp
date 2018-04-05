#include <bits/stdc++.h>
using namespace std;

const int MOD = 1000000007;
#define MAX_N 300005

int F[MAX_N];

void build_failure_function(string& p) {
    int m = p.size();
    F[0] = 0;
    int k = 0;
    for(int i = 1; i < m; i++) {
        while(k > 0 and p[k] != p[i]) {
            k = F[k - 1];
        }
        if(p[k] == p[i]) {
            ++k;
        }
        F[i] = k;
    }
}

size_t kmp(string& s, string& p) {
    int n = s.size(), m = p.size();
    int k = 0;
    for(int i = 0; i < n; i++) {
        while(k > 0 and p[k] != s[i]) {
            k = F[k - 1];
        }
        if(p[k] == s[i]) {
            ++k;
        }
        if(k == m) {
            return i - m + 1;
        }
    }
    return string::npos;
}

int main()
{
    string s = "abxabcabcabyab";
    string p = "abcaby";
    build_failure_function(p);
    printf("%zu\n", kmp(s, p));
    return 0;
}
