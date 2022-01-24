// 方格分割

#include <bits/stdc++.h>

using namespace std;

const int dx[4] = {0,0,-1,1};
const int dy[4] = {-1,1,0,0};

int n, m;
int vis[10][10];
int ans;

bool vaild(int x, int y) {
    return x >= 0 && x < n && y >= 0 && y < m;
}

void dfs(int x, int y) {
    if (x == 0 || x == n - 1 || y == 0 || y == m - 1) {
        ans++;
        return;
    }

    for (int k = 0; k < 4; k++) {
        int nx = x + dx[k], ny = y + dy[k];

        if (vaild(nx, ny) && !vis[nx][ny]) {
            vis[nx][ny] = vis[n - 1 - nx][m - 1 - ny] = 1;
            dfs(nx, ny);
            vis[nx][ny] = vis[n - 1 - nx][m - 1 - ny] = 0;
        }
    }
}

void solve() {
    n = m = 7;
    vis[3][3] = 1;
    dfs(3, 3);

    cout << ans / 4 << endl;
}

int main() {
    freopen("../in.txt", "r", stdin);

    solve();

    return 0;
}