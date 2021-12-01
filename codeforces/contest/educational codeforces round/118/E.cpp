#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#include <queue>

using namespace std;

#define ll long long

typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

const int N = 1e6 + 10;
const int dx[4] = {0, 0, -1, 1};
const int dy[4] = {-1, 1, 0, 0};

int n, m;
string g[N];
vector<vector<int>> vis;

int calc(int x, int y) {
    int res = 0;
    for (int k = 0; k < 4; k++) {
        int nx = x + dx[k], ny = y + dy[k];
        if (nx >= 1 && nx <= n && ny >= 1 && ny <= m) {
            if (g[nx][ny] == '.' && !vis[nx][ny]) res++;
        }
    }
    return res;
}

void solve() {
    vis = vector<vector<int>>(n + 1, vector<int>(m + 1, 0));

    queue<pii> que;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (g[i][j] == 'L') {
                vis[i][j] = 1;
                que.push({i, j});
            }
        }
    }

    while (!que.empty()) {
        auto [x, y] = que.front(); que.pop();

        for (int k = 0; k < 4; k++) {
            int nx = x + dx[k], ny = y + dy[k];
            if (nx >= 1 && nx <= n && ny >= 1 && ny <= m) {
                if (g[nx][ny] == '.' && !vis[nx][ny]) {
                    int cnt = calc(nx, ny);
                    if (cnt <= 1) {
                        vis[nx][ny] = 1;
                        que.push({nx, ny});
                    }
                }
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (vis[i][j] && g[i][j] == '.') g[i][j] = '+';
        }
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cout << g[i][j];
        }
        cout << "\n";
    }
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int T;
    cin >> T;
    while (T--) {
        cin >> n >> m;
        for (int i = 1; i <= n; i++) {
            string str;
            cin >> str;
            str = ' ' + str;
            g[i] = str;
        }
        solve();
    }

    return 0;
}