#include <bits/stdc++.h>
using namespace std;

struct Node {
    int id;
    Node* fail;
    array<Node*, 26> next;

    Node(): id(-1), fail(nullptr), next({}) {}
};

struct ACA {
    Node *root;
    ACA(): root(new Node()) {}

    void insert(const string& s, int id) {
        Node* p = root;
        for(auto c : s) {
            int i = c - 'a';
            if(p->next[i] == NULL) {
                p->next[i] = new Node();
            }
            p = p->next[i];
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

    auto search(const string& s) {
        vector<pair<int, int>> res;
        Node *p = root;
        for(int j = 0; j < int(s.size()); ++j) {
            int i = s[j] - 'a';
            while(p != root and not p->next[i]) {
                p = p->fail;
            }
            if(p->next[i]) {
                p = p->next[i];
            } else {
                p = root;
            }
            auto q = p;
            if(q->id > -1) {
                res.push_back({q->id, j});
            }
            while(q->fail != NULL and q->fail->id > -1) {
                q = q->fail;
                res.push_back({q->id, j});
            }
        }
        return res;
    }
};

int main() {
    ACA t;
    vector<string> words = {"z", "y", "zy", "yx", "zzy", "zzx", "yw"};
    for(int i = 0; i < int(words.size()); ++i) {
        t.insert(words[i], i);
        if(i != 0) cout << ", ";
        cout << "\"" << words[i] << "\"";
    }
    cout << endl;
    t.build_failure();

    string s("wzzyww");
    auto res = t.search(s);

    cout << s << endl;
    for(auto it = res.begin(); it != res.end(); ++it) {
        auto [id, idx] = *it;
        int l = int(words[id].size());
        for(int i = 0; i < idx - l + 1; ++i) cout << " ";
        cout << words[id] << endl;
    }
    return 0;
}
