#include <bits/stdc++.h>

using namespace std;

const int N = 25;
const int INF = 0x3f3f3f3f;

int n, m;
int minv[N], mins[N];
int rs[N], hs[N];
int ans;

void dfs(int dep, int v, int s) {
    // 可行性剪枝
    if (v + minv[dep] > n) return;
    // 最优化剪枝
    if (s + mins[dep] >= ans) return;
    // 鬼畜剪枝
    if (s + 2 * (n - v) / rs[dep + 1] >= ans) return;

    if (dep == 0) {
        if (v == n) ans = min(ans, s);
        return;
    }

    // 搜索顺序优化
    int mxr = min((int) sqrt(n - v), rs[dep + 1] - 1);
    for (int r = mxr; r >= dep; r--) {
        int mxh = min((int) (n - v) / r / r, hs[dep + 1] - 1);

        for (int h = mxh; h >= dep; h--) {
            int nv = v + r * r * h;
            int ns = s + 2 * r * h;
            if (dep == m) ns += r * r;
            rs[dep] = r, hs[dep] = h;
            dfs(dep - 1, nv, ns);
        }
    }
}

void solve() {
    for (int i = 1; i <= m; i++) {
        minv[i] = minv[i - 1] + i * i * i;
        mins[i] = mins[i - 1] + 2 * i * i;
    }

    ans = INF;
    rs[m + 1] = hs[m + 1] = INF;
    dfs(m, 0, 0);

    cout << (ans == INF ? 0 : ans) << endl;
}

int main() {
    freopen("../in.txt", "r", stdin);

    cin >> n >> m;
    solve();

    return 0;
}