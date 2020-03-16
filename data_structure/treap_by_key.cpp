#include <bits/stdc++.h>
using namespace std;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
size_t seed = rng();

struct Node {//{{{
    size_t sz;
    int val;
    unique_ptr<Node> left, right;
    Node(int v): sz(1), val(v) {}
    void pull() {
        sz = 1;
        if(left) sz += left->sz;
        if(right) sz += right->sz;
    };
    void push() {
    };
};
using NodePtr = unique_ptr<Node>;
//}}}
class Treap {//{{{
    private:
        NodePtr root;
        bool prior(NodePtr& node1, NodePtr& node2) {
            seed = 0xdefaced * seed + 1;
            size_t r = seed % (node1->sz + node2->sz);
            return r < node1->sz;
        }

        size_t size(NodePtr& node) {
            return node ? node->sz : 0;
        }

        pair<NodePtr, NodePtr> split(NodePtr& root, const int val) {
            if(not root) {
                return {nullptr, nullptr};
            }
            NodePtr a, b;
            if(val <= root->val) {
                b = move(root);
                b->push();
                tie(a, b->left) = split(b->left, val);
                b->pull();
            } else {
                a = move(root);
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

        NodePtr unite(NodePtr& a, NodePtr& b) {
            if(not a or not b) {
                return a ? move(a) : move(b);
            }

            if(prior(a, b)) {
                auto [bl, br] = split(b, a->val);
                a->push();
                a->left = unite(a->left, bl);
                a->right = unite(a->right, br);
                a->pull();
                return move(a);
            } else {
                auto [al, ar] = split(a, b->val);
                b->push();
                b->left = unite(b->left, al);
                b->right = unite(b->right, ar);
                b->pull();
                return move(b);
            }
        }

        int kth(const NodePtr& node, const size_t k) {
            if(k == size(node->left)) {
                return node->val;
            } else if(k < size(node->left)) {
                return kth(node->left, k);
            } else {
                return kth(node->right, k - size(node->left) - 1);
            }
        }

        template<class F>
        void dfs(const NodePtr& node, const F& f) {
            if(not node) return;
            dfs(node->left, f);
            f(node->val);
            dfs(node->right, f);
        }

    public:
        Treap(): root(nullptr) {}

        void insert(const int val) {
            auto node = make_unique<Node>(val);
            auto [a, b] = split(root, val);
            a = merge(a, node);
            root = merge(a, b);
        }

        void unite(Treap& other) {
            root = unite(root, other.root);
        }

        int kth(const size_t k) {
            return kth(root, k);
        }

        template<class F>
        void dfs(const F& f) {
            dfs(root, f);
        }
};//}}}

int main(){
    vector<int> v1 = {15, 3, 16, 4, 10, 7, 19, 1, 8, 12};
    vector<int> v2 = {13, 6, 18, 9, 11, 0, 14, 2, 17, 5};

    Treap t1, t2;

    for(size_t i = 0; i < v1.size(); ++i) {
        t1.insert(v1[i]);
    }
    for(size_t i = 0; i < v2.size(); ++i) {
        t2.insert(v2[i]);
    }

    auto f = [](const int val) { printf("%2d ", val); };

    printf("t1: ");
    t1.dfs(f);
    putchar('\n');
    printf("4th: %d\n\n", t1.kth(4));

    printf("t2: ");
    t2.dfs(f);
    putchar('\n');
    printf("4th: %d\n\n", t2.kth(4));

    printf("unite t1 and t2\n\n");
    t1.unite(t2);

    printf("t1: ");
    t1.dfs(f);
    putchar('\n');
    printf("4th: %d\n\n", t1.kth(4));

    printf("t2: ");
    t2.dfs(f);
    putchar('\n');
    return 0;
}
