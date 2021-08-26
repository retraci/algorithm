#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <queue>

using namespace std;

const int N = 110;
const int dx[4] = {-1, 1, 0, 0};
const int dy[4] = {0, 0, -1, 1};

struct Node {
    int x, y, d;

    bool operator<(const Node &that) const {
        return d > that.d;
    }
};

int n, m;
int xs, ys, xt, yt;
int va[N][N], vb[N][N];

int dist[N][N];
int vis[N][N];

int get(int x, int y, int d, int k) {
    int now = d % (va[x][y] + vb[x][y]);
    if (now < va[x][y]) {
        if (k < 2) return 1;
        else return va[x][y] - now + 1;
    } else {
        if (k >= 2) return 1;
        else return va[x][y] + vb[x][y] - now + 1;
    }
}

void solve() {
    priority_queue<Node> que;
    memset(dist, 0x3f, sizeof dist);
    memset(vis, 0, sizeof vis);
    dist[xs][ys] = 0;
    que.push({xs, ys, 0});
    while (!que.empty()) {
        auto[x, y, d] = que.top();
        que.pop();
        if (vis[x][y]) continue;
        vis[x][y] = 1;

        for (int k = 0; k < 4; k++) {
            int nx = x + dx[k], ny = y + dy[k];
            if (nx >= 1 && nx <= n && ny >= 1 && ny <= m) {
                int nd = dist[x][y] + get(x, y, d, k);
                if (dist[nx][ny] > nd) {
                    dist[nx][ny] = nd;
                    que.push({nx, ny, nd});
                }
            }
        }
    }

    cout << dist[xt][yt] << endl;
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    cin >> n >> m >> xs >> ys >> xt >> yt;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            scanf("%d", &va[i][j]);
        }
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            scanf("%d", &vb[i][j]);
        }
    }
    solve();

    return 0;
}