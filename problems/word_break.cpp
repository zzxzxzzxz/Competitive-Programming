#include <bits/stdc++.h>/*{{{*/
using namespace std;
template<class T> struct rge { T b, e; };
template<class T> rge<T> range(T i, T j) { return rge<T>{i, j}; }
template<class T> auto dud(T* x) -> decltype(cerr << *x, 0);
template<class T> char dud(...);
template<class ...T> void absorb(...) {}

struct debug {
    template<class T> typename enable_if<sizeof dud<T>(0) != 1, debug&>::type operator<<(T i) {
        cerr << boolalpha << i; return * this;
    }
    template<class T> typename enable_if<sizeof dud<T>(0) == 1, debug&>::type operator<<(T i) {
        return *this << range(begin(i), end(i));
    }
    debug& operator<<(string d) {
        cerr << "\"" << d << "\""; return *this;
    }
    template<class T, class U> debug& operator<<(pair<T, U> d) {
        return *this << "(" << d.first << ", " << d.second << ")";
    }
    template<class ...T> debug& operator<<(tuple<T...> d) {
        *this << "(";
        debug_tuple(*this, index_sequence_for<T...>{}, d);
        return *this << ")";
    }
    template<class T> debug & operator <<(rge<T> d) {
        *this << "[";
        for(auto it = d.b; it != d.e; ++it)
            *this << (it != d.b ?  ", " : "") << *it;
        return * this << "]";
    }
    debug& operator<<(ostream&(*pf)(std::ostream&)) {
        cerr << pf; return *this;
    }
    template<size_t ...Is, class T> void debug_tuple(index_sequence<Is...>, const T& t) {
        absorb((*this << (Is != 0 ? ", " : "") << get<Is>(t))...);
    }
};
#define imie(...) " [" << #__VA_ARGS__  << ": " << (__VA_ARGS__) << "] "

template<class...> struct types { using type = types; };
template<class Sig> struct args;
template<class R, class... Args> struct args<R(Args...)> : types<Args...> {};
template<class Sig> using args_t = typename args<Sig>::type;

template<typename T> struct is_vector : false_type {};
template<typename T> struct is_vector<vector<T>> : true_type {};

template<class T> auto read(istringstream& iss) {
    if constexpr(is_same_v<T, string>) {
        char c; iss >> c;
        string res;
        getline(iss, res, '"');
        return res;
    } else if constexpr(is_vector<T>::value) {
        T res;
        char c; iss >> c;
        while(c != ']') {
            auto tmp = read<typename T::value_type>(iss);
            res.push_back(tmp);
            iss >> c;
        }
        return res;
    } else {
        T res; iss >> res; return res;
    }
}

optional<tuple<>> read1() { return {{}}; }
template<class T, class ...U> optional<tuple<T, U...>> read1(T, U ...tail) {
    string s;
    getline(cin, s);
    if(cin.eof()) return {};
    auto iss = istringstream(s);
    auto t1 = make_tuple(read<T>(iss));
    auto t2 = read1(tail...);
    return { tuple_cat(t1, t2.value()) };
}

template<class ...T, class U = tuple<remove_reference_t<T>...>>
optional<U> parse_input(types<T...>) {
    return read1<remove_reference_t<T>...>( remove_reference_t<T>()... );
}/*}}}*/
using PII = pair<int, int>;
using LL = long long;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

struct Node {
    int len = 0, fail = 0, link = 0;
    array<int, 26> nxt = {};
};

class Solution {
private:
    const int root = 1;
    vector<Node> aca = vector<Node>(2, Node{});

    void insert(const string& s) {
        int p = root;
        for(size_t i = 0; i < s.size(); ++i) {
            int c = s[i] - 'a';
            if(aca[p].nxt[c] == 0) {
                aca[p].nxt[c] = aca.size();
                aca.push_back({});
            }
            p = aca[p].nxt[c];
        }
        aca[p].len = s.size();
    }

    void build() {
        queue<int> que;
        for(int c = 0; c < 26; ++c) {
            if(aca[root].nxt[c] != 0) {
                aca[aca[root].nxt[c]].fail = root;
                que.push(aca[root].nxt[c]);
            }
        }
        while(que.size()) {
            int p = que.front();
            que.pop();
            for(int c = 0; c < 26; ++c) {
                if(aca[p].nxt[c] != 0) {
                    int fail = aca[p].fail;
                    while(fail != root and aca[fail].nxt[c] == 0) {
                        fail = aca[fail].fail;
                    }
                    if(aca[fail].nxt[c] != 0) {
                        aca[aca[p].nxt[c]].fail = aca[fail].nxt[c];
                        if(aca[aca[fail].nxt[c]].len) {
                            aca[aca[p].nxt[c]].link = aca[fail].nxt[c];
                        } else {
                            aca[aca[p].nxt[c]].link = aca[aca[fail].nxt[c]].link;
                        }
                    } else {
                        aca[aca[p].nxt[c]].fail = root;
                    }
                    que.push(aca[p].nxt[c]);
                }
            }
        }
    }

    void search(const string& s, vector<char>& dp) {
        int p = root;
        for(size_t i = 0; i < s.size(); ++i) {
            int c = s[i] - 'a';
            while(p != root and aca[p].nxt[c] == 0) {
                p = aca[p].fail;
            }
            if(aca[p].nxt[c] != 0) {
                p = aca[p].nxt[c];
            }
            if(aca[p].len) {
                dp[i + 1] |= dp[i - aca[p].len + 1];
            }
            auto q = aca[p].link;
            while(q > 0) {
                dp[i + 1] |= dp[i - aca[q].len + 1];
                q = aca[q].link;
            }
        }
    }

public:
    bool wordBreak(string s, vector<string>& wordDict) {
        for(auto& word : wordDict) {
            insert(word);
        }
        build();
        vector<char> dp(s.size() + 1, false);
        dp[0] = true;
        search(s, dp);
        return dp[s.size()];
    }
};

bool wordBreak(string s, vector<string>& wordDict);
#define METHOD wordBreak

int main() {
    while(true) {
        auto input = parse_input(args_t<decltype(METHOD)>{});
        if(input == nullopt) break;
        auto sol = Solution();
        apply([&sol](auto ...args) { debug() << sol.METHOD(args...) << endl; }, input.value());
    }
    return 0;
}
