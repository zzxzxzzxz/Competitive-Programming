#include <bits/stdc++.h>
using namespace std;

mt19937 rng(123123123);
size_t seed = rng();

template<class T> class Treap {//{{{
    private:
        struct Node {
            size_t sz;
            T val, maxv, lazy;
            unique_ptr<Node> left, right;
            Node(const T& v): sz(1), val(v), maxv(INT_MIN), lazy(0) {}

            void add(T x) {
                val += x;
                lazy += x;
            }

            void pull() {
                sz = 1;
                maxv = val;
                if(left) {
                    sz += left->sz;
                    maxv = max(maxv, left->maxv);
                }
                if(right) {
                    sz += right->sz;
                    maxv = max(maxv, right->maxv);
                }
            };

            void push() {
                if(left) left->add(lazy);
                if(right) right->add(lazy);
                lazy = 0;
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

        pair<NodePtr, NodePtr> split(NodePtr& node, size_t k) {
            if(not node) {
                return {nullptr, nullptr};
            }
            NodePtr a, b;
            if(k <= size(node->left)) {
                b = move(node);
                b->push();
                tie(a, b->left) = split(b->left, k);
                b->pull();
            } else {
                size_t left_sz = size(node->left) + 1;
                a = move(node);
                a->push();
                tie(a->right, b) = split(a->right, k - left_sz);
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

        void insert(const T& val, const size_t k) {
            auto node = make_unique<Node>(val);
            NodePtr a, b;
            tie(a, b) = split(root, k);
            a = merge(a, node);
            root = merge(a, b);
        }

        int ask(const size_t l, const size_t r) {
            NodePtr a, b, c;
            tie(a, b) = split(root, l);
            tie(b, c) = split(b, r - l);

            int ans = b ? b->maxv : INT_MIN;

            b = merge(b, c);
            root = merge(a, b);
            return ans;
        }

        void add(const size_t l, const size_t r, const T& v) {
            NodePtr a, b, c;
            tie(a, b) = split(root, l);
            tie(b, c) = split(b, r - l);
            b->add(v);
            b = merge(b, c);
            root = merge(a, b);
        }

        template<class F> void dfs(F f) {
            auto traverse = [](auto self, NodePtr& node, F f) {
                if(not node) return;
                self(self, node->left, f);
                f(node);
                self(self, node->right, f);
            };
            traverse(traverse, root, f);
        }
};//}}}

int main(){
    vector<int> v = {5, 3, 6, 4, 0, 7, 9, 1, 8, 2};
    int n = v.size();

    Treap<int> t;
    for(int i = 0; i < n; ++i) {
        t.insert(v[i], i);
    }

    auto f = [](const auto& node) {
        cout << node->val << " ";
    };
    t.dfs(f);
    cout << endl;

    for(int i = 0; i < 10; ++i) {
        int l = rng() % n, r = rng() % n;
        if(l > r) swap(l, r);
        if(i % 4) {
            printf("%3d  | ask(%2d, %2d)\n", t.ask(l, r + 1), l, r + 1);
        } else {
            printf("     | add(%2d, %2d, %2d)\n", l, r + 1, 5);
            t.add(l, r + 1, 5);
            for(int j = l; j <= r; ++j) v[j] += 5;
        }
        for(int j = 0; j < n; ++j) printf("%2d ", j); cout << endl;
        for(int j = 0; j < n; ++j) printf("%2d ", v[j]); cout << endl;
        cout << endl;
    }

    return 0;
}
