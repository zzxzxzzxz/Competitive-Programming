#include <bits/stdc++.h>
using namespace std;


vector<string> split(const string& s, const string& delim) {
    vector<string> tokens;
    size_t start = 0;
    //size_t end = s.find(delim, start);
    size_t end = s.find_first_of(delim);
    while(end != string::npos) {
        tokens.push_back(s.substr(start, end-start));
        //start = end + delim.size();
        //end = s.find(delim, start);
        start = end + 1;
        end = s.find_first_of(delim, start);
    }
    tokens.push_back(s.substr(start, s.size()-start));
    return tokens;
}


int main()
{
    char s[100] = ",;asdq,;dsgre,tjjjj,;";
    vector<string> tokens = split(s, ",;");
    for(auto ii = tokens.begin(); ii != tokens.end(); ++ii) {
        printf("\"%s\"\n", ii->c_str());
    }
    return 0;
}
