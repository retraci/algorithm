#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <stack>

using namespace std;

string str;

int calc(int &s) {
    stack<int> stk;
    int cur = 0;
    while (s < str.size()) {
        if (str[s] == '(') {
            stk.push(cur);
            cur = 0;
        } else if (str[s] == ')') {
            if (stk.empty()) {
                s--;
                return cur;
            }
            stk.pop();
        } else {
            int a = cur;
            s += 2;
            int b = calc(s);

            cur = max(a + 1, b);
        }
        s++;
    }

    return cur;
}

void solve() {
    int id = 0;
    int ans = calc(id);

    cout << ans << endl;
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    ios::sync_with_stdio(false);
    cin >> str;
    solve();

    return 0;
}