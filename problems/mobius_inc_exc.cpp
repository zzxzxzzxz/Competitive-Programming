//{{{
#pragma comment(linker, "/stack:200000000")
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

#include <bits/stdc++.h>
using namespace std;

#define putchar(x) cout << (x)
#define repeat(x) [[maybe_unused]] auto _: range(x)

template<typename T>
constexpr auto range(T start, T stop, T step) {
    struct iterator {
        T i, step;
        bool operator!=(const iterator& other) const { return i != other.i; }
        auto& operator++() { i += step; return *this; }
        auto& operator*() { return i; }
    };
    struct iterable_wrapper {
        T start, stop, step;
        auto begin() const { return iterator{start, step}; }
        auto end() const { return iterator{stop, step}; }
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

template<size_t ...Is, class Iter>
constexpr auto zip(index_sequence<Is...>, Iter be, Iter ed) {
    struct iterator {
        Iter iter;
        bool operator!=(const iterator& other) { return ((get<Is>(iter) != get<Is>(other.iter)) and ...); }
        auto& operator++() { ((++get<Is>(iter)), ...); return *this; }
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

template<typename T>
auto enumerate(T&& iterable) {
    return zip(range(iterable.size()), forward<T>(iterable));
}

template<typename T, typename TIter = decltype(begin(declval<T>())),
    typename = decltype(end(declval<T>()))>
constexpr auto printer(T&& iterable) {
    struct iterator {
        TIter iter, ed;
        auto operator!=(const iterator& other) {
            auto ret = (iter != other.iter);
            if(not ret) putchar('\n');
            return ret;
        }
        auto& operator++() { ++iter; if(iter != ed) cout << " "; return *this; }
        auto operator*() { return *iter; }
    };
    struct iterable_wrapper {
        T iterable;
        auto begin() const { return iterator{ iterable.begin(), iterable.end() }; }
        auto end() const { return iterator{ iterable.end(), iterable.end() }; }
    };
    return iterable_wrapper{ forward<T>(iterable) };
};

template <size_t ... Is, typename T>
auto tuple_slice(const T& t) { return tie(get<Is>(t)...); }

template<class ...T> void read(T& ...args) { (cin >> ... >> args); }
template<class T> inline void print_1(const T& x) { cout << x; }
template<class T> inline void print_1(const vector<T>& v) {
    for(auto it = v.begin(); it != v.end(); ++it) {
        if(it != v.begin()) putchar(' '); print_1(*it);
    }
}
template<class T, class ...U> void print_n(const T& head, const U& ...args) {
    print_1(head); ((cout << ' ' << args), ...);
}
template<class ...T> inline void print(const T& ...args) { print_n(args...); putchar('\n'); }

static int fastio = [](){ ios_base::sync_with_stdio(false); cin.tie(0); return 0; }();
//}}}
using PII = pair<int, int>;
using LL = long long;

const int MOD = 1e9 + 7;
const int INF = 1e9 + 10;
const LL LLINF = 1e18 + 1e10;
const int MAX_P = 100005;

bool composite[MAX_P];
int mu[MAX_P];
vector<int> primes;

void Sieve() {
    mu[1] = 1;
    for(int i = 2; i < MAX_P; ++i) {
        if(not composite[i]) {
            primes.push_back(i);
            mu[i] = -1;
        }
        for(int j = 0; j < int(primes.size()) and i * primes[j] < MAX_P; ++j) {
            composite[i * primes[j]] = true;
            if(i % primes[j] == 0) {
                mu[i * primes[j]] = 0;
                break;
            } else {
                mu[i * primes[j]] = mu[i] * mu[primes[j]];
            }
        }
    }
}

/*
 * https://codeforces.com/contest/803/problem/F
 */

LL mypow(LL x, LL p) {
    LL ret = 1;
    while(p) {
        if(p & 1) {
            ret = (ret * x) % MOD;
        }
        x = (x * x) % MOD;
        p >>= 1;
    }
    return ret;
}

int cnt[MAX_P];

int main()
{
    Sieve();
    int n;
    read(n);
    for(repeat(n)) {
        int a;
        read(a);
        cnt[a] += 1;
    }

    LL ans = 0;
    for(int i : range(1, 100001)) {
        int c = 0;
        for(int j : range(i, 100001, i)) {
            c += cnt[j];
        }
        ans = (ans + ((MOD + mu[i]) * (mypow(2, c) - 1)) % MOD) % MOD;
    }
    print(ans);
    return 0;
}
