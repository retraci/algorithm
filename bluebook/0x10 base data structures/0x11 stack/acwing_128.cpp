#include <bits/stdc++.h>

using namespace std;

const int N = 1e6 + 10;

int s[N], f[N];
stack<int> stk1, stk2;

void solve() {
    int Q;
    char op;
    int x;

    cin >> Q;
    memset(f, -0x3f3f3f3f, sizeof f);
    for (int i = 0; i < Q; i++) {
        cin >> op;
        if (op == 'I') {
            cin >> x;
            stk1.push(x);

            s[stk1.size()] = s[stk1.size() - 1] + stk1.top();
            f[stk1.size()] = max(f[stk1.size() - 1], s[stk1.size()]);
        } else if (op == 'D') {
            if (stk1.empty()) continue;
            stk1.pop();
        } else if (op == 'L') {
            if (stk1.empty()) continue;
            stk2.push(stk1.top());
            stk1.pop();
        } else if (op == 'R') {
            if (stk2.empty()) continue;
            stk1.push(stk2.top());
            stk2.pop();

            s[stk1.size()] = s[stk1.size() - 1] + stk1.top();
            f[stk1.size()] = max(f[stk1.size() - 1], s[stk1.size()]);
        } else if (op == 'Q') {
            cin >> x;
            cout << f[x] << endl;
        }
    }
}

int main() {
    freopen("../in.txt", "r", stdin);
    std::ios::sync_with_stdio(false);

    solve();

    return 0;
}