#include <bits/stdc++.h>
using namespace std;

const int MAX_P = 1000005;

int minp[MAX_P];
vector<int> primes;

void Sieve() {
    for(int i = 2; i < MAX_P; ++i) {
        if(minp[i] == 0) {
            primes.push_back(i);
            minp[i] = i;
        }
        for(int j = 0; j < int(primes.size()) and i * primes[j] < MAX_P; ++j) {
            minp[i * primes[j]] = primes[j];
            if(i % primes[j] == 0) break;
        }
    }
}

vector<int> getpdiv(int x) {
    vector<int> ps;
    while(x > 1) {
        int d = minp[x];
        ps.push_back(d);
        while(x % d == 0) {
            x /= d;
        }
    }
    return ps;
}

int main() {
    Sieve();
    int x = 734132;
    cout << x << " : ";
    auto ps = getpdiv(x);
    for(auto v: ps) cout << v << " ";
    cout << endl;
    return 0;
}
