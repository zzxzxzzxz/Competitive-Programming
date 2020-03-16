#include <bits/stdc++.h>
using namespace std;

#define INF 0x3f3f3f3f

const int MOD = 1000000007;
#define MAX_N 105
struct edge {
    int to;
    int cost;
};

int N;
vector<edge> G[MAX_N];
int match[MAX_N];
int label[MAX_N];

void init() {
    memset(match, -1, sizeof(match));
    memset(label, 0, sizeof(label));
    for(int v = 1; v <= N; ++v) {
        for(auto ii = G[v].begin(); ii != G[v].end(); ++ii) {
            label[v] = max(label[v], ii->cost);
        }
    }
}

void update_labels(unordered_set<int>& S,
        unordered_set<int>& T,
        unordered_map<int, int>& nlS) {

    int delta = INT_MAX;
    unordered_map<int, int> new_nlS;
    for(auto ii = S.begin(); ii != S.end(); ++ii) {
        for(auto jj = G[*ii].begin(); jj != G[*ii].end(); ++jj) {
            if(T.find(jj->to) != T.end()) {
                continue;
            }
            int diff = label[*ii] + label[jj->to] - jj->cost;
            if(diff <= delta) {
                if(diff < delta) {
                    delta = diff;
                    new_nlS.clear();
                }
                new_nlS[jj->to] = *ii;
            }
        }
    }
    for(auto ii = T.begin(); ii != T.end(); ++ii) {
        label[*ii] += delta;
    }
    for(auto ii = S.begin(); ii != S.end(); ++ii) {
        label[*ii] -= delta;
    }
    nlS.insert(new_nlS.begin(), new_nlS.end());
}

int extend_aug_tree(unordered_set<int>& S,
        unordered_set<int>& T,
        unordered_map<int, int>& nlS) {
    auto ii = nlS.begin();
    while(T.find(ii->first) != T.end()) { ++ii; }
    int y = ii->first;
    T.insert(y);

    if(match[y] == -1) {
        return y;
    }

    int v = match[y];
    S.insert(v);
    for(auto jj = G[v].begin(); jj != G[v].end(); ++jj) {
        if(label[y] + label[jj->to] == jj->cost and nlS.find(jj->to) == nlS.end()) {
            nlS[jj->to] = v;
        }
    }
    return -1;
}

void increase_match(int u, int y, unordered_map<int, int>& nlS) {
    int v = nlS[y];
    while(v != u) {
        int tmp = match[v];
        match[v] = y;
        match[y] = v;
        y = tmp;
        v = nlS[y];
    }
    match[v] = y;
    match[y] = v;
}

void augment() {
    int u = 0;
    while(match[++u] != -1) {;}

    unordered_set<int> S = {u}, T;
    unordered_map<int, int> nlS;
    for(auto jj = G[u].begin(); jj != G[u].end(); ++jj) {
        if(label[u] + label[jj->to] == jj->cost) {
            nlS[jj->to] = u;
        }
    }

    int new_matched = -1;
    while(new_matched == -1) {
        if(int(T.size()) == int(nlS.size())) {
            update_labels(S, T, nlS);
        } else {
            new_matched = extend_aug_tree(S, T, nlS);
        }
    }

    increase_match(u, new_matched, nlS);
}

int hungarian() {
    init();

    for(int i = 0; i < N; ++i) {
        augment();
    }
    int ans = 0;
    for(int v = 1; v <= N; ++v) {
        auto ii = G[v].begin();
        while(ii->to != match[v]) { ++ii; }
        ans += ii->cost;
    }
    return ans;
}

int main() {
    vector<vector<int>> g = {
        {1, 5, 6}, {2, 5, 8},
        {2, 6, 6}, {3, 4, 4}
    };

    N = 3;
    for(int i = 0; i < int(g.size()); i++) {
        int u = g[i][0], v = g[i][1], cost = g[i][2];
        G[u].push_back(edge({v, cost}));
    }

    int mwm = hungarian();
    cout << mwm << endl;
    return 0;
}
