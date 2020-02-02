#include <vector>
using namespace std;

template<class T>
auto test(T&& t) {
    return *t.begin();
}

template<typename T> struct TD;

int main() {
    vector<vector<int>> v = {{1, 2}, {3}};
    auto&& x = test(v);
    auto&& y = v[0];

    TD<decltype(x)> td1;
    TD<decltype(y)> td2;
    return 0;
}
