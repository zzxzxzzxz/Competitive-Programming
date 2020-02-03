#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 300005;

vector<int> G[MAX_N];
int pos[MAX_N], vs[MAX_N], to[MAX_N];

void euler(int p, int v, int& sz) {
    pos[v] = sz;
    vs[sz] = v;
    ++sz;
    for(int u: G[v]) {
        if(u == p) continue;
        euler(v, u, sz);
        //vs[sz] = v;
        //++sz;
    }
    to[v] = sz;
}

int main() {
    cout << "          1" << endl;
    cout << "         / \\" << endl;
    cout << "        2   4" << endl;
    cout << "       / \\   \\" << endl;
    cout << "      3   5   7" << endl;
    cout << "     / \\" << endl;
    cout << "    6   8" << endl;
    cout << endl;

    int n = 8;
    vector<int> p = {1, 2, 1, 2, 3, 4, 3};
    for(int i = 2; i <= n; i++) {
        int u = i, v = p[i - 2];
        G[u].push_back(v);
        G[v].push_back(u);
    }

    int root = 1, sz = 0;
    euler(-1, root, sz);

    auto show = [](const int v) {
        cout << "children of " << v << ": ";
        for(int i = pos[v] + 1; i < to[v]; ++i) {
            cout << vs[i] << " ";
        }
        cout << endl;
    };
    show(1);
    show(2);
    show(3);
    show(4);
    return 0;
}
