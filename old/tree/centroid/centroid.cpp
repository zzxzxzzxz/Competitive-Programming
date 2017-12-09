#include <bits/stdc++.h>
using namespace std;

#define GET_MACRO(_1,_2,_3,_4,NAME,...) NAME
#define REP2(i,n) for(int i=0;i<(int)(n);i++)
#define REP3(i,m,n) for(int i=m;i<(int)(n);i++)
#define REP4(i,m,n,s) for(int i=m;(s>0 and i<(int)(n)) or (s<0 and i>(int)(n));i+=s)
#define REP(...) GET_MACRO(__VA_ARGS__, REP4, REP3, REP2)(__VA_ARGS__)
#define REPIT(i,c) for(__typeof((c).begin()) i=(c).begin();i!=(c).end();i++)
#define PIS(x) printf("%d ",x)
#define PRINTIA(a,n) REP(i,n){printf("%d ", *((a)+i));}putchar('\n');
#define PN() putchar('\n')
#define MP make_pair
#define PB push_back

typedef pair<int,int> PII;
typedef long long LL;
typedef unsigned long long ULL;

void RI() {}
template<typename... T>
void RI( int& head, T&... tail ) {
    scanf("%d",&head);
    RI(tail...);
}
void PI() {putchar('\n');}
template<typename... T>
void PI(const int head, T... tail ) {
    printf("%d ", head);
    PI(tail...);
}

#define MAX_N 10005

struct edge {
    int to, length;
};
int N, K;
vector<edge> G[MAX_N];

bool centroid[MAX_N];
int subtree_size[MAX_N];

int ans;

int compute_subtree_size(int v, int p) {
    int c = 1;
    for(int i = 0; i < (int)G[v].size(); i++) {
        int w = G[v][i].to;
        if(w == p or centroid[w])
            continue;
        c += compute_subtree_size(G[v][i].to, v);
    }
    subtree_size[v] = c;
    return c;
}

pair<int, int> search_centroid(int v, int p, int t) {
    pair<int, int> res = make_pair(INT_MAX, -1);
    int s = 1, m = 0;
    for(int i = 0; i < (int)G[v].size(); i++) {
        int w = G[v][i].to;
        if(w == p or centroid[w])
            continue;
        res = min(res, search_centroid(w, v, t));
        m = max(m, subtree_size[w]);
        s += subtree_size[w];
    }
    m = max(m, t-s);
    res = min(res, make_pair(m, v));
    return res;
}

void enumerate_paths(int v, int p, int d, vector<int>& ds) {
    ds.push_back(d);
    for(int i = 0; i < (int)G[v].size(); i++) {
        int w = G[v][i].to;
        if(w == p or centroid[w])
            continue;
        enumerate_paths(w, v, d + G[v][i].length, ds);
    }
}

int count_pairs(vector<int>& ds) {
    int res = 0;
    sort(ds.begin(), ds.end());
    int j = ds.size();
    for(int i = 0; i < (int)ds.size(); i++) {
        while(j > 0 and ds[i] + ds[j - 1] > K)
            --j;
        res += j - (j > i ? 1 : 0);
    }
    return res / 2;
}

void solve_subproblem(int v) {
    compute_subtree_size(v, -1);
    int s = search_centroid(v, -1, subtree_size[v]).second;
    centroid[s] = true;

    for(int i = 0; i < (int)G[s].size(); i++) {
        if(centroid[G[s][i].to])
            continue;
        solve_subproblem(G[s][i].to);
    }

    vector<int> ds;
    ds.push_back(0);
    for(int i = 0; i < (int)G[s].size(); i++) {
        if(centroid[G[s][i].to])
            continue;
        vector<int> tds;
        enumerate_paths(G[s][i].to, s, G[s][i].length, tds);

        ans -= count_pairs(tds);
        ds.insert(ds.end(), tds.begin(), tds.end());
    }

    ans += count_pairs(ds);
    centroid[s] = false;
}

void solve() {
    ans = 0;
    solve_subproblem(0);
    printf("%d\n", ans);
}

int main()
{
    while(true) {
        scanf("%d%d", &N, &K);
        if(N == 0 and K == 0)
            break;
        for(int i = 0; i < N-1; i++) {
            int a, b, l;
            scanf("%d%d%d", &a, &b, &l);
            a--; b--;
            G[a].push_back(edge{b, l});
            G[b].push_back(edge{a, l});
        }
        solve();

        for(int i = 0; i < MAX_N; i++) {
            G[i].clear();
        }
        memset(subtree_size, 0, sizeof(subtree_size));
        memset(centroid, false, sizeof(centroid));
    }
    return 0;
}
