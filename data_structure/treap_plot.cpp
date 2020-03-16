#include <bits/stdc++.h>
using namespace std;

const string line(110, '-');

struct Node {
    size_t sz, pri;
    int idx, val, maxv, lazy;
    unique_ptr<Node> left, right;
    Node(int v, int idx): sz(1), pri(randpri()), idx(idx), val(v), maxv(val), lazy(0) {}

    size_t randpri() {
        static size_t x = 199412285566105;
        x = 0xdefaced * x + 1;
        return x;
    }

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

class Treap {
    private:
        NodePtr root;
        bool prior(NodePtr& node1, NodePtr& node2) {
            return node1->pri < node2->pri;
        }

        size_t size(NodePtr& node) {
            return node ? node->sz : 0;
        }

        pair<NodePtr, NodePtr> split(NodePtr& root, size_t k) {
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
        void insert(const int val, const int k) {
            auto node = make_unique<Node>(val, k);
            auto [a, b] = split(root, k);
            a = merge(a, node);
            root = merge(a, b);
        }

        int ask(int l, int r){
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
            printf("add (%d, %d) %d\n", l, r, v);
            cout << line << endl;

            draw({dfs(root)});

            NodePtr a, b, c;
            tie(a, b) = split(root, l);
            tie(b, c) = split(b, r - l);

            b->lazy += v;
            draw({dfs(a), dfs(b), dfs(c)});

            b = merge(b, c);
            root = merge(a, b);

            draw({dfs(root)});
        }

        void dfs(NodePtr& node, int &pos, int depth,
                vector<array<int, 6>>& res) {

            if(not node) {
                return;
            }
            dfs(node->left, pos, depth + 1, res);
            res.push_back({node->idx, node->val, node->lazy, node->maxv, depth, pos++});
            dfs(node->right, pos, depth + 1, res);
        }

        vector<vector<vector<int>>> dfs() {
            return dfs(root);
        }

        vector<vector<vector<int>>> dfs(NodePtr& node) {
            vector<array<int, 6>> res;
            int pos = 0;
            dfs(node, pos, 0, res);

            int n = res.size();
            vector<vector<vector<int>>> plot;

            for(auto& [i, v, l, m, d, p]: res) {
                while(int(plot.size()) <= d) {
                    plot.push_back(vector<vector<int>>(n));
                }
                plot[d][p] = {i, v, l, m};
            }
            return plot;
        }

        void draw(vector<vector<vector<vector<int>>>> plots) {
            size_t n = 0;
            for(auto& p: plots) {
                n = max(n, p.size());
            }
            for(auto& p: plots) {
                while(p.size() < n) {
                    p.push_back(vector<vector<int>>(p[0].size()));
                }
            }

            for(size_t i = 0; i < n; ++i) {
                for(size_t k = 0; k < plots.size(); ++k) {
                    if(k != 0) { printf(" | "); }
                    for(size_t j = 0; j < plots[k][0].size(); ++j) {
                        auto& v = plots[k][i][j];
                        if(not v.empty()) {
                            printf("%2d(%d,%d,%d) ", v[0], v[1], v[2], v[3]);
                        } else {
                            printf("          ");
                        }
                    }
                }
                putchar('\n');
            }
            cout << line << endl;
        }
};

int main() {
    vector<int> v = {1, 3, 2, 0, 2, 1, 2, 1, 1, 2};
    int n = v.size();

    Treap t;
    for(int i = 0; i < n; ++i) {
        t.insert(v[i], i);
    }
    t.add(3, 8, 1);
    return 0;
}
