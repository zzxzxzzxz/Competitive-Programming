#include <bits/stdc++.h>
using namespace std;

const int MOD = 1000000007;
#define MAX_N 300005
#define MAX_P 10000005

int minp[MAX_P];
//vector<int> primes;

void Sieve() {
    for(int i = 2; i < MAX_P; i++) {
        if(minp[i] == 0) {
            //primes.push_back(i);
            for(int j = i; j < MAX_P; j += i) {
                if(minp[j] == 0) {
                    minp[j] = i;
                }
            }
        }
    }
}

vector<int> getpdiv(int x) {
    vector<int> ps;
    while(x > 1) {
        if(ps.empty() or ps.back() != minp[x]) {
            ps.push_back(minp[x]);
        }
        x /= minp[x];
    }
    return ps;
}

int main()
{
    Sieve();
    int x;
    scanf("%d", &x);
    auto ps = getpdiv(x);
    for(auto v: ps) {
        printf("%d\n", v);
    }
    return 0;
}
