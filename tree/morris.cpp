#include<bits/stdc++.h>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

void dfs(TreeNode* node) {
    TreeNode *cur = node, *ptr;
    while(cur != nullptr) {
        if(cur->left) {
            ptr = cur->left;
            while(ptr->right != nullptr and ptr->right != cur) {
                ptr = ptr->right;
            }
            if(ptr->right == nullptr) {
                ptr->right = cur;
                cur = cur->left;
            } else {
                ptr->right = nullptr;
                cout << cur->val << " ";
                cur = cur->right;
            }
        } else {
            cout << cur->val << " ";
            cur = cur->right;
        }
    }
    cout << endl;
}

int main() {
    vector<TreeNode*> node;
    for(int i = 0; i <= 10; ++i) {
        node.push_back(new TreeNode(i));
    }
    node[2]->left = node[1];
    node[2]->right = node[5];
    node[3]->right = node[4];
    node[5]->left = node[3];
    node[6]->left = node[2];
    node[6]->right = node[8];
    node[8]->left = node[7];
    node[8]->right = node[10];
    node[10]->left = node[9];
    dfs(node[6]);
    return 0;
}
