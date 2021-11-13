#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <queue>

using namespace std;

#define ll long long

struct Node {
    ll x, y, d;

    bool operator<(const Node &that) const {
        return d > that.d;
    }
};

const int N = 510;

int n, m, x1, y1, x2, y2;
ll a[N][N], b[N][N], c[N][N], w[N][N];
ll f[N][N];
int vis[N][N];

void solve() {
    memset(f, 0x3f, sizeof f), memset(vis, 0, sizeof vis);
    priority_queue<Node> que;
    f[x1][y1] = 0;
    que.push({x1, y1, 0});
    while (!que.empty()) {
        auto [x, y, d] = que.top(); que.pop();
        if (vis[x][y]) continue;
        vis[x][y] = 1;

        ll t = a[x][y] + b[x][y];
        ll cur = d % t;
        // 上
        if (x > 1 && !vis[x - 1][y]) {
            ll nd = d + w[x - 1][y];
            if (cur >= a[x][y]) {
                ll rem = t - cur;
                nd += rem;
            }
            if (f[x - 1][y] > nd) {
                f[x - 1][y] = nd;
                que.push({x - 1, y, nd});
            }
        }
        // 下
        if (x < n && !vis[x + 1][y]) {
            ll nd = d + w[x][y];
            if (cur >= a[x][y]) {
                ll rem = t - cur;
                nd += rem;
            }
            if (f[x + 1][y] > nd) {
                f[x + 1][y] = nd;
                que.push({x + 1, y, nd});
            }
        }
        // 左
        if (y > 1 && !vis[x][y - 1]) {
            ll nd = d + c[x][y - 1];
            if (cur < a[x][y]) {
                ll rem = a[x][y] - cur;
                nd += rem;
            }
            if (f[x][y - 1] > nd) {
                f[x][y - 1] = nd;
                que.push({x, y - 1, nd});
            }
        }
        // 右
        if (y < m && !vis[x][y + 1]) {
            ll nd = d + c[x][y];
            if (cur < a[x][y]) {
                ll rem = a[x][y] - cur;
                nd += rem;
            }
            if (f[x][y + 1] > nd) {
                f[x][y + 1] = nd;
                que.push({x, y + 1, nd});
            }
        }
    }

    cout << f[x2][y2] << endl;
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    ios::sync_with_stdio(false);
    cin >> n >> m >> x1 >> y1 >> x2 >> y2;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cin >> a[i][j];
        }
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cin >> b[i][j];
        }
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m - 1; j++) {
            cin >> c[i][j];
        }
    }
    for (int i = 1; i <= n - 1; i++) {
        for (int j = 1; j <= m; j++) {
            cin >> w[i][j];
        }
    }
    solve();

    return 0;
}