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

struct Person;

template<class T>
struct List {
    struct Node {
        T data;
        shared_ptr<Node> prv;
        shared_ptr<Node> nxt;

        Node(): data(), prv(nullptr), nxt(nullptr) {}
        Node(const T& data): data(data), prv(nullptr), nxt(nullptr) {}
    };

    struct iterator {
        shared_ptr<Node> ptr;
        iterator(): ptr(nullptr) {}
        iterator(shared_ptr<Node> ptr): ptr(ptr) {}
        shared_ptr<Node> operator->() { return ptr; };
        iterator operator++() { ptr = ptr->nxt; return *this; }
        iterator operator--() { ptr = ptr->prv; return *this; }
        friend bool operator==(const iterator& lhs, const iterator& rhs) { return lhs.ptr == rhs.ptr; }
        friend bool operator!=(const iterator& lhs, const iterator& rhs) { return not operator==(lhs, rhs); }

        iterator erase() {
            auto prv = ptr->prv;
            auto nxt = ptr->nxt;
            prv->nxt = nxt;
            nxt->prv = prv;
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

    shared_ptr<Node> head, tail;
    List() {
        head = make_shared<Node>();
        tail = make_shared<Node>();
        head->nxt = tail;
        tail->prv = head;
    }

    iterator begin() { return ++iterator(head); };
    iterator end() { return iterator(tail); }

    iterator push_back(const T& data) {
        shared_ptr<Node> node = make_shared<Node>(data);
        auto prv = tail->prv;
        prv->nxt = node;
        node->prv = prv;
        tail->prv = node;
        node->nxt = tail;
        return iterator(node);
    }
};

struct Person {
    string name;
    shared_ptr<List<Person>> children;
    Person(): name("") {}
    Person(const string& s): name(s) {
        children = make_shared<List<Person>>();
    }
};

class Monarchy {
    private:
        bool first = true;
        List<Person> dummy_list;
        List<Person>::iterator dummy;
        unordered_map<string, List<Person>::iterator> name_map;

        void dfs(List<Person>::iterator node, vector<string>& res) {
            res.push_back(node->data.name);
            auto& ch = node->data.children;
            for(auto it = ch->begin(); it != ch->end(); ++it) {
                dfs(it, res);
            }
        }

    public:
        void birth(const string& child, const string& parent) {
            print("birth:", child, parent);

            if(first) {
                first = false;
                dummy_list.push_back(Person(""));
                dummy = dummy_list.begin();

                name_map[parent] = dummy->data.children->push_back(Person(parent));
            }
            auto par = name_map[parent];
            name_map[child] = par->data.children->push_back(Person(child));
        }

        void death(const string& name) {
            print("death:", name);

            auto person = name_map[name];
            person.insert(person->data.children->begin(), person->data.children->end());
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
