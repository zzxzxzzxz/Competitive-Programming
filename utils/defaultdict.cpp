#include<bits/stdc++.h>
using namespace std;


template<class T, class U, U default_val>
struct defaultdict {
    unordered_map<T, U> dict;
    U& operator[](T key) {
        if(dict.find(key) == dict.end()) {
            dict[key] = default_val;
        }
        return dict[key];
    }
};

int main() {
    const int INF = 1e9 + 10;
    defaultdict<int, int, INF> dict;
    cout << dict[3] << endl;
    dict[3] = 5;
    cout << dict[3] << endl;
    return 0;
}
