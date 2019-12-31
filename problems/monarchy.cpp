//{{{
#include<bits/stdc++.h>
using namespace std;
template<class T>
void print(vector<T>&& data) {
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

struct List {
    struct Node {
        string name;
        Node* prv;
        Node* nxt;
        List* children;

        Node(): name(""), prv(NULL), nxt(NULL), children(NULL) {}
        Node(const string& s): name(s), prv(NULL), nxt(NULL), children(new List()) {}
    };
    struct iterator {
        Node* ptr;
        iterator(): ptr(NULL) {}
        iterator(Node* ptr): ptr(ptr) {}
        Node* operator->() { return ptr; };
        iterator operator++() { ptr = ptr->nxt; return *this; }
        iterator operator--() { ptr = ptr->prv; return *this; }
        friend bool operator==(const iterator& lhs, const iterator& rhs) { return lhs.ptr == rhs.ptr; }
        friend bool operator!=(const iterator& lhs, const iterator& rhs) { return not operator==(lhs, rhs); }

        iterator erase() {
            auto prv = ptr->prv;
            auto nxt = ptr->nxt;
            prv->nxt = nxt;
            nxt->prv = prv;
            delete ptr;
            return iterator(nxt);
        }

        iterator insert(iterator start, iterator stop) {
            if(start == stop) {
                return *this;
            }
            auto prv = ptr->prv;
            auto last = stop->prv;
            ptr->prv = last;
            last->nxt = ptr;
            prv->nxt = start.ptr;
            start->prv = prv;
            return iterator(start.ptr);
        }
    };

    Node* head;
    Node* tail;
    List() {
        head = new Node();
        tail = new Node();
        head->nxt = tail;
        tail->prv = head;
    }

    iterator begin() { return ++iterator(head); };
    iterator end() { return iterator(tail); }

    iterator push_back(const string& s) {
        Node* node = new Node(s);
        auto prv = tail->prv;
        prv->nxt = node;
        node->prv = prv;
        tail->prv = node;
        node->nxt = tail;
        return iterator(node);
    }
};

class Monarchy {
    private:
        bool first = true;
        List dummy_list;
        List::iterator dummy;
        unordered_map<string, List::iterator> name_map;

        void dfs(List::iterator person, vector<string>& res) {
            res.push_back(person->name);
            auto ch = person->children;
            for(auto it = ch->begin(); it != ch->end(); ++it) {
                dfs(it, res);
            }
        }

    public:
        void birth(const string& child, const string& parent) {
            print("birth:", child, parent);

            if(first) {
                first = false;
                dummy_list.push_back("");
                dummy = dummy_list.begin();

                dummy->children->push_back(parent);
                name_map[parent] = --(dummy->children->end());
            }
            auto par = name_map[parent];
            par->children->push_back(child);
            name_map[child] = --(par->children->end());
        }

        void death(const string& name) {
            print("death:", name);
            auto person = name_map[name];
            person.insert(person->children->begin(), person->children->end());
            person.erase();
            name_map.erase(name);
        }

        vector<string> getOrderOfSuccession() {
            cout << "get: ";
            vector<string> ans;
            dfs(dummy, ans);
            ans.erase(ans.begin());
            return ans;
        }
};

int main() {
    Monarchy m;
    m.birth("a1", "king");
    m.birth("a2", "king");
    m.birth("b1", "a1");
    m.birth("b2", "a1");
    m.birth("a3", "king");
    m.birth("c1", "b1");
    m.birth("d1", "b2");
    m.birth("d2", "b2");
    m.birth("e1", "a2");
    m.birth("e2", "a2");
    print(m.getOrderOfSuccession());
    m.death("king");
    print(m.getOrderOfSuccession());
    m.birth("d3", "b2");
    m.death("b2");
    print(m.getOrderOfSuccession());
    m.death("a1");
    print(m.getOrderOfSuccession());
    m.death("e1");
    print(m.getOrderOfSuccession());
    return 0;
}
