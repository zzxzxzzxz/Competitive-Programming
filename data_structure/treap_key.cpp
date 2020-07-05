#include <bits/stdc++.h>
using namespace std;

mt19937 rng(123123123);
size_t seed = rng();

using DataType = int;
class Treap {//{{{
    private:
        struct Node {
            size_t sz;
            DataType val;
            Node* left;
            Node* right;
            Node(const DataType& v): sz(1), val(v), left(nullptr), right(nullptr) {}
            void pull() {
                sz = 1 + (left ? left->sz : 0) + (right ? right->sz : 0);
            };
            void push() {
            };
        };

        using NodePtr = Node*;
        NodePtr root;
        bool prior(NodePtr& node1, NodePtr& node2) {
            seed = 0xdefaced * seed + 1;
            size_t r = seed % (size(node1) + size(node2));
            return r < size(node1);
        }

        size_t size(NodePtr& node) {
            return node ? node->sz : 0;
        }

        pair<NodePtr, NodePtr> split(NodePtr& node, const DataType& val) {
            if(not node) {
                return { nullptr, nullptr };
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

        NodePtr unite(NodePtr& a, NodePtr& b) {
            if(not a or not b) {
                return a ? move(a) : move(b);
            }

            if(prior(a, b)) {
                NodePtr bl, br;
                tie(bl, br) = split(b, a->val);
                a->push();
                a->left = unite(a->left, bl);
                a->right = unite(a->right, br);
                a->pull();
                return move(a);
            } else {
                NodePtr al, ar;
                tie(al, ar) = split(a, b->val);
                b->push();
                b->left = unite(b->left, al);
                b->right = unite(b->right, ar);
                b->pull();
                return move(b);
            }
        }


    public:
        Treap(): root(nullptr) {}

        void insert(const DataType& val) {
            auto node = new Node(val);
            NodePtr a, b;
            tie(a, b) = split(root, val);
            a = merge(a, node);
            root = merge(a, b);
        }

        int count_ge(const DataType& val) {
            NodePtr a, b;
            tie(a, b) = split(root, val);
            int ans = size(b);
            root = merge(a, b);
            return ans;
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

        void unite(Treap& other) {
            root = unite(root, other.root);
            other.root = nullptr;
        }
};//}}}

int main(){
    Treap t;
    t.insert(2);
    t.insert(3);
    t.insert(4);

    cout << "[2, 3, 4]" << endl;
    for(int i = 0; i <= 6; ++i) {
        cout << i << ": " << t.count_ge(i) << endl;
    }
    Treap t2;
    for(int v : {1, 5, 6, 7}) {
        t2.insert(v);
    }
    cout << "unite t with t2([1, 5, 6, 7])" << endl;
    t.unite(t2);
    for(int i = 0; i <= 6; ++i) {
        cout << i << ": " << t.count_ge(i) << endl;
    }
    t.free();
    return 0;
}
