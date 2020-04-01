#include <bits/stdc++.h>
using namespace std;

const int MOD = 1000000007;
#define MAX_N 300005

size_t F[MAX_N];

void build_failure_function(string& p) {
    size_t m = p.size();
    F[0] = 0;
    for(size_t i = 1; i < m; i++) {
        size_t k = F[i - 1];
        while(k != 0 and p[k] != p[i]) {
            k = F[k - 1];
        }
        if(p[k] == p[i]) {
            F[i] = k + 1;
        } else {
            F[i] = 0;
        }
    }
}

size_t kmp(string& s, string& p) {
    size_t n = s.size(), m = p.size();
    size_t k = 0;
    for(size_t i = 0; i < n; i++) {
        while(k != 0 and p[k] != s[i]) {
            k = F[k - 1];
        }
        if(p[k] == s[i]) {
            k = k + 1;
        } else {
            k = 0;
        }
        if(k == m) {
            return i - m + 1;
            // k = F[k - 1]
        }
    }
    return string::npos;
}

int main()
{
    string s = "abxabcabcabyab";
    string p = "abcaby";
    build_failure_function(p);
    size_t idx = kmp(s, p);
    cout << idx << endl;
    if(idx == string::npos) {
        printf("Not found\n");
        return 0;
    }
    cout << s << endl;
    for(size_t i = 0; i < idx; ++i) cout << " ";
    cout << p << endl;
    return 0;
}
