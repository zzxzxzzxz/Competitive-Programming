#include <bits/stdc++.h>
using namespace std;

auto str_split(string_view strv, string_view delims = " \t") {
    vector<string_view> res;
    size_t prv = 0, idx;
    while((idx = strv.find_first_of(delims, prv)) != string_view::npos) {
        res.emplace_back(strv.substr(prv, idx - prv));
        prv = idx + 1;
    }
    res.emplace_back(strv.substr(prv));
    return res;
}

int main() {
    char s[100] = "asdq dsgre,tjj\tjj ";
    auto tokens = str_split(s);
    for(const auto& s: tokens) {
        cout << "\"" << s << "\"" << endl;
    }
    return 0;
}
