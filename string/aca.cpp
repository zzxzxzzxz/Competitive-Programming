#include <bits/stdc++.h>
using namespace std;

struct Node {
    int id;
    Node *fail;
    Node *next[26];

    Node(): id(-1), fail(NULL), next() {}
};

struct ACA {
    Node *root;

    ACA() {
        root = new Node();
    }

    void insert(const string& s, int id) {
        Node *p = root;
        for(int i = 0; i < int(s.size()); ++i)
        {
            int c = s[i] - 'a';
            if(p->next[c] == NULL) {
                p->next[c] = new Node();
            }
            p = p->next[c];
        }
        p->id = id;
    }

    void build_failure() {
        deque<Node*> que;
        for(int i = 0; i < 26; ++i) {
            if(root->next[i]) {
                (root->next[i])->fail = root;
                que.push_back(root->next[i]);
            }
        }
        while(not que.empty()) {
            Node* node = que.front();
            que.pop_front();
            for(int i = 0; i < 26; ++i) {
                if(node->next[i]) {
                    Node* fail = node->fail;
                    while(fail != root and fail->next[i] == NULL) {
                        fail = fail->fail;
                    }
                    if(fail->next[i]) {
                        node->next[i]->fail = fail->next[i];
                        //node->next[i]->cnt += fail->next[i]->cnt;
                    } else {
                        node->next[i]->fail = root;
                    }
                    que.push_back(node->next[i]);
                }
            }
        }
    }

    void search(const string& s, vector<pair<int, int>>& res) {
        Node *p = root;
        for(int i = 0; i < int(s.size()); ++i) {
            int c = s[i] - 'a';
            while(p != root and not p->next[c]) {
                p = p->fail;
            }
            if(p->next[c]) {
                p = p->next[c];
            } else {
                p = root;
            }
            auto q = p;
            if(q->id > -1) {
                res.push_back({q->id, i});
            }
            while(q->fail->id > -1) {
                q = q->fail;
                res.push_back({q->id, i});
            }
        }
    }
};

int main() {
    ACA t;
    vector<string> words = {"a", "b", "ab", "bc", "aab", "aac", "bd"};
    for(int i = 0; i < int(words.size()); ++i) {
        t.insert(words[i], i);
    }
    t.build_failure();

    vector<pair<int, int>> res;
    string s("aabd");
    t.search(s, res);

    cout << s << endl;
    for(auto it = res.begin(); it != res.end(); ++it) {
        auto [id, idx] = *it;
        int l = int(words[id].size());
        for(int i = 0; i < idx - l + 1; ++i) cout << " ";
        cout << words[id] << endl;
    }
    return 0;
}
