#include <bits/stdc++.h>
using namespace std;

template<class T>
struct SBTree {
    struct Node {
        Node* child[2];
        Node* parent;
        size_t sz;
        T data;
        Node(const T& data, Node* p, Node* ch0, Node* ch1):
            child{ch0, ch1}, parent(p), sz(1), data(data) {}
        Node(): parent(nullptr), sz(0) {
            child[0] = this;
            child[1] = this;
        }
    } *nil, *root, *_end, *_begin;

    struct iterator {
        using difference_type = int;
        using value_type = T;
        using pointer = T*;
        using reference = T&;
        using iterator_category = random_access_iterator_tag;

        using Node = typename SBTree::Node;
        SBTree* tree;
        Node* node;
        iterator(): tree(nullptr), node(nullptr) {}
        iterator(SBTree* tree, Node* node): tree(tree), node(node) {}
        reference operator*() const { return node->data; }
        pointer operator->() { return &(node->data); }
        iterator& increment(bool rev = false) {
            if(node->child[!rev]->sz) {
                node = node->child[!rev];
                while(node->child[rev]->sz) {
                    node = node->child[rev];
                }
            } else {
                while(node->parent and node->parent->child[rev] != node) {
                    node = node->parent;
                }
                node = node->parent;
            }
            return *this;
        }
        iterator& operator++() { return increment(false); }
        iterator operator++(int) { iterator tmp(tree, node); operator++(); return tmp; }
        iterator& operator--() { return increment(true); }
        iterator operator--(int) { iterator tmp(node); operator--(); return tmp; }
        iterator& operator+=(const int& n) {
            this->node = tree->kth(tree->rank(node->data) + n).node;
            return *this;
        }
        iterator& operator-=(const int& n) { return operator+=(-n); }
        friend iterator operator+(iterator lhs, const int& n) { lhs += n; return lhs; };
        friend iterator operator-(iterator lhs, const int& n) { lhs -= n; return lhs; };
        friend int operator-(iterator lhs, const iterator& rhs) {
            return lhs.tree->rank(lhs) - lhs.tree->rank(rhs);
        };
        friend bool operator==(const iterator& lhs, const iterator& rhs) { return lhs.node == rhs.node; }
        friend bool operator!=(const iterator& lhs, const iterator& rhs) { return not operator==(lhs, rhs); }
    };
    typedef const iterator const_iterator;

    void rotate(Node*& node, bool d) {
        Node* tmp = node->child[!d];
        tmp->parent = node->parent;

        node->child[!d] = tmp->child[d];
        node->child[!d]->parent = node;

        tmp->child[d] = node;
        tmp->child[d]->parent = tmp;

        tmp->sz = node->sz;
        node->sz = node->child[0]->sz + node->child[1]->sz + 1;

        node = tmp;
    }

    void maintain(Node*& node, bool d){
        if(node->child[d]->child[d]->sz > node->child[!d]->sz){
            rotate(node, !d);
        } else if(node->child[d]->child[!d]->sz > node->child[!d]->sz) {
            rotate(node->child[d], d);
            rotate(node, !d);
        } else {
            return;
        }
        maintain(node->child[1], 1);
        maintain(node->child[0], 0);
        maintain(node, 1);
        maintain(node, 0);
    }

    iterator insert(Node*& node, const T& data, Node* parent) {
        if(!node->sz) {
            node = new Node(data, parent, nil, nil);
            return iterator(this, node);
        }
        ++(node->sz);
        auto ii = insert(node->child[node->data < data], data, node);
        maintain(node, node->data < data);
        return ii;
    }

    bool erase(Node*& node, const T& data) {
        if(!node->sz) {
            return false;
        }
        if(node->data == data) {
            if(!node->child[1]->sz) {
                Node* tmp = node;
                node = node->child[0];
                if(node->sz) {
                    node->parent = tmp->parent;
                }
                delete tmp;
            } else {
                --(node->sz);
                Node* min_node = node->child[1];
                while(min_node->child[0]->sz) {
                    min_node = min_node->child[0];
                }
                node->data = min_node->data;
                erase(node->child[1], min_node->data);
            }
            return true;
        } else if(erase(node->child[node->data < data], data)) {
            --(node->sz);
            return true;
        }
        return false;
    }

    void clear(Node*& node) {
        if(node->sz) {
            clear(node->child[0]);
            clear(node->child[1]);
            delete node;
        }
    }

    iterator find(const T& data) {
        Node *node = root;
        while(node->sz and node->data != data) {
            node = node->child[node->data < data];
        }
        if(node->sz) {
            return iterator(this, node);
        }
        return end();
    }

    int rank(const T& data) {
        int cnt = 0;
        Node* node = root;
        while(node->sz) {
            if(node->data < data) {
                cnt += node->child[0]->sz + 1;
                node = node->child[1];
            } else if(node->data > data) {
                node = node->child[0];
            } else {
                cnt += node->child[0]->sz;
                return cnt;
            }
        }
        return -1;
    }

    int rank(const_iterator& ii) {
        if(ii == end()) {
            return root->sz;
        }
        return rank(ii.node->data);
    }

    iterator kth(int k) {
        Node* node = root;
        while(node->sz) {
            if(k < int(node->child[0]->sz)) {
                node = node->child[0];
            } else if(k == int(node->child[0]->sz)) {
                return iterator(this, node);
            } else {
                k -= node->child[0]->sz + 1;
                node = node->child[1];
            }
        }
        return end();
    }

    void maintain_begin() {
        _begin = _end;
        while(_begin->child[0]->sz) {
            _begin = _begin->child[0];
        }
    }

    iterator insert(const T& data) {
        auto ii = find(data);
        if(ii == end()) {
            ii = insert(root, data, _end);
            _end->child[0] = root;
            if(_begin == _end or data < _begin->data) {
                maintain_begin();
            }
        }
        return ii;
    }

    bool erase(const T& data) {
        bool new_begin = (data == _begin->data);
        bool succ = erase(root, data);
        _end->child[0] = root;
        if(succ and new_begin) {
            maintain_begin();
        }
        return succ;
    }

    bool erase(const iterator& ii) {
        return erase(root, *ii);
    }

    void clear() {
        clear(root);
        root = nil;
        _end->child[0] = nil;
        _begin = _end;
    }

    bool empty() {
        return root->sz == 0;
    }

    size_t size() {
        return root->sz;
    }

    SBTree(): nil(new Node), root(nil), _end(new Node(T(), nullptr, root, nil)), _begin(_end) {}
    SBTree(const initializer_list<T>& init) {
        new (this) SBTree();
        for(auto& t: init) {
            insert(t);
        }
    }

    ~SBTree() {
        clear(_end);
        delete nil;
    }

    iterator begin() { return iterator(this, _begin); };
    iterator end() { return iterator(this, _end); }
    const_iterator begin() const { return begin(); }
    const_iterator end() const { return end(); }
};


template<class Key, class Value>
struct SBMap: public SBTree<pair<Key, Value>> {
    using Base = SBTree<pair<Key, Value>>;
    using iterator = typename Base::iterator;
    using Node = typename Base::Node;

    using Base::Base;

    iterator find(const Key& key) {
        Node *node = Base::root;
        while(node->sz and node->data.first != key) {
            node = node->child[node->data.first < key];
        }
        if(node->sz) {
            return iterator(node);
        }
        return Base::end();
    }

    iterator insert(const pair<Key, Value>& data) {
        auto ii = find(data.first);
        if(ii == Base::end()) {
            ii = Base::insert(data);
        }
        return ii;
    }

    int rank(const Key& key) {
        int cnt = 0;
        Node* node = Base::root;
        while(node->sz) {
            if(node->data.first < key) {
                cnt += node->child[0]->sz + 1;
                node = node->child[1];
            } else if(node->data.first > key) {
                node = node->child[0];
            } else {
                cnt += node->child[0]->sz;
                return cnt;
            }
        }
        return -1;
    }

    bool erase(const Key& key) {
        auto ii = find(key);
        if(ii == Base::end()) {
            return false;
        }
        return Base::erase(ii);
    }

    bool erase(const iterator& ii) {
        return Base::erase(ii);
    }

    Value& operator[](const Key& key) {
        auto ii = find(key);
        if(ii == Base::end()) {
            ii = Base::insert({key, Value()});
        }
        return ii->second;
    }
};

template<class T>
void test(T& t) {
    double t0 = clock();
    int n = 300000;
    for(int i = 0; i < n; i++) {
        t.insert(i);
    }
    for(int i = 0; i < n; i += 2) {
        t.erase(i);
    }
    for(int i = 0; i < n; i += 3) {
        t.insert(i);
    }
    bool x = false;
    for(int i = 0; i < n; i++) {
        bool ret = (t.find(i) == t.end());
        x ^= ret;
    }
    cout << x << endl;
    cout << (clock() - t0) / 1000000 << endl;;
}


int main() {
    SBTree<int> t;
    test(t);
    set<int> t2;
    test(t2);

    t.clear();
    vector<int> v = {1, 1, 2, 2, 3, 3, 4, 5, 6, 7, 8, 9, 10};
    shuffle(v.begin(), v.end(), default_random_engine(time(0)));
    for(auto& i: v) {
        t.insert(i);
    }
    t.erase(10);
    t.erase(123);
    cout << t.size() << endl;
    cout << *(t.kth(3)) << endl;
    cout << (3 == t.rank(*(t.kth(3)))) << endl;
    for(auto& i: t) {
        cout << i << " ";
    }
    cout << endl;
    auto ii = t.begin();
    ii += 2;
    cout << *(ii + 3) << endl;
    cout << *(ii - 1) << endl;
    cout << *prev(ii) << endl;
    cout << distance(t.begin(), t.end()) << endl;
    return 0;
}
