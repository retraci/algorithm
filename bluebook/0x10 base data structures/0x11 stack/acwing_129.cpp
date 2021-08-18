#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

const int N = 25;

int n;
int cnt;
int vis[N];
int ans[N], stk[N], top, tot;

void dfs(int x) {
    if (cnt >= 20) return;
    if (x >= n + 1) {
        cnt++;

        for (int i = 0; i < tot; i++) printf("%d", ans[i]);
        for (int i = top - 1; i >= 0; i--) printf("%d", stk[i]);
        cout << endl;

        return;
    }

    // 出栈
    if (top) {
        ans[tot++] = stk[--top];
        dfs(x);
        stk[top++] = ans[--tot];
    }

    // 进栈
    stk[top++] = x;
    dfs(x + 1);
    top--;
}

void solve() {
    memset(vis, 0, sizeof vis);
    cnt = tot = top = 0;
    dfs(1);
}

int main() {
    freopen("../in.txt", "r", stdin);

    cin >> n;
    solve();

    return 0;
}