#include <bits/stdc++.h>
using namespace std;

#define MAX_N (1 << 20)

vector<vector<int>> G;
int sz = 0;
int from[MAX_N], to[MAX_N];

void euler(int v) {
    from[v] = sz;
    to[v] = sz;
    ++sz;

    for(auto ii = G[v].begin(); ii != G[v].end(); ++ii) {
        euler(*ii);
        to[v] = max(to[v], to[*ii]);
    }
}


int main()
{
    vector<pair<int, int>> edges = {
        {1, 2},
        {1, 3},
        {2, 4},
        {2, 5},
        {3, 6},
        {1, 7},
        {5, 8},
    };

    G.resize(10);
    for(auto e: edges) {
        G[e.first].push_back(e.second);
    }

    sz = 0;
    euler(1);

    vector<int> id(10);
    for(int i = 1; i <= 8; i++) {
        id[from[i]] = i;
    }
    for(int i = 0; i < 8; i++) {
        cout << i << " \n"[i == 7];
    }
    for(int i = 0; i < 8; i++) {
        cout << id[i] << " \n"[i == 7];
    }
    cout << endl;

    for(int i = 1; i <= 8; i++) {
        cout << i << " \n"[i == 8];
    }
    for(int i = 1; i <= 8; i++) {
        cout << from[i] << " \n"[i == 8];
    }
    for(int i = 1; i <= 8; i++) {
        cout << to[i] << " \n"[i == 8];
    }
    return 0;
}
