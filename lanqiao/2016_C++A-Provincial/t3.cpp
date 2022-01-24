// 方格填数

#include <bits/stdc++.h>
#pragma GCC optimize(2)

using namespace std;

const int dx[8] = {0,0,-1,1,-1,1,-1,1};
const int dy[8] = {-1,1,0,0,-1,1,1,-1};

int ans;
int n, m;
int va[15];
int g[4][4];

bool vaild(int x, int y) {
    if (x == 0 && y == 0 || x == n - 1 && y == m - 1) return false;
    return x >= 0 && x < n && y >= 0 && y < m;
}

void solve() {
    n = 3, m = 4;
    for (int i = 1; i <= 10; i++) va[i] = i;
    ans = 0;

    do {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (i == 0 && j == 0 || i == n - 1 && j == m - 1) continue;
                g[i][j] = va[i * m + j];
            }
        }

        int flag = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (i == 0 && j == 0 || i == n - 1 && j == m - 1) continue;

                for (int k = 0; k < 8; k++) {
                    int nx = i + dx[k];
                    int ny = j + dy[k];
                    if (vaild(nx, ny)) {
                        if (abs(g[nx][ny] - g[i][j]) == 1) flag = 1;
                    }
                }
            }
        }

        if (!flag) ans++;
    } while (next_permutation(va + 1, va + 1 + 10));

    cout << ans << endl;
}

int main() {
    freopen("../in.txt", "r", stdin);

    solve();

    return 0;
}