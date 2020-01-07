//{{{
#include<bits/stdc++.h>
using namespace std;

template<class T>
void print(vector<T>& data) {
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

struct Node {
    array<shared_ptr<Node>, 256> nxt;
    vector<int> best;
};

class Trie {
    private:
        shared_ptr<Node> root = make_shared<Node>();
        shared_ptr<Node> ptr;
        string cur_str;
        vector<string> strs;
        vector<int> scores;
        unordered_map<string, int> id_map;

        int update(string& s, int score) {
            if(id_map.find(s) == id_map.end()) {
                id_map[s] = strs.size();
                strs.push_back(s);
                scores.push_back(0);
            }
            int id = id_map[s];
            scores[id] += score;
            return id;
        }

    public:
        Trie() {
            ptr = root;
            cur_str = "";
        }

        void insert(string&s, int score) {
            int id = update(s, score);
            auto node = root;
            for(int c: s) {
                if(not node->nxt[c]) {
                    node->nxt[c] = make_shared<Node>();
                }
                node = node->nxt[c];
                auto& best = node->best;
                best.push_back(id);
                sort(best.begin(), best.end(),
                        [&](const int i, const int j) {
                            if(scores[i] != scores[j]) {
                                return scores[i] > scores[j];
                            }
                            return strs[i] < strs[j];
                        }
                    );
                best.erase(unique(best.begin(), best.end()), best.end());
                if(best.size() > 3) {
                    best.pop_back();
                }
            }
        }

        void search(int c, vector<string>& res) {
            if(c == '#') {
                insert(cur_str, 1);
                ptr = root;
                cur_str = "";
                return;
            }
            cur_str.push_back(c);
            if(not ptr->nxt[c]) {
                ptr->nxt[c] = make_shared<Node>();
            }
            ptr = ptr->nxt[c];
            for(int id: ptr->best) {
                res.push_back(strs[id]);
            }
        }
};

class AutocompleteSystem {
    private:
        Trie trie;
    public:
        AutocompleteSystem(vector<string>& sentences, vector<int>& times) {
            int n = sentences.size();
            for(int i = 0; i < n; ++i) {
                trie.insert(sentences[i], times[i]);
            }
        }

        vector<string> input(char c) {
            vector<string> res;
            trie.search(c, res);
            return res;
        }
};

int main() {
    vector<string> data = {"i love you", "island", "ironman", "i love leetcode"};
    vector<int> times = {5, 3, 2, 2};
    AutocompleteSystem ats(data, times);
    string q = "i a#";
    for(char c: q) {
        auto res = ats.input(c);
        print(res);
    }
    return 0;
}
