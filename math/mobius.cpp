#include<bits/stdc++.h>
using namespace std;

const int MAX_P = 100005;

bool composite[MAX_P];
int mu[MAX_P];
vector<int> primes;

void Sieve() {
    mu[1] = 1;
    for(int i = 2; i < MAX_P; ++i) {
        if(not composite[i]) {
            primes.push_back(i);
            mu[i] = -1;
        }
        for(int j = 0; j < int(primes.size()) and i * primes[j] < MAX_P; ++j) {
            composite[i * primes[j]] = true;
            if(i % primes[j] == 0) {
                mu[i * primes[j]] = 0;
                break;
            } else {
                mu[i * primes[j]] = mu[i] * mu[primes[j]];
            }
        }
    }
}

int main() {
    Sieve();
    for(int i = 1; i <= 30; ++i) {
        printf("%2d ", i);
    }
    cout << endl;
    for(int i = 1; i <= 30; ++i) {
        printf("%2d ", mu[i]);
    }
    cout << endl;
    return 0;
}
