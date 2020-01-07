#include<bits/stdc++.h>
using namespace std;

struct Node {
    int idx, val;
    unique_ptr<Node> left, right;
    Node(int i, int v): idx(i), val(v) {}
};

template<class Cmp = less<>>
unique_ptr<Node> cartesian(vector<int>& v, Cmp cmp = Cmp()) {

    auto dummy = make_unique<Node>(-1, 0);
    vector<Node*> stack = {dummy.get()};

    for(size_t i = 0; i < v.size(); ++i) {
        auto node = make_unique<Node>(i, v[i]);
        auto node_ptr = node.get();

        while(stack.size() > 1 and not cmp(node->val, stack.back()->val)) {
            stack.pop_back();
        }
        auto cur = stack.back();
        if(cur->right) {
            node->left = move(cur->right);
        }
        cur->right = move(node);
        stack.push_back(node_ptr);
    }
    return move(dummy->right);
}

void dfs(unique_ptr<Node>& node) {
    if(not node) {
        return;
    }
    dfs(node->left);
    int l = (node->left) ? node->left->val : -1;
    int r = (node->right) ? node->right->val : -1;
    printf("%2d : %2d, %2d\n", node->val, l, r);
    dfs(node->right);
}

int main() {
    vector<int> v = {1, 14, 5, 0, 8};
    for(int i: v) {
        cout << i << " ";
    }
    cout << endl;
    auto root = cartesian(v);
    dfs(root);
    return 0;
}
