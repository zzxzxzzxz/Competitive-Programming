/*{{{*/
#include "bits/stdc++.h"
using namespace std;

#define all(x) begin(x), end(x)
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
    template<class T, class U> debug& operator<<(pair<T, U> D) {
        return *this << "(" << D.first << ", " << D.second << ")";
    }
    template<class ...T> debug& operator<<(tuple<T...> D) {
        *this << "(";
        debug_tuple(*this, index_sequence_for<T...>{}, D);
        return *this << ")";
    }
    template<class T> debug & operator <<(rge<T> D) {
        *this << "[";
        for(auto it = D.b; it != D.e; ++it)
            *this << (it != D.b ?  ", " : "") << *it;
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

/*
 * N = 10000
 * D = 50
 * 1 <= A[i] <= 360 * 1e9
 */

void solve(int) {
    int N, D;
    cin >> N >> D;
    vector<LL> A(N);
    for(int i = 0; i < N; ++i) {
        cin >> A[i];
    }

    sort(all(A), greater<LL>());
    unordered_map<LL, vector<LL>> ids;

    size_t mx = 50;
    auto fac = [&](LL a) {
        for(LL i = 1; i <= min(a, LL(mx)); ++i) {
            if(a % i == 0 and ids[a / i].size() < mx) {
                ids[a / i].push_back(a);
            }
        }
    };

    for(int i = N - 1; i >= 0; --i) {
        fac(A[i]);
    }

    int ans = D - 1;
    for(auto& p : ids) {
        LL f = p.first;
        auto& v = p.second;
        sort(all(v));

        LL s = 0;
        for(int i = 0; i < N and s < D and A[i] >= f; ++i) {
            s += A[i] / f;
        }
        LL div = 1;
        if(s < D) {
            div = (D + s - 1) / s;
        }

        s = 0;
        int cost = 0;
        for(LL i : v) {
            int m = (i * div) / f;
            if(s + m <= D) {
                cost += m - 1;
                s += m;
                if(s >= D) {
                    break;
                }
            } else {
                cost += D - s;
                s += D - s;
            }
        }
        if(s < D) {
            cost += D - s;
        }
        ans = min(ans, cost);
    }
    cout << ans << endl;
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
