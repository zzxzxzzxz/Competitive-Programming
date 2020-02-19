#include <bits/stdc++.h>

using namespace std;

template<class T>
using Fd = typename enable_if<is_fundamental<T>::value>::type;
template<class T>
using NotFd = typename enable_if<!is_fundamental<T>::value>::type;

template<class T>
Fd<T> test(const T&) {
    cout << 1 << endl;
}

template<class T>
NotFd<T> test(const T&) {
    cout << 2 << endl;;
}

int main()
{
    int n = 1;
    vector<int> v;
    test(1);
    test(n);
    test(v);
    test("gg");
    return 0;
}
