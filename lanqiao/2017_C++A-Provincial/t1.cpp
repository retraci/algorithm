// 迷宫

#include <bits/stdc++.h>

using namespace std;

string str = "UDDLUULRULUURLLLRRRURRUURLDLRDRUDDDDUUUUURUDLLRRUUDURLRLDLRLULLURLLRDURDLULLRDDDUUDDUDUDLLULRDLUURRR";
char g[15][15];
int vis[15][15];
int ans;

bool vaild(int x, int y) {
    return x >= 0 && x < 10 && y >= 0 && y < 10;
}

void dfs(int x, int y) {
    if (!vaild(x, y)) {
        ans++;
        return;
    }

    if (vis[x][y]) return;
    vis[x][y] = 1;

    if (g[x][y] == 'U') return dfs(x - 1, y);
    if (g[x][y] == 'D') return dfs(x + 1, y);
    if (g[x][y] == 'L') return dfs(x, y - 1);
    if (g[x][y] == 'R') return dfs(x, y + 1);
}

void solve() {
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            g[i][j] = str[i * 10 + j];
        }
    }

    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            memset(vis, 0, sizeof vis);
            dfs(i, j);
        }
    }

    cout << ans << endl;
}

int main() {
    freopen("../in.txt", "r", stdin);

//    cout << str.size() << endl;

    solve();

    return 0;
}