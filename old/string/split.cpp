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

#define MAX_N 50000

vector<string> split(const string& s, const string& delim) {
    vector<string> tokens;
    size_t start = 0;
    size_t end = s.find(delim, start);
    while(end != string::npos) {
        tokens.push_back(s.substr(start, end-start));
        start = end + delim.size();
        end = s.find(delim, start);
    }
    tokens.push_back(s.substr(start, s.size()-start));
    return move(tokens);
}

#include<omp.h>
int main()
{
    char s[100] = ",asdq,,dsgre,tjjjj,";
    vector<string> tokens = split(s, ",");
    REPIT(ii, tokens) {
        printf("\"%s\"\n", ii->c_str());
    }
    return 0;
}