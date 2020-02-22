#include <iostream>
#include <vector>
#include <set>
using namespace std;

template<size_t ...Is, class T, class ...Cs,
    class Iter = tuple<decltype(begin(declval<Cs>()))...>,
    class Val = tuple<decltype(*begin(declval<Cs>()))&...>
    >
constexpr auto zip(index_sequence<Is...>, T&& iterables, Cs&&...) {
    struct iterator {
        Iter iter;
        unique_ptr<Val> tref = nullptr;
        bool operator!=(const iterator& other) { return ((get<Is>(iter) != get<Is>(other.iter)) and ...); }
        auto& operator++() { ((++get<Is>(iter)), ...); return *this; }
        auto& operator*() {
            tref.reset();
            tref = make_unique<Val>(tie(*get<Is>(iter)...));
            return *tref;
        }
    };
    struct iterable_wrapper {
        T iterables;
        auto begin() const { return iterator { Iter{ std::begin(get<Is>(iterables))... } }; }
        auto end() const { return iterator { Iter{ std::end(get<Is>(iterables))... } }; }
    };
    return iterable_wrapper{ forward<T>(iterables) };
}
template<class ...Cs, class = tuple<decltype(begin(declval<Cs>()))...>>
constexpr auto zip(Cs&& ...cs) {
    return zip(index_sequence_for<Cs...>{}, tie(cs...), forward<Cs>(cs)...);
}

int main() {
    vector<int> v = {1, 2, 3};
    for(auto [x] : zip(v)) cout << x << " "; cout << endl;
    for(auto [x] : zip(zip(v))) cout << get<0>(x) << " "; cout << endl;
    for(auto [x] : zip(zip(v))) cout << get<0>(x) << " "; cout << endl;
    v[1] = 100;
    for(auto [x] : zip(v)) cout << x << " "; cout << endl;
    for(auto [x] : zip(zip(v))) cout << get<0>(x) << " "; cout << endl;
    return 0;
}
