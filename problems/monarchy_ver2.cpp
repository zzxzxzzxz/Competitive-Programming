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
    struct Node : public std::enable_shared_from_this<Node> {
        string name;
        shared_ptr<Node> prv, nxt;
        unique_ptr<List> children;

        Node(): name(""), prv(nullptr), nxt(nullptr), children(nullptr) {}
        Node(const string& s): name(s), prv(nullptr), nxt(nullptr), children(make_unique<List>()) {}

        shared_ptr<Node> erase() {
            auto prv = this->prv;
            auto nxt = this->nxt;
            prv->nxt = nxt;
            nxt->prv = prv;
            return nxt;
        }

        shared_ptr<Node> insert(shared_ptr<Node> start, shared_ptr<Node> stop) {
            if(start == stop) {
                return shared_from_this();
            }
            auto prv = this->prv;
            auto last = (stop) ? stop->prv : start;
            this->prv = last;
            last->nxt = shared_from_this();
            prv->nxt = start;
            start->prv = prv;
            return start;
        }

        shared_ptr<Node> insert(shared_ptr<Node> start) {
            return insert(start, start->nxt);
        }
    };

    shared_ptr<Node> head, tail;

    List() {
        head = make_shared<Node>();
        tail = make_shared<Node>();
        head->nxt = tail;
        tail->prv = head;
    }

    shared_ptr<Node> begin() { return head->nxt; };
    shared_ptr<Node> end() { return tail; }

    shared_ptr<Node> push_back(const string& s) {
        shared_ptr<Node> node = make_shared<Node>(s);
        return tail->insert(node);
    }
};

class Monarchy {
    private:
        bool first = true;
        List dummy_list;
        shared_ptr<List::Node> dummy;
        unordered_map<string, shared_ptr<List::Node>> name_map;

        void dfs(shared_ptr<List::Node> person, vector<string>& res) {
            res.push_back(person->name);
            auto& ch = person->children;
            for(auto ptr = ch->begin(); ptr != ch->end(); ptr = ptr->nxt) {
                dfs(ptr, res);
            }
        }

    public:
        void birth(const string& child, const string& parent) {
            print("birth:", child, parent);

            if(first) {
                first = false;
                dummy_list.push_back("");
                dummy = dummy_list.begin();
                name_map[parent] = dummy->children->push_back(parent);
            }
            auto par = name_map[parent];
            name_map[child] = par->children->push_back(child);
        }

        void death(const string& name) {
            print("death:", name);

            auto person = name_map[name];
            person->insert(person->children->begin(), person->children->end());
            person->erase();
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
