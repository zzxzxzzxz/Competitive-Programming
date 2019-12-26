#include<bits/stdc++.h>

using namespace std;

int main() {
    vector<int> s = {4, 5, 11, 15};
    int sup = 0;
    for(int i: s) {
        sup |= (1 << i);
    }
    int sub = (sup - 1) & sup;
    while(sub != sup) { // -1 & sup == sup
        for(int i = 0; i < 31; ++i) {
            if((sub >> i) & 1) {
                cout << i << " ";
            }
        }
        cout << endl;

        sub = (sub - 1) & sup;
    }
    return 0;
}
