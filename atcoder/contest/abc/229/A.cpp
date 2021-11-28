#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>

using namespace std;

#define ll long long

const int dx[4] = {0, 0, -1, 1};
const int dy[4] = {-1, 1, 0, 0};

typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

string maze[2];
int vis[2][2];

void dfs(int x, int y) {
    vis[x][y] = 1;
    for (int k = 0; k < 4; k++) {
        int nx = x + dx[k], ny = y + dy[k];
        if (nx >= 0 && nx < 2 && ny >= 0 && ny < 2) {
            if (maze[nx][ny] == '#' && !vis[nx][ny]) dfs(nx, ny);
        }
    }
}

bool check() {
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            if (!vis[i][j] && maze[i][j] == '#') return false;
        }
    }
    return true;
}

void solve() {
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            if (maze[i][j] != '#') continue;
            dfs(i, j);

            if (check()) cout << "Yes" << endl;
            else cout << "No" << endl;
            return;
        }
    }
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> maze[0] >> maze[1];
    solve();

    return 0;
}