/*{{{*/
#include "bits/stdc++.h"
using namespace std;

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
    template<class T> debug& operator<<(T&&) { return *this; }
    debug& operator<<(ostream&(*pf)(std::ostream&)) { return *this; }
#endif
};
#define imie(...) " [" << #__VA_ARGS__ << ": " << (__VA_ARGS__) << "] "
/*}}}*/
using LL = long long;

const int MOD = 1e9 + 7;
const int INF = 0x3f3f3f3f;
const LL LLINF = 0x3f3f3f3f3f3f3f3f;
const int MAX_N = 200005;

size_t seed = rng();
template<class T> class Treap {//{{{
    private:
        struct Node {
            size_t sz;
            T val;
            unique_ptr<Node> left, right;
            Node(const T& v): sz(1), val(v) {}
            void pull() {
                sz = 1 + (left ? left->sz : 0) + (right ? right->sz : 0);
            };
            void push() {
            };
        };

        using NodePtr = unique_ptr<Node>;
        NodePtr root;
        bool prior(NodePtr& node1, NodePtr& node2) {
            seed = 0xdefaced * seed + 1;
            size_t r = seed % (node1->sz + node2->sz);
            return r < node1->sz;
        }

        size_t size(NodePtr& node) {
            return node ? node->sz : 0;
        }

        pair<NodePtr, NodePtr> split(NodePtr& node, const T& val) {
            if(not node) {
                return {nullptr, nullptr};
            }
            NodePtr a, b;
            if(val <= node->val) {
                b = move(node);
                b->push();
                tie(a, b->left) = split(b->left, val);
                b->pull();
            } else {
                a = move(node);
                a->push();
                tie(a->right, b) = split(a->right, val);
                a->pull();
            }
            return {move(a), move(b)};
        }

        NodePtr merge(NodePtr& a, NodePtr& b) {
            if(not a or not b) {
                return a ? move(a) : move(b);
            }

            if(prior(a, b)) {
                a->push();
                a->right = merge(a->right, b);
                a->pull();
                return move(a);
            } else {
                b->push();
                b->left = merge(a, b->left);
                b->pull();
                return move(b);
            }
        }

    public:
        Treap(): root(nullptr) {}

        void insert(const T& val) {
            auto node = make_unique<Node>(val);
            NodePtr a, b;
            tie(a, b) = split(root, val);
            a = merge(a, node);
            root = merge(a, b);
        }

        int count_ge(const T& val) {
            NodePtr a, b;
            tie(a, b) = split(root, val);
            int ans = b ? b->sz : 0;
            root = merge(a, b);
            return ans;
        }
};//}}}

void solve(int) {
    int N;
    LL H;
    cin >> N >> H;
    vector<int> A(N), B(N);
    for(int i = 0; i < N; ++i) {
        cin >> A[i];
    }
    for(int i = 0; i < N; ++i) {
        cin >> B[i];
    }

    int M = N / 2;

    vector<LL> sa1(1 << M, 0), sb1(1 << M, 0);
    for(int mask = 0; mask < (1 << M); ++mask) {
        for(int i = 0; i < M; ++i) {
            if(mask >> i & 1) {
                sa1[mask] += A[i];
                sb1[mask] += B[i];
            }
        }
    }
    vector<LL> sa2(1 << (N - M), 0), sb2(1 << (N - M), 0);
    for(int mask = 0; mask < (1 << (N - M)); ++mask) {
        for(int i = 0; i < (N - M); ++i) {
            if(mask >> i & 1) {
                sa2[mask] += A[M + i];
                sb2[mask] += B[M + i];
            }
        }
    }

    vector<int> idx1(1 << M), idx2(1 << (N - M));
    iota(all(idx1), 0);
    sort(all(idx1), [&](int i, int j) { return sa1[i] < sa1[j]; });
    iota(all(idx2), 0);
    sort(all(idx2), [&](int i, int j) { return sa2[i] > sa2[j]; });

    int all1 = (1 << M) - 1, all2 = (1 << (N - M)) - 1;
    LL ans = 0;
    auto treap = Treap<LL>();
    int j = 0;
    for(int mask1 : idx1) {
        while(j < (1 << (N - M)) and sa1[mask1] + sa2[idx2[j]] >= H) {
            int mask2 = idx2[j];

            treap.insert(sb2[all2]);
            for(int subm = mask2; subm > 0; subm = (subm - 1) & mask2) {
                treap.insert(sb2[all2 ^ subm]);
            }
            ++j;
        }

        ans += treap.count_ge(H - sb1[all1]);
        for(int subm = mask1; subm > 0; subm = (subm - 1) & mask1) {
            ans += treap.count_ge(H - sb1[all1 ^ subm]);
        }
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
