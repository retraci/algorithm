#include <bits/stdc++.h>

using namespace std;

class MinStack {
public:
    stack<int> stk1;
    stack<int> stk2;

    /** initialize your data_structure here. */
    MinStack() {

    }

    void push(int x) {
        stk1.push(x);

        if (stk2.empty() || x <= stk2.top()) stk2.push(x);
    }

    void pop() {
        if (stk1.top() == stk2.top()) stk2.pop();

        stk1.pop();
    }

    int top() {
        return stk1.top();
    }

    int getMin() {
        return stk2.top();
    }
};

/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack obj = new MinStack();
 * obj.push(x);
 * obj.pop();
 * int param_3 = obj.top();
 * int param_4 = obj.getMin();
 */

int main() {
    freopen("../in.txt", "r", stdin);


    return 0;
}