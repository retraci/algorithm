#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#include <unordered_map>

using namespace std;

const int N = 2e3 + 5;
const int dx[5] = {0, 1, -1, 0, 0}, dy[5] = {0, 0, 0, 1, -1};

int T, n, m;
char s[N][N];
bool vis[N][N];
int vis1[N][N];
int f[N][N], flag;

int cho(char ss) {
    if (ss == 'D') return 1;
    if (ss == 'U') return 2;
    if (ss == 'R') return 3;
    if (ss == 'L') return 4;
    return 1;
}

void dfs(int x, int y, int dep) {
    vis1[x][y] = dep;
    if (dep > 4e5) {
        cout << 1;
        return;
    }
    int x1 = x + dx[cho(s[x][y])], y1 = y + dy[cho(s[x][y])];
    if (x1 == 0 || y1 == 0 || x1 > n || y1 > m) {
        f[x][y] = 1;
        vis1[x][y] = 0;
        vis[x][y] = true;
        return;
    }
    if (vis[x1][y1]) {
        vis1[x][y] = 0;
        vis[x][y] = true;
        f[x][y] = f[x1][y1] + 1;
        return;
    }
    if (vis1[x1][y1]) {
        f[x][y] = vis1[x][y] - vis1[x1][y1] + 1;
        flag = vis1[x1][y1];
        vis1[x][y] = 0;
        vis[x][y] = true;
        return;
    }

    dfs(x1, y1, dep + 1);
    if (dep < flag) f[x][y] = f[x1][y1] + 1;
    else f[x][y] = f[x1][y1];
    vis[x][y] = true;
    vis1[x][y] = 0;
}

void solve() {
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            vis[i][j] = f[i][j] = 0;
        }
    }

    int maxn = 0, maxi, maxj;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            if (!vis[i][j]) {
                flag = 1e9;
                dfs(i, j, 1);
                if (f[i][j] > maxn) {
                    maxn = f[i][j];
                    maxi = i;
                    maxj = j;
                }
            }
        }
    }
    cout << maxi << ' ' << maxj << ' ' << maxn << endl;
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    cin >> T;
    while (T--) {
        cin >> n >> m;
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= m; ++j) {
                cin >> s[i][j];
            }
        }
        solve();
    }

    return 0;
}