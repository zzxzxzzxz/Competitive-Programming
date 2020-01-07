//{{{
#include<bits/stdc++.h>
using namespace std;
template<class T>
void print(vector<T>&& data) {
    int n = int(data.size());
    for(int i = 0; i < n; ++i) { cout << data[i] << ((i == n - 1)? '\n' : ' '); }
}
inline void print() {putchar('\n');}
template<class T, class... U> inline void print(const T& head, const U&... tail) {
    cout << head;
    if(sizeof...(tail)) putchar(' ');
    print(tail...);
}
//}}}

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
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
