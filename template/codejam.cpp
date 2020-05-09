/*{{{*/
#include "bits/stdc++.h"
using namespace std;

#define all(x) (x).begin(), (x).end()
#define putchar(x) cout << (x)
static int fastio = [](){ ios_base::sync_with_stdio(false); cin.tie(0); cout.precision(17); return 0; }();
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

template<class T> struct rge { T b, e; };
template<class T> rge<T> range(T i, T j) { return rge<T>{i, j}; }
template<class T> auto dud(T* x) -> decltype(cerr << *x, 0);
template<class T> char dud(...);

template<class ...T> void absorb(T&& ...) {}
template<class OUT, size_t ...Is, class T>
void debug_tuple(OUT& out, index_sequence<Is...>, const T& t) {
    absorb((out << (Is != 0 ? ", " : "") << get<Is>(t))...);
}

struct debug {
#ifdef LOCAL
	template<class T> typename enable_if<sizeof dud<T>(0) != 1, debug&>::type operator<<(T i) {
		cerr << boolalpha << i; return * this;
	}
	template<class T> typename enable_if<sizeof dud<T>(0) == 1, debug&>::type operator<<(T i) {
		return *this << range(begin(i), end(i));
	}
	template<class T, class U> debug& operator<<(pair<T, U> d) {
		return *this << "(" << d.first << ", " << d.second << ")";
	}
	template<class ...T> debug& operator<<(tuple<T...> d) {
        *this << "(";
        debug_tuple(*this, index_sequence_for<T...>{}, d);
        return *this << ")";
	}
    debug& operator<<(const tuple<>&) { return *this; }
	template<class T> debug & operator <<(rge<T> d) {
		*this << "[";
		for(auto it = d.b; it != d.e; ++it) {
            if(it != d.b) *this << ", "; *this << *it;
        }
		return * this << "]";
	}
    debug& operator<<(ostream&(*pf)(std::ostream&)) {
        cerr << pf; return *this;
    }
#else
    template<class T> debug& operator<<(T&&) { return *this; }
    debug& operator<<(ostream&(*pf)(std::ostream&)) { return *this; }
#endif
};
#define imie(x) " [" << #x ": " << (x) << "] "
/*}}}*/
using PII = pair<int, int>;
using LL = long long;

const int MOD = 1e9 + 7;
const int INF = 0x3f3f3f3f;
const LL LLINF = 0x3f3f3f3f3f3f3f3f;
const int MAX_N = 200005;

void solve(int) {
}

int main() {
    int T;
    cin >> T;
    for(int i = 1; i <= T; ++i) {
        cout << "Case #" << i << ": ";
        solve(i);
    }
    return 0;
}
