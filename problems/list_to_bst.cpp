//{{{
#pragma comment(linker, "/stack:200000000")
#pragma GCC optimize("O2")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

#include <bits/stdc++.h>
using namespace std;

#define putchar(x) cout << (x)
#define repeat(x) int _ = 0; _ < (x); ++_

#define SELECT(_1, _2, _3, _4, _5, _6, _7, _8, NAME,...) NAME
#define showvar(x) print_n(#x, "=", x);
#define dbg1(a) showvar(a) cout << endl;
#define dbg2(a, b) showvar(a) cout << ", "; dbg1(b);
#define dbg3(a, b, c) showvar(a) cout << ", "; dbg2(b, c);
#define dbg4(a, b, c, d) showvar(a) cout << ", "; dbg3(b, c, d);
#define dbg5(a, b, c, d, e) showvar(a) cout << ", "; dbg4(b, c, d, e);
#define dbg6(a, b, c, d, e, f) showvar(a) cout << ", "; dbg5(b, c, d, e, f);
#define dbg7(a, b, c, d, e, f, g) showvar(a) cout << ", "; dbg6(b, c, d, e, f, g);
#define dbg8(a, b, c, d, e, f, g, h) showvar(a) cout << ", "; dbg7(b, c, d, e, f, g, h);
#define debug(...) SELECT(__VA_ARGS__, dbg8, dbg7, dbg6, dbg5, dbg4, dbg3, dbg2, dbg1)(__VA_ARGS__)

template<typename T>
constexpr auto range(T start, T stop, T step) {
    struct iterator {
        using difference_type = T;
        using value_type = T;
        using pointer = T*;
        using reference = T&;
        using iterator_category = random_access_iterator_tag;

        T i, step;
        T operator-(const iterator& other) { return i - other.i; };
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
auto reversed(T&& iterable) {
    struct iterable_wrapper {
        T iterable;
        auto begin() const { return std::rbegin(iterable); }
        auto end() const { return std::rend(iterable); }
    };
    return iterable_wrapper{ forward<T>(iterable) };
}

template<typename T, typename Iter = decltype(begin(declval<T>()))>
constexpr auto printer(T&& iterable) {
    struct iterator {
        Iter iter, ed;
        auto operator!=(const iterator& other) {
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

template <size_t ...Is, typename T>
auto subarr(const T& t) { return tie(get<Is>(t)...); }

template<typename T, typename = void> struct is_container : false_type {};
template<typename T> struct is_container<T, void_t<decltype(begin(declval<T>()))>> : true_type {};
template<typename T> struct is_tuple : false_type {};
template<typename ...T> struct is_tuple<tuple<T...>> : true_type {};
template<typename T> struct is_pair : false_type {};
template<typename T, typename U> struct is_pair<pair<T, U>> : true_type {};

inline void print_n() {}
template<class T, class ...U> inline void print_n(const T& head, const U& ...args);

template<class T> inline void print_1(const T& x) {
    if constexpr(is_same<T, string>::value) {
        cout << x;
    } else if constexpr(is_tuple<T>::value) {
        apply([](const auto& ...ts) { print_n(ts...); }, x);
    } else if constexpr(is_pair<T>::value) {
        print_n(x.first, x.second);
    } else if constexpr(is_container<T>::value) {
        for(auto it = x.begin(); it != x.end(); ++it) { if(it != x.begin()) cout << ' '; print_1(*it); }
    } else {
        cout << x;
    }
}
template<class T, class ...U> void print_n(const T& head, const U& ...args) {
    print_1(head); ((cout << ' ', print_1(args)), ...);
}
template<class ...T> inline void print(const T& ...args) { print_n(args...); putchar('\n'); }
template<class ...T> void read(T& ...args) { (cin >> ... >> args); }

mt19937 rnd((random_device())());
//static int fastio = [](){ ios_base::sync_with_stdio(false); cin.tie(0); cout.precision(17); return 0; }();
//}}}
using PII = pair<int, int>;
using LL = long long;

const int MOD = 1e9 + 7;
const int INF = 0x3f3f3f3f;
const LL LLINF = 0x3f3f3f3f3f3f3f3f;
const int MAX_N = 300005;

struct Node {
    int val;
    Node *left, *right;
    Node(int val): val(val), left(0), right(0) {}
};

pair<Node*, Node*> balance_n(Node* node, int n) {
    if(n == 0) {
        return { nullptr, node };
    }
    auto [right, root] = balance_n(node, (n - 1) / 2);
    auto [left, tail] = balance_n(root->left, n - 1 - (n - 1) / 2);
    root->left = left;
    root->right = right;
    return {root, tail};
}

Node* balance(Node* root) {
    auto ptr = root;
    int n = 0;
    while(ptr) {
        ptr = ptr->left;
        ++n;
    }
    tie(root, ignore) = balance_n(root, n);
    return root;
}


void inorder(Node* node, int& pos, int depth, vector<array<int, 3>>& res) {
    if(not node) return;
    inorder(node->left, pos, depth + 1, res);
    res.push_back({node->val, depth, pos++});
    inorder(node->right, pos, depth + 1, res);
}

void plot(Node* root) {
    vector<array<int, 3>> dat;
    int C = 0;
    inorder(root, C, 0, dat);
    int R = 0;
    for(auto [val, r, c] : dat) {
        R = max(R, r + 1);
    }
    vector<vector<int>> grid(R, vector<int>(C, -1));
    for(auto [val, r, c] : dat) {
        grid[r][c] = val;
    }
    for(int i : range(R)) {
        for(int j : printer(range(C))) {
            if(grid[i][j] != -1) {
                printf("%2d", grid[i][j]);
            } else {
                printf("  ");
            }
        }
    }
}

pair<Node*, Node*> flatten1(Node* node) {
    if(not node) {
        return { nullptr, nullptr };
    }
    Node* head = node;
    Node* tail = node;
    if(node->right) {
        Node* tmp;
        tie(head, tmp) = flatten1(node->right);
        tmp->left = node;
    }
    if(node->left) {
        tie(node->left, tail) = flatten1(node->left);
    }
    return { head, tail };
}

Node* flatten(Node* root) {
    tie(root, ignore) = flatten1(root);
    return root;
}

int main() {
    int n = 31;
    vector<Node*> nodes(n);
    for(int i = 0; i < n; ++i) {
        nodes[i] = new Node(i);
    }
    for(int i = 1; i < n; ++i) {
        nodes[i]->left = nodes[i - 1];
    }
    auto root = nodes[n - 1];

    cout << "list ot bst:" << endl;
    root = balance(root);
    plot(root);

    cout << endl << endl;

    cout << "bst ot list:" << endl;
    root = flatten(root);

    while(root) {
        cout << root->val << " ";
        root = root->left;
    }
    cout << endl;
    return 0;
}
