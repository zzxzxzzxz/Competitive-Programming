#include <bits/stdc++.h>
using namespace std;

const int MOD = 1000000007;
#define MAX_N 300005

size_t Z[MAX_N];

void build_Z(string& p) {
    size_t m = p.size();
    Z[0] = 0;
    size_t l = 0, r = 0;
    for(size_t i = 1; i < m; i++) {
        size_t& z = Z[i];
        if(i < r and Z[i - l] < r - i) {
            z = Z[i - l];
            continue;
        }
        z = (r > i)? r - i : 0;

        while(i + z < m and p[i + z] == p[z]) {
            ++z;
        }
        l = i;
        r = i + z;
    }
}

size_t z_alg(string& s, string& p) {
    size_t n = s.size(), m = p.size();
    size_t l = 0, r = 0;
    for(size_t i = 0; i < n; ++i) {
        if(i < r and Z[i - l] < r - i) {
            continue;
        }
        size_t z = (r > i)? r - i : 0;

        while(i + z < n and z < m and s[i + z] == p[z]) {
            ++z;
        }
        if(z == m) {
            return i;
        }
        l = i;
        r = i + z;
    }
    return string::npos;
}

int main()
{
    string s = "abaabaabcaabxaaazaaz";
    string p = "aabcaabxaaaz";
    build_Z(p);
    for(int i = 0; i < int(p.size()); ++i) {
        printf("%2c ", p[i]);
    }
    printf("\n");
    for(int i = 0; i < int(p.size()); ++i) {
        printf("%2zu ", Z[i]);
    }
    printf("\n");

    size_t idx = z_alg(s, p);
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
