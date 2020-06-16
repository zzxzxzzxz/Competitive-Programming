/*{{{*/
#include "bits/stdc++.h"
using namespace std;

#define MT make_tuple
#define all(x) begin(x), end(x)
#define putchar(x) cout << (x)
static int fastio = [](){ ios_base::sync_with_stdio(false); cin.tie(0); cout.precision(17); return 0; }();
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

template<typename ...T> string format(const string& fmt, T&&... args) {
    size_t sz = snprintf(nullptr, 0, fmt.c_str(), args...) + 1;
    unique_ptr<char[]> buf(new char[sz]);
    snprintf(buf.get(), sz, fmt.c_str(), args...);
    return string(buf.get(), buf.get() + sz - 1);
}

template<class T> struct rge { T b, e; auto begin() const { return b; } auto end() const { return e; } };
template<class T> rge<T> range(T i, T j) { return rge<T>{i, j}; }
template<class T> auto dud(T* x) -> decltype(cerr << *x, 0);
template<class T> char dud(...);

struct debug {
#ifdef LOCAL
    debug(int line) {
        if(line) cerr << "LINE(" << line << ") -> ";
    }
    template<class T> typename enable_if<sizeof dud<T>(0) != 1, debug&>::type operator<<(T i) {
        cerr << boolalpha << i; return * this;
    }
    template<class T> typename enable_if<sizeof dud<T>(0) == 1, debug&>::type operator<<(T i) {
        return *this << range(begin(i), end(i));
    }
    template<class T, class U> debug& operator<<(pair<T, U> d) {
        return *this << "(" << d.first << ", " << d.second << ")";
    }
    debug& operator<<(tuple<>&) { return *this << "()"; };
    template<class ...T> debug& operator<<(tuple<T...> d) {
        *this << "("; debug_tuple<sizeof...(T), 0>(d);
        return *this << ")";
    }
    template<size_t L, size_t I, class T> void debug_tuple(const T& t) {
        *this << (I == 0 ? "" : ", ") << get<I>(t);
        if(I + 1 < L) debug_tuple<L, (I + 1) % L>(t);
    }
    template<class T> debug & operator <<(rge<T> d) {
        *this << "[";
        for(auto it = d.b; it != d.e; ++it)
            *this << (it != d.b ?  ", " : "") << *it;
        return *this << "]";
    }
    debug& operator<<(ostream&(*pf)(std::ostream&)) {
        cerr << pf; return *this;
    }
#else
    debug(int) {}
    template<class T> debug& operator<<(T&&) { return *this; }
    debug& operator<<(ostream&(*)(std::ostream&)) { return *this; }
#endif
};
#define imie(...) " [" << #__VA_ARGS__ << ": " << (__VA_ARGS__) << "] "

#define debug0()  debug(__LINE__)
#define debug1(x) debug(0)
#define GET_MACRO(_0, _1, NAME, ...) NAME
#define debug(...) GET_MACRO(_0, ##__VA_ARGS__, debug1, debug0)(__VA_ARGS__)
/*}}}*/
using LL = long long;

const int MOD = 1e9 + 7;
const int INF = 0x3f3f3f3f;
const LL LLINF = 0x3f3f3f3f3f3f3f3f;
const int MAX_N = 200005;

class LFUCache {
private:
    int capacity, sz, min_freq;
    unordered_map<int, list<pair<int, int>>> data; // frequency -> data
    unordered_map<int, int> freq; // key -> frequency
    unordered_map<int, list<pair<int, int>>::iterator> dict; // key -> iterator in data

    void remove(int key) {
        int f = freq[key];
        data[f].erase(dict[key]);
        if(data[f].empty()) {
            data.erase(f);
            if(f == min_freq) {
                ++min_freq;
            }
        }
        freq.erase(key);
        dict.erase(key);
    }

public:
    LFUCache(int capacity): capacity(capacity), sz(0), min_freq(0) {}

    int get(int key) {
        int f = freq[key];
        if(f == 0) {
            return -1;
        }
        int value = dict[key]->second;
        remove(key);

        freq[key] = ++f;
        data[f].emplace_front(key, value);
        dict[key] = data[f].begin();
        return value;
    }

    void put(int key, int value) {
        if(capacity == 0) {
            return;
        }

        int f = freq[key];
        if(f == 0) {
            if(sz == capacity) {
                remove(data[min_freq].back().first);
            } else {
                ++sz;
            }
            min_freq = 1;
        } else {
            remove(key);
        }

        freq[key] = ++f;
        data[f].emplace_front(key, value);
        dict[key] = data[f].begin();
    }
};

// https://leetcode.com/problems/lfu-cache/

int main() {
    auto cache = LFUCache(3);
    cache.put(2, 2);
    cache.put(1, 1);
    debug(0) << cache.get(2) << endl;
    debug(0) << cache.get(1) << endl;
    debug(0) << cache.get(2) << endl;
    cache.put(3, 3);
    cache.put(4, 4);
    debug(0) << cache.get(3) << endl;
    debug(0) << cache.get(2) << endl;
    debug(0) << cache.get(1) << endl;
    debug(0) << cache.get(4) << endl;
    return 0;
}
