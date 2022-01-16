#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#include <queue>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>

using namespace std;

#define ll long long

typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

struct Node {
    int x, y, l;
};

const int dx[9] = {0, 0, -1, 1, -1, -1, 1, 1, 0};
const int dy[9] = {-1, 1, 0, 0, -1, 1, -1, 1, 0};
const int d[3][4][3] = {
        {{-2, 0, 2}, {0, 1, 1}, {1, 0, 2}, {0, -2, 1}},
        {{-1, 0, 1}, {0, 2, 0}, {1, 0, 1}, {0, -1, 0}},
        {{-1, 0, 0}, {0, 1, 2}, {2, 0, 0}, {0, -1, 2}}
};

const int N = 510;

int n, m;
string g[N];

Node s, t;
int dist[N][N][3];

bool check(int x, int y) {
    return x >= 1 && x <= n && y >= 1 && y <= m && g[x][y] != '#';
}

int bfs() {
    queue<Node> que;
    dist[s.x][s.y][s.l] = 0;
    que.push(s);
    while (!que.empty()) {
        auto [x, y, l] = que.front(); que.pop();

        for (int k = 0; k < 4; k++) {
            int nx = x + d[l][k][0], ny = y + d[l][k][1], nl = d[l][k][2];

            if (nl == 0) {
                if (check(nx, ny) && g[nx][ny] != 'E' && dist[nx][ny][nl] == -1) {
                    dist[nx][ny][nl] = dist[x][y][l] + 1;
                    que.push({nx, ny, nl});
                }
            } else if (nl == 1) {
                if (check(nx, ny) && check(nx, ny + 1) && dist[nx][ny][nl] == -1) {
                    dist[nx][ny][nl] = dist[x][y][l] + 1;
                    que.push({nx, ny, nl});
                }
            } else {
                if (check(nx, ny) && check(nx + 1, ny) && dist[nx][ny][nl] == -1) {
                    dist[nx][ny][nl] = dist[x][y][l] + 1;
                    que.push({nx, ny, nl});
                }
            }
        }
    }

    return dist[t.x][t.y][0];
}

void solve() {
    memset(dist, -1, sizeof dist);
    s = t = {-1, -1, -1};
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (g[i][j] == 'X' && s.x == -1) {
                if (g[i + 1][j] == 'X') s = {i, j, 2};
                else if (g[i][j + 1] == 'X') s = {i, j, 1};
                else s = {i, j, 0};
            }
            if (g[i][j] == 'O' && t.x == -1) {
                t = {i, j, 0};
            }
        }
    }

    int ans = bfs();
    if (ans == -1) cout << "Impossible" << "\n";
    else cout << ans << "\n";
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    while (cin >> n >> m, n && m) {
        for (int i = 1; i <= n; i++) {
            cin >> g[i];
            g[i] = ' ' + g[i];
        }
        solve();
    }

    return 0;
}