#include<bits/stdc++.h>

using namespace std;

int main() {
    string s;
    getline(cin, s);

    vector<int> nums;
    vector<char> ops;

    auto pop = [&]() {
        char op = ops.back();
        ops.pop_back();

        if(op == ')') {
            ops.pop_back();
            return;
        }

        int r = nums.back();
        nums.pop_back();
        int l = nums.back();
        nums.pop_back();

        if(op == '+') {
            nums.push_back(l + r);
        } else if(op == '-') {
            nums.push_back(l - r);
        } else if (op == '*') {
            nums.push_back(l * r);
        } else if (op == '/') {
            nums.push_back(l / r);
        } else if (op == '^') {
            int x = 1;
            for(int i = 0; i < r; i++) {
                x *= l;
            }
            nums.push_back(x);
        }
    };

    auto read_int = [&](int& i) {
        int x = 0;
        while(isdigit(s[i])) {
            x = x * 10 + int(s[i] - '0');
            ++i;
        }
        --i;
        nums.push_back(x);
    };

    auto prior = [](const char a, const char b) -> bool {
        map<char, int> pr = {{'+', 1}, {'-', 1}, {'*', 2}, {'/', 2}, {'^', 3}};
        map<char, int> pr_self = {{'^', 1}};
        if(pr[a] < pr[b]) {
            return false;
        } else if(pr[a] > pr[b]) {
            return true;
        }
        if(pr_self[a] == 1) {
            return false;
        }
        return true;
    };

    for(int i = 0; i < int(s.size()); ++i) {
        if(string("+-*/^").find(s[i]) != string::npos) {
            while(not ops.empty() and prior(ops.back(), s[i])) {
                pop();
            }
            ops.push_back(s[i]);

        } else if(isdigit(s[i])) {
            read_int(i);

        } else if(s[i] == '(') {
            ops.push_back('(');

        } else if(s[i] == ')') {
            while(ops.back() != '(') { pop(); }
            ops.pop_back();
        }
    }
    while(int(ops.size()) > 0) {
        pop();
    }
    cout << nums.front() << '\n';
    return 0;
}
