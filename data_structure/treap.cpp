#include <bits/stdc++.h>
using namespace std;

struct Node {
    size_t sz;
    int val, maxv, lazy;
    unique_ptr<Node> left, right;
    Node(int v): sz(1), val(v), maxv(INT_MIN), lazy(0) {}
    void pull() {
        sz = 1;
        maxv = val;
        if(left) {
            sz += left->sz;
            maxv = max(maxv, left->maxv + left->lazy);
        }
        if(right) {
            sz += right->sz;
            maxv = max(maxv, right->maxv + right->lazy);
        }
    };
    void push() {
        val += lazy;
        if(left) left->lazy += lazy;
        if(right) right->lazy += lazy;
        lazy = 0;
    };
};

using NodePtr = unique_ptr<Node>;

class Treap{
    private:
        NodePtr root;
        size_t seed;
        bool prior(NodePtr& node1, NodePtr& node2) {
            seed = 0xdefaced * seed + 1;
            size_t r = seed % (node1->sz + node2->sz);
            return r < node1->sz;
        }

        size_t size(NodePtr& node) {
            return node ? node->sz : 0;
        }

        array<NodePtr, 2> split(NodePtr& root, size_t k) {
            if(not root) {
                return {nullptr, nullptr};
            }
            NodePtr a, b;

            if(k <= size(root->left)) {
                b = move(root);
                b->push();
                tie(a, b->left) = split(b->left, k);
                b->pull();
            } else {
                size_t left_sz = size(root->left) + 1;
                a = move(root);
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

            NodePtr ret = nullptr;
            if(prior(a, b)) {
                a->push();
                a->right = merge(a->right, b);
                a->pull();
                ret = move(a);
            } else {
                b->push();
                b->left = merge(a, b->left);
                b->pull();
                ret = move(b);
            }
            return ret;
        }

    public:
        Treap(size_t seed = 0): root(nullptr), seed(seed) {}

        void insert(const int val, const int k) {
            auto node = make_unique<Node>(val);
            auto [a, b] = split(root, k);
            a = merge(a, node);
            root = merge(a, b);
        }

        int ask(int l, int r) {
            NodePtr a, b, c;
            tie(a, b) = split(root, l);
            tie(b, c) = split(b, r - l);

            int ans = INT_MIN;
            if(b) {
                b->push();
                ans = b->maxv;
            }
            b = merge(b, c);
            root = merge(a, b);
            return ans;
        }

        void add(int l, int r, int v) {
            NodePtr a, b, c;
            tie(a, b) = split(root, l);
            tie(b, c) = split(b, r - l);
            b->lazy += v;
            b = merge(b, c);
            root = merge(a, b);
        }

        void dfs(NodePtr& node) {
            if(not node) {
                return;
            }
            dfs(node->left);
            printf("%2d ", node->val);
            dfs(node->right);
        }
        void dfs() {
            dfs(root); putchar('\n');
        }
};

int main(){
    vector<int> v = {5, 3, 6, 4, 0, 7, 9, 1, 8, 2};
    int n = v.size();

    random_device rd;
    mt19937 mt(rd());
    uniform_int_distribution<size_t> dist(0, SIZE_MAX);
    Treap t(dist(mt));

    for(int i = 0; i < n; ++i) {
        t.insert(v[i], i);
    }
    t.dfs();

    for(int i = 0; i < 10; ++i) {
        int l = dist(mt) % n, r = dist(mt) % n;
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
