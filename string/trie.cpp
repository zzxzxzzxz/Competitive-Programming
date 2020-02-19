#include <bits/stdc++.h>
using namespace std;

struct TrieNode {
    array<TrieNode*, 26> next;
    bool is_end;
    TrieNode(): next({}), is_end(false) {}
};

struct Trie {
    TrieNode *root;
    Trie(): root(new TrieNode()) {}

    void insert(const string& s) {
        TrieNode* p = root;
        for(char c : s) {
            int i = c - 'a';
            if(p->next[i] == nullptr) {
                p->next[i] = new TrieNode();
            }
            p = p->next[i];
        }
        p->is_end = true;
    }

    bool search(const string& s) {
        TrieNode* p = root;
        for(char c : s) {
            int i = c - 'a';
            if(p->next[i]) {
                p = p->next[i];
            } else {
                return false;
            }
        }
        return p->is_end;
    }
};

int main() {
    Trie t;
    t.insert("abcd");
    t.insert("abce");
    cout << t.search("abc") << endl;
    cout << t.search("abf") << endl;
    cout << t.search("abce") << endl;
    cout << t.search("abcde") << endl;
    return 0;
}
