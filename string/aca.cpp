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
                root->nxt[i]->fail = root;
                root->nxt[i]->link = (root->id != -1) ? root : nullptr;
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
                    ptr->nxt[i]->link = (fl->nxt[i]->id != -1) ? fl->nxt[i] : fl->nxt[i]->link;
                    //ptr->nxt[i]->cnt += fail->nxt[i]->cnt;
                } else {
                    ptr->nxt[i]->fail = root;
                }
                que.push_back(ptr->nxt[i]);
            }
        }
    }

    auto search(const string& s, int n) {
        vector<vector<int>> res(n, vector<int>{});
        Node *p = root;
        for(int j = 0; j < int(s.size()); ++j) {
            int i = s[j] - 'a';
            while(p != root and not p->nxt[i]) {
                p = p->fail;
            }
            p = p->nxt[i] ? p->nxt[i] : root;

            if(p->id > -1) {
                res[p->id].push_back(j);
            }
            auto q = p->link;
            while(q != nullptr) {
                res[q->id].push_back(j);
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

    auto res = t.search(s, words.size());

    for(int id = 0; id < int(words.size()); ++id) {
        for(int idx : res[id]) {
            int l = int(words[id].size());
            for(int i = 0; i < idx - l + 1; ++i) cout << " ";
            cout << words[id] << endl;
        }
    }
    return 0;
}
