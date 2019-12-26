#include <bits/stdc++.h>
using namespace std;

const int MOD = 1000000007;
#define MAX_N 300005

string padding(string& s) {
    string t;
    for(int i = 0; i < int(s.size()); ++i) {
        t.push_back('#');
        t.push_back(s[i]);
    }
    t.push_back('#');
    return t;
}

int manacher(string& s)
{
    string t = padding(s);
    int N = int(t.size());
    vector<int> P(N);
    int c = 0, r = 0;
    int ans = 0;
    for(int i = 0; i < N; ++i) {

        int mirror = 2 * c - i;
        if(mirror >= 0 and P[mirror] < r - i) {
            P[i] = P[mirror];
            continue;
        }
        P[i] = max(0, r - i);

        int a = i - 1 - P[i], b = i + 1 + P[i];
        while(a >= 0 and b < N and t[a] == t[b]) {
            ++P[i];
            --a;
            ++b;
        }

        c = i;
        r = i + P[i];

        if(ans < P[i]) {
            ans = P[i];
        }
    }
    return ans;
}

int main() {
    string s("abaxabaxabb");
    cout << manacher(s) << endl;
    return 0;
}
