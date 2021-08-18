#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <queue>

#include <direct.h>

using namespace std;

struct Node {
    int x, y, score;
    bool operator< (const Node &that) const {
        return score < that.score;
    }
};

const int N = 110;
const int dx[4] = {0, 0, -1, 1};
const int dy[4] = {-1, 1, 0, 0};

int n, m;
int va[N][N];
int f[N][N];

void solve() {
    memset(f, 0, sizeof f);
    priority_queue<Node> que;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            que.push({i, j, va[i][j]});
        }
    }

    while (!que.empty()) {
        Node cur = que.top(); que.pop();
        int x = cur.x, y = cur.y;

        for (int k = 0; k < 4; k++) {
            int nx = x + dx[k], ny = y + dy[k];
            if (va[nx][ny] > cur.score) f[x][y] = max(f[x][y], f[nx][ny] + 1);
        }
    }

    int ans = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            ans = max(ans, f[i][j]);
        }
    }
    cout << ans + 1 << endl;
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m;j ++) {
            scanf("%d", &va[i][j]);
        }
    }
    solve();

    return 0;
}