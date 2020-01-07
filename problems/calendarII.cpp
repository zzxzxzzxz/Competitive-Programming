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

class MyCalendarTwo {
private:
    set<pair<int, int>> records, overlaped;
public:
    MyCalendarTwo() {
        records.insert({INT_MIN, INT_MIN});
        overlaped.insert({INT_MIN, INT_MIN});
    }

    bool book(int start, int end) {
        pair<int, int> p = {start, INT_MAX};
        auto it = prev(overlaped.upper_bound(p));
        --it;
        for(int i = 0; i < 2 and it != overlaped.end(); ++i, ++it) {
            auto [l, r] = *it;
            if(start < r and l < end) {
                return false;
            }
        }

        it = prev(records.upper_bound(p));
        while(it != records.end() and it->first < end) {
            auto [l, r] = *it;
            if(start < r and l < end) {
                overlaped.insert({max(start, l), min(end, r)});
                start = min(start, l);
                end = max(end, r);
                it = records.erase(it);
            } else {
                ++it;
            }
        }
        records.insert({start, end});
        return true;
    }
};


int main() {
    vector<string> ans = {"false", "true"};
    MyCalendarTwo m;
    cout << ans[m.book(10, 20)] << endl;
    cout << ans[m.book(50, 60)] << endl;
    cout << ans[m.book(10, 40)] << endl;
    cout << ans[m.book(5, 15)] << endl;
    cout << ans[m.book(5, 10)] << endl;
    cout << ans[m.book(25, 55)] << endl;
    return 0;
}
