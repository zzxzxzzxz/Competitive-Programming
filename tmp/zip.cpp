#include <iostream>
#include <vector>
#include <set>
using namespace std;

template<size_t ...Is, class Iter>
constexpr auto zip(index_sequence<Is...>, Iter be, Iter ed) {
    struct iterator {
        Iter iter;
        bool operator!=(const iterator& other) { return ((get<Is>(iter) != get<Is>(other.iter)) and ...); }
        void operator++() { ((++get<Is>(iter)), ...); }
        auto operator*() { return tie(*get<Is>(iter)...); }
    };
    struct iterable_wrapper {
        Iter be, ed;
        auto begin() const { return iterator{ be }; }
        auto end() const { return iterator{ ed }; }
    };
    return iterable_wrapper{ be, ed };
}
template<class ...Cs, class Iter = tuple<decltype(begin(declval<Cs>()))...>>
constexpr auto zip(Cs&& ...cs) {
    return zip(index_sequence_for<Cs...>{}, Iter{ begin(cs)... }, Iter{ end(cs)... });
}

int main() {
    vector<int> v1 = {1, 2, 3, 4};
    set<int> v2 = {11, 12, 13, 14, 15, 16, 17};
    vector<double> v3 = {4.5, 5.5, 6.5};
    for(const auto& [k1, k2, k3] : zip(v1, v2, v3)) {
        cout << k1 << " ";
        cout << k2 << " ";
        cout << k3 << endl;
    }
    return 0;
}
