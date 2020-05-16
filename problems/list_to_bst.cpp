#include <bits/stdc++.h>
using namespace std;

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
    for(int i = 0; i < R; ++i) {
        for(int j = 0; j < C; ++j) {
            if(j == 0) putchar(' ');
            if(grid[i][j] != -1) {
                printf("%2d", grid[i][j]);
            } else {
                printf("  ");
            }
        }
        putchar('\n');
    }
}

pair<Node*, Node*> flatten1(Node* node) {
    Node* head = node;
    Node* tail = node;
    if(node->right) {
        Node* tmp;
        tie(head, tmp) = flatten1(node->right);
        tmp->left = node;
        node->right = nullptr;
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
