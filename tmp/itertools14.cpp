#include <bits/stdc++.h>
using namespace std;

template<typename T> constexpr auto range(T start, T stop, T step) {
    struct iterator {
        using difference_type = T;
        using value_type = T;
        using pointer = T*;
        using reference = T&;
        using iterator_category = random_access_iterator_tag;

        T i, step;
        T operator-(const iterator& other) const { return i - other.i; };
        bool operator!=(const iterator& other) const { return i != other.i; }
        auto& operator+=(const int& n) { i += step * n; return *this; }
        auto& operator++() { i += step; return *this; }
        auto& operator*() { return i; }
    };
    struct iterable_wrapper {
        T start, stop, step;
        auto begin() const { return iterator{ start, step }; }
        auto end() const { return iterator{ stop, step }; }
        size_t size() const { return (stop - start) / step; }

        iterable_wrapper(T start_, T stop_, T step_): start(start_), stop(stop_), step(step_) {
            stop = step > 0 ? max(start, stop) : min(start, stop);
            stop += (step - (stop - start) % step) % step;
        }
    };
    return iterable_wrapper(start, stop, step);
};
template<typename T> constexpr auto range(T start, T stop) { return range(start, stop, T(1)); }
template<typename T> constexpr auto range(T stop) { return range(T(0), stop, T(1)); }

template<typename T, typename Iter = decltype(rbegin(declval<T>()))>
constexpr auto reversed(T&& iterable) {
    struct iterable_wrapper {
        T iterable;
        auto begin() const { return std::rbegin(iterable); }
        auto end() const { return std::rend(iterable); }
        auto size() const { return iterable.size(); }
    };
    return iterable_wrapper{ forward<T>(iterable) };
}

template<typename T, typename Iter = decltype(begin(declval<T>()))>
constexpr auto printer(T&& iterable) {
    struct iterator {
        Iter iter, ed;
        auto operator!=(const iterator& other) const {
            auto ret = (iter != other.iter);
            if(not ret) cout << '\n';
            return ret;
        }
        auto& operator++() { ++iter; if(iter != ed) cout << ' '; return *this; }
        auto& operator*() { return *iter; }
    };
    struct iterable_wrapper {
        T iterable;
        auto begin() const { return iterator{ std::begin(iterable), std::end(iterable) }; }
        auto end() const { return iterator{ std::end(iterable), std::end(iterable) }; }
    };
    return iterable_wrapper{ forward<T>(iterable) };
};

template<class ...T> void absorb(T&& ...) {}
template<size_t L, size_t I, class T>
bool zip_it_ne(const T& it1, const T& it2) {
    if(not (get<I>(it1) != get<I>(it2))) return false;
    if(I + 1 == L) return true;
    return zip_it_ne<L, (I + 1) % L, T>(it1, it2);
}
template<size_t ...Is, class T, class ...Cs,
    class Iter = tuple<decltype(begin(declval<Cs>()))...>,
    class Ref = tuple<decltype(*begin(declval<Cs>()))&...>
    >
constexpr auto zip(index_sequence<Is...>, T&& iterables, Cs&&...) {
    struct iterator {
        Iter iter;
        unique_ptr<Ref> tref = nullptr;
        bool operator!=(const iterator& other) const {
            return zip_it_ne<sizeof...(Is), 0, Iter>(iter, other.iter);
        }
        auto& operator++() { absorb(++get<Is>(iter)...); return *this; }
        auto& operator*() { tref.reset(new Ref(tie(*get<Is>(iter)...))); return *tref; }
    };
    struct iterable_wrapper {
        T iterables;
        auto begin() const { return iterator { Iter{ std::begin(get<Is>(iterables))... } }; }
        auto end() const { return iterator { Iter{ std::end(get<Is>(iterables))... } }; }
        auto size() const { return min({ get<Is>(iterables).size()... }); }
    };
    return iterable_wrapper{ forward<T>(iterables) };
}
template<class ...Cs, class = tuple<decltype(begin(declval<Cs>()))...>>
constexpr auto zip(Cs&& ...cs) {
    return zip(index_sequence_for<Cs...>{}, tuple<Cs...>(forward<Cs>(cs)...), forward<Cs>(cs)...);
}

template<typename T, typename Iter = decltype(begin(declval<T>()))>
constexpr auto enumerate(T&& iterable) {
    return zip(range(iterable.size()), forward<T>(iterable));
}

int main() {
    vector<int> v = {11, 22, 33, 44, 55, 66};

    for(const auto& i : printer(enumerate(zip(reversed(v), range(5, 20, 4))))) {
        int idx, a, b;
        pair<int, int> p;
        tie(idx, p) = i;
        tie(a, b) = p;
        cout << "(" << idx << ", " << a << ", " << b << ")";
    }

    auto r = range(5, 50, 7);
    auto x = *lower_bound(r.begin(), r.end(), 20);
    cout << x << endl;
    return 0;
}
