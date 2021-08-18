// 全球变暖

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <set>

using namespace std;

const int N = 1010;
const int dx[4] = {0,0,-1,1};
const int dy[4] = {-1,1,0,0};

int n;
char g[N][N];
char ne[N][N];
int vis[N][N];
int fa[N * N];

bool valid(int x, int y) {
    return x >= 0 && x < n && y >= 0 && y < n;
}

int getIdx(int x, int y) {
    return x * n + y;
}

int find(int x) {
    return x == fa[x] ? x : fa[x] = find(fa[x]);
}

void dfs(int x, int y, int f) {
    if (!valid(x, y)) return;
    if (g[x][y] == '.') return;

    if (vis[x][y]) return;
    vis[x][y] = 1;
    int idx = getIdx(x, y);
    int tx = find(idx);
    fa[tx] = f;

    for (int k = 0; k < 4; k++) {
        int nx = x + dx[k], ny = y + dy[k];
        dfs(nx, ny, f);
    }
}

void solve() {
    for (int i = 0; i < n * n; i++) fa[i] = i;
    memset(vis, 0, sizeof vis);
    int tot = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (!vis[i][j] && g[i][j] == '#') {
                tot++;
                dfs(i, j, getIdx(i, j));
            }
        }
    }

    memcpy(ne, g, sizeof g);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (ne[i][j] == '.') continue;

            for (int k = 0; k < 4; k++) {
                int nx = i + dx[k], ny = j + dy[k];
                if (valid(nx, ny) && g[nx][ny] == '.') ne[i][j] = '.';
            }
        }
    }

    set<int> sett;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (ne[i][j] == '#') {
                int x = find(getIdx(i, j));
//                cout << i << " " << j << " " << x << endl;
                sett.insert(x);
            }
        }
    }

    cout << tot - sett.size() << endl;
}

int main() {
    freopen("../in.txt", "r", stdin);
    std::ios::sync_with_stdio(false);

    cin >> n;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> g[i][j];
        }
    }
    solve();

    return 0;
}