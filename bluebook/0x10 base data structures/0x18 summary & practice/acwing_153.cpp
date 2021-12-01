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

const int N = 1010;

int n;
int va[N];
int f[N];

vector<int> g[N];
int color[N];

int cur;
stack<int> stk1, stk2;

bool dfs(int u, int c) {
    color[u] = c;
    for (auto v: g[u]) {
        if (color[v] == c) return false;
        if (color[v] == -1 && !dfs(v, !c)) return false;
    }

    return true;
}

void add(int u, int v) {
    g[u].push_back(v);
}

void pop_all() {
    while (true) {
        if (!stk1.empty() && stk1.top() == cur) {
            stk1.pop();
            cout << "b" << " ";
            cur++;
        } else if (!stk2.empty() && stk2.top() == cur) {
            stk2.pop();
            cout << "d" << " ";
            cur++;
        } else {
            break;
        }
    }
}

void solve() {
    f[n + 1] = n + 1;
    for (int i = n; i >= 1; i--) f[i] = min(f[i + 1], va[i]);

    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            if (f[j + 1] < va[i] && va[j] > va[i]) {
                add(i, j), add(j, i);
            }
        }
    }

    memset(color, -1, sizeof color);
    int flag = 0;
    for (int i = 1; i <= n; i++) {
        if (color[i] == -1 && !dfs(i, 0)) {
            flag = 1;
            break;
        }
    }
    if (flag) {
        cout << 0 << endl;
        return;
    }

    cur = 1;
    for (int i = 1; i <= n; i++) {
        if (color[i] == 0) {
            // 要入第一个栈了, 第一个栈该出的现在必须要出掉
            // 为了使字典序最小, 第二个栈可以再等等
            while (!stk1.empty() && stk1.top() == cur) {
                stk1.pop();
                cout << "b" << " ";
                cur++;
            }
            // 如果a[i]入栈的话, 发现无法满足，此时就要考虑将第二个栈的元素pop
            if (!stk1.empty() && va[i] > stk1.top()) pop_all();

            stk1.push(va[i]);
            cout << "a" << " ";
        } else {
            // 要入第二个栈了, 第二个栈该出的现在必须要出掉
            // 然而由于b比c字典序小, 第一个栈可以出的也应该出掉
            pop_all();

            stk2.push(va[i]);
            cout << "c" << " ";
        }
    }
    // 最后出栈剩余的
    pop_all();
    cout << endl;
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> va[i];
    solve();

    return 0;
}