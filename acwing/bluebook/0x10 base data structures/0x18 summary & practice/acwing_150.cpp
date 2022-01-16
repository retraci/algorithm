#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#include <stack>

using namespace std;

#define ll long long

typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

string str;

void solve() {
    stack<int> stk;

    int ans = 0;
    for (int i = 0; i < str.size(); i++) {
        char ch = str[i];
        if (stk.empty() || ch == '(' || ch == '[' || ch == '{') {
            stk.push(i);
            continue;
        }

        char tp = str[stk.top()];
        if (tp == '(' && ch == ')' || tp == '[' && ch == ']' || tp == '{' && ch == '}') stk.pop();
        else stk.push(i);

        int lb = stk.empty() ? 0 : stk.top() + 1;
        ans = max(ans, i - lb + 1);
    }

    cout << ans << endl;
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> str;
    solve();

    return 0;
}