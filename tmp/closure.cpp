#include <bits/stdc++.h>

using namespace std;


int main()
{
    auto f = []() {
        int x = 0;
        return [x]() mutable {return x++;};
    };

    auto g = f();
    cout << g() << endl;
    cout << g() << endl;
    cout << g() << endl;
    return 0;
}
