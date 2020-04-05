#include <bits/stdc++.h>
using namespace std;

template<typename T>
void apply_permutation(vector<T>& A, vector<int>& P) {
   for(size_t i = 0 ; i < A.size() ; i++){
        size_t curr = i;
        size_t next = P[curr];
        while(next != i) {
            swap(A[curr], A[next]);
            P[curr] = curr;
            curr = next;
            next = P[next];
        }
        P[curr] = curr;
   }
}

int main() {
    vector<char> A = {'a', 'b', 'c', 'd', 'e'};
    vector<int> P = {4, 3, 2, 0, 1};
    apply_permutation(A, P);
    for(size_t i = 0; i < A.size(); ++i) {
        cout << A[i] << " \n"[i == A.size() - 1];
    }
    return 0;
}
