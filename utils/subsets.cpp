#include<bits/stdc++.h>

using namespace std;

/*
 * sigma_{0, N} C(N, K) * 2^K = O(3^N)
 */

int main() {
    const int n = 3;
    // iterate over all the masks
    for (int mask = 0; mask < (1 << n); ++mask){
        cout << bitset<n>(mask) << " : ";
        // iterate over all the subsets of the mask
        for(int i = mask; i > 0; i = (i - 1) & mask){
            if(i != mask) cout << ", ";
            cout << bitset<n>(i);
        }
        cout << endl;
    }
    return 0;
}
