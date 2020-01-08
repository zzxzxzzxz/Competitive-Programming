#include<bits/stdc++.h>
using namespace std;

template<class T>
void print(const vector<T>& data) {
    int n = int(data.size());
    for(int i = 0; i < n; ++i) { cout << data[i] << ((i == n - 1)? '\n' : ' '); }
}
inline void print() {putchar('\n');}
template<class T, class... U> inline void print(const T& head, const U&... tail) {
    cout << head;
    if(sizeof...(tail)) putchar(' ');
    print(tail...);
}

struct Node {
    size_t sz;
    int pri, val, lazy;
    unique_ptr<Node> left, right;
    Node(int val): sz(1), pri(rand()), val(val), lazy(0) {}
    void pull() {
        sz = 1;
        if(left) { sz += left->sz; }
        if(right) { sz += right->sz; }
    }

    void push() {
        val = max(val, lazy);
        if(left) left->lazy = max(left->lazy, lazy);
        if(right) right->lazy = max(right->lazy, lazy);
        lazy = 0;
    }
};

using NodePtr = unique_ptr<Node>;

class Treap {
    private:
        NodePtr root;
        size_t size(NodePtr& node) {
            return node ? node->sz : 0;
        }
        array<NodePtr, 2> split(NodePtr& root, size_t k) {
            if(not root) {
                return {nullptr, nullptr};
            }
            NodePtr a, b;

            root->push();
            if(k <= size(root->left)) {
                tie(a, root->left) = split(root->left, k);
                b = move(root);
                b->pull();
            } else {
                size_t left_sz = size(root->left) + 1;
                tie(root->right, b) = split(root->right, k - left_sz);
                a = move(root);
                a->pull();
            }
            return {move(a), move(b)};
        }

        NodePtr merge(NodePtr& a, NodePtr& b) {
            if(not a or not b) {
                return a ? move(a) : move(b);
            }
            if(a->pri < b->pri) {
                a->push();
                a->right = merge(a->right, b);
                a->pull();
                return move(a);
            }
            b->push();
            b->left = merge(a, b->left);
            b->pull();
            return move(b);
        }

    public:
        void insert(int val, size_t k) {
            auto node = make_unique<Node>(val);
            auto [a, b] = split(root, k);
            b = merge(node, b);
            root = merge(a, b);
        }

        void add(int l, int r, int val) {
            NodePtr a, b, c;
            tie(a, b) = split(root, l);
            tie(b, c) = split(b, r - l);
            b->push();
            b->lazy = val;
            b = merge(b, c);
            root = merge(a, b);
        }

        template<class F> void dfs(int& idx, NodePtr& node, F f) {
            if(not node) return;
            node->push();
            dfs(idx, node->left, f);
            f(node->val, idx++);
            dfs(idx, node->right, f);
        }
        template<class F> void dfs(F f) {
            int idx = 0;
            dfs(idx, root ,f);
        }
};

size_t compress(vector<int>& nums, unordered_map<int, int>& dict, unordered_map<int, int>& idict) {
    sort(nums.begin(), nums.end());
    nums.erase(unique(nums.begin(), nums.end()), nums.end());
    for(size_t i = 0; i < nums.size(); ++i) {
        dict[nums[i]] = i;
        idict[i] = nums[i];
    }
    return nums.size();
}

class Solution {
public:
    vector<vector<int>> getSkyline(vector<vector<int>>& buildings) {
        Treap t;
        vector<int> xs;
        for(auto& b: buildings) {
            xs.push_back(b[0]);
            xs.push_back(b[1]);
        }
        unordered_map<int, int> dict, idict;
        int n = compress(xs, dict, idict);
        for(int i = 0; i < n; ++i) {
            t.insert(0, i);
        }

        for(auto& b: buildings) {
            t.add(dict[b[0]], dict[b[1]], b[2]);
        }

        vector<vector<int>> ans;
        int cur = 0;
        auto f = [&](const int val, const int idx) {
            if(cur != val) {
                cur = val;
                ans.push_back({idict[idx], val});
            }
        };
        t.dfs(f);
        return ans;
    }
};

/*
 * https://leetcode.com/problems/the-skyline-problem/
 */

int main() {
     vector<vector<int>> b = {{2, 9, 10}, {3, 7, 15}, {5, 12, 12}, {15, 20, 10}, {19, 24, 8}};
     Solution sol;
     auto ans = sol.getSkyline(b);
     for(auto& v: ans) {
         print(v[0], v[1]);
     }
    return 0;
}
