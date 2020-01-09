//{{{
#include<bits/stdc++.h>
using namespace std;
template<class T>
void print(const vector<T>& data) {
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

struct Node {
    int l, r;
    int val, lazy;
    unique_ptr<Node> lc, rc;
    Node(int l, int r): l(l), r(r), val(0), lazy(0) {};
    void pull() {
        if(l < r - 1) {
            val = max(rc->val + rc->lazy, lc->val + lc->lazy);
        }
    }
    void push() {
        val += lazy;
        if(l < r - 1) {
            int mid = l + (r - l) / 2;
            if(not lc) lc = make_unique<Node>(l, mid);
            if(not rc) rc = make_unique<Node>(mid, r);
            lc->lazy += lazy;
            rc->lazy += lazy;
        }
        lazy = 0;
    }
};
using NodePtr = unique_ptr<Node>;

class MyCalendarThree {
private:
    NodePtr root = make_unique<Node>(0, 1e9 + 1);
    void update(int a, int b, NodePtr& node) {
        int l = node->l, r = node->r;
        if(r <= a or b <= l) {
            return;
        }
        if(a <= l and r <= b) {
            node->lazy += 1;
            node->push();
            return;
        }
        node->push();
        update(a, b, node->lc);
        update(a, b, node->rc);
        node->pull();
    }

    //int query(int a, int b, NodePtr& node) {
    //    int l = node->l, r = node->r;
    //    if(r <= a or b <= l) {
    //        return 0;
    //    }
    //    node->push();
    //    if(a <= l and r <= b) {
    //        return node->val;
    //    }
    //    int lret = query(a, b, node->lc);
    //    int rret = query(a, b, node->rc);
    //    return max(lret, rret);
    //}

public:
    MyCalendarThree() {
    }

    int book(int start, int end) {
        update(start, end, root);
        return root->val;
    }
};

/*
 * https://leetcode.com/problems/my-calendar-iii
 */

int main() {
    MyCalendarThree mct;
    vector<pair<int, int>> q = {{10, 20}, {50, 60}, {10, 40}, {5, 15}, {5, 10}, {25, 55}};
    for(auto& [b, e]: q) {
        auto ans = mct.book(b, e);
        print(ans);
    }
    return 0;
}
