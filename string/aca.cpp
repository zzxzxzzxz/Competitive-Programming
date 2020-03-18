#include <bits/stdc++.h>
using namespace std;

struct Node {//{{{
    int id = -1;
    Node* fail = nullptr;
    Node* link = nullptr;
    array<Node*, 26> nxt = {};
};//}}}

struct ACA {//{{{
    Node *root;
    ACA(): root(new Node()) {}

    void insert(const string& s, int id) {
        Node* ptr = root;
        for(auto c : s) {
            int i = c - 'a';
            if(not ptr->nxt[i]) {
                ptr->nxt[i] = new Node();
            }
            ptr = ptr->nxt[i];
        }
        ptr->id = id;
    }

    void build_failure() {
        deque<Node*> que;
        for(int i = 0; i < 26; ++i) {
            if(root->nxt[i]) {
                (root->nxt[i])->fail = root;
                (root->nxt[i])->link = root;
                que.push_back(root->nxt[i]);
            }
        }
        while(not que.empty()) {
            Node* ptr = que.front();
            que.pop_front();

            for(int i = 0; i < 26; ++i) {
                if(not ptr->nxt[i]) {
                    continue;
                }
                Node* fl = ptr->fail;
                while(fl != root and not fl->nxt[i]) {
                    fl = fl->fail;
                }
                if(fl->nxt[i]) {
                    ptr->nxt[i]->fail = fl->nxt[i];
                    if(fl->nxt[i]->id != -1) {
                        ptr->nxt[i]->link = fl->nxt[i];
                    } else {
                        ptr->nxt[i]->link = fl->nxt[i]->link;
                    }
                    //ptr->nxt[i]->cnt += fail->nxt[i]->cnt;
                } else {
                    ptr->nxt[i]->fail = root;
                }
                que.push_back(ptr->nxt[i]);
            }
        }
    }

    auto search(const string& s) {
        vector<pair<int, int>> res;
        Node *p = root;
        for(int j = 0; j < int(s.size()); ++j) {
            int i = s[j] - 'a';
            while(p != root and not p->nxt[i]) {
                p = p->fail;
            }
            if(p->nxt[i]) {
                p = p->nxt[i];
            } else {
                p = root;
            }
            if(p->id > -1) {
                res.push_back({p->id, j});
            }
            auto q = p->link;
            while(q != root) {
                res.push_back({q->id, j});
                q = q->link;
            }
        }
        return res;
    }
};//}}}

int main() {
    ACA t;
    vector<string> words = {"a", "aa", "aaaa"};
    cout << "{";
    for(int i = 0; i < int(words.size()); ++i) {
        t.insert(words[i], i);
        if(i != 0) cout << ", ";
        cout << "\"" << words[i] << "\"";
    }
    cout << "}" << endl;
    t.build_failure();

    string s("aaaaaaa");
    cout << s << endl;

    auto res = t.search(s);

    for(auto it = res.begin(); it != res.end(); ++it) {
        auto [id, idx] = *it;
        int l = int(words[id].size());
        for(int i = 0; i < idx - l + 1; ++i) cout << " ";
        cout << words[id] << endl;
    }
    return 0;
}
