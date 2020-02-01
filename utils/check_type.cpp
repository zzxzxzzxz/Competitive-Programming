#include <vector>

template<typename T> struct TD;

int main() {
    std::vector<int> v;
    TD<decltype(v)> td;
    return 0;
}
