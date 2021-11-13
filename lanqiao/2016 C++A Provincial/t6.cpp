// 寒假作业

#include <bits/stdc++.h>

using namespace std;

int vis[15];
int vv[15];
int ans;

void dfs(int x) {
    if (x == 12) {
        // 除法 转 乘法验证
        if (vv[9] == vv[11] * vv[10]) ans++;
        return;
    }
    // 可行性剪枝
    if (x >= 3 && vv[0] + vv[1] != vv[2]) return;
    if (x >= 6 && vv[3] - vv[4] != vv[5]) return;
    if (x >= 9 && vv[6] * vv[7] != vv[8]) return;

    for (int i = 1; i <= 13; i++) {
        if (!vis[i]) {
            vis[i] = 1;
            vv[x] = i;
            dfs(x + 1);
            vv[x] = 0;
            vis[i] = 0;
        }
    }
}

void solve() {
    ans = 0;
    dfs(0);

    cout << ans << endl;
}

int main() {
    freopen("../in.txt", "r", stdin);

    solve();

    return 0;
}