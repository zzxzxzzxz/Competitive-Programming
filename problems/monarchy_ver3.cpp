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


class Monarchy {
    private:
        bool first = true;
        unordered_map<string, string> name_map, i_name_map;
        unordered_map<string, int> n_children;
        set<string> s;

    public:
        void birth(const string& child, const string& parent) {
            print("birth:", child, parent);

            if(first) {
                first = false;
                name_map[parent] = "0";
                i_name_map["0"] = parent;
                s.insert("0");
            }
            string id = name_map[parent] + char('0' + n_children[parent]);
            name_map[child] = id;
            i_name_map[id] = child;
            n_children[parent] += 1;
            s.insert(name_map[child]);
        }

        void death(const string& name) {
            print("death:", name);

            s.erase(name_map[name]);
            i_name_map.erase(name_map[name]);
            name_map.erase(name);
        }

        vector<string> getOrderOfSuccession() {
            cout << "get: ";
            vector<string> ans;
            for(auto& id: s) {
                ans.push_back(i_name_map[id]);
            }
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
