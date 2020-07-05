#include <bits/stdc++.h>
using namespace std;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
size_t seed = rng();

using DataType = int;
const DataType minval = INT_MIN;

class Treap {//{{{
    private:
        struct Node {
            size_t sz;
            DataType val, maxv, lazy;
            Node* left;
            Node* right;
            Node(const DataType& v): sz(1), val(v), maxv(minval),
                              lazy(), left(nullptr), right(nullptr) {}
            void add(DataType x) {
                val += x;
                maxv += x;
                lazy += x;
            }
            void pull() {
                sz = 1 + (left? left->sz : 0) + (right? right->sz : 0);
                maxv = max(
                    { val, left? left->maxv : minval, right? right->maxv : minval }
                );
            };
            void push() {
                if(left) left->add(lazy);
                if(right) right->add(lazy);
                lazy = {};
            };
        };
        using NodePtr = Node*;
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

        void insert(const DataType& val, const size_t k) {
            auto node = new Node(val);
            NodePtr a, b;
            tie(a, b) = split(root, k);
            a = merge(a, node);
            root = merge(a, b);
        }

        DataType query(const size_t l, const size_t r) {
            NodePtr a, b, c;
            tie(a, b) = split(root, l);
            tie(b, c) = split(b, r - l);

            DataType ans = b ? b->maxv : minval;

            b = merge(b, c);
            root = merge(a, b);
            return ans;
        }

        void add(const size_t l, const size_t r, const DataType& v) {
            NodePtr a, b, c;
            tie(a, b) = split(root, l);
            tie(b, c) = split(b, r - l);
            b->add(v);
            b = merge(b, c);
            root = merge(a, b);
        }

        void free() {
            auto f = [](auto self, const auto& node) {
                if(not node) {
                    return;
                }
                self(self, node->left);
                self(self, node->right);
                delete node;
            };
            f(f, root);
            root = nullptr;
        }
};//}}}

int main(){
    vector<int> v = {5, 3, 6, 4, 0, 7, 9, 1, 8, 2};
    int n = v.size();

    Treap t;
    for(int i = 0; i < n; ++i) {
        t.insert(v[i], i);
    }

    for(int j = 0; j < n; ++j) printf("%2d ", j); cout << endl;
    for(int j = 0; j < n; ++j) printf("%2d ", v[j]); cout << endl;

    cout << "add(0, 5, 5)" << endl;
    t.add(0, 5, 5);
    for(int j = 0; j < 5; ++j) v[j] += 5;

    for(int j = 0; j < n; ++j) printf("%2d ", j); cout << endl;
    for(int j = 0; j < n; ++j) printf("%2d ", v[j]); cout << endl;

    cout << "query(1, 5): " << t.query(1, 5) << endl;
    t.free();
    return 0;
}
