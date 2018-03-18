#include <bits/stdc++.h>
using namespace std;

struct TrieNode {
    TrieNode *next[26];
    bool is_end;

    TrieNode() {
        memset(next, 0, sizeof(next));
        is_end = false;
    }
};

struct Trie {
    TrieNode *root;

    Trie() {
        root = new TrieNode();
    }

    void insert(const string& s)
    {
        TrieNode *p = root;
        for(int i = 0; i < s.size(); ++i)
        {
            int c = s[i] - 'a';
            if(p->next[c] == NULL) {
                p->next[c] = new TrieNode();
            }
            p = p->next[c];
        }
        p->is_end = true;
    }

    bool search(const string& s)
    {
        TrieNode *p = root;
        for(int i = 0; i < s.size(); ++i) {
            int c = s[i] - 'a';
            if(p->next[c]) {
                p = p->next[c];
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
    return 0;
}
