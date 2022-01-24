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

const int dx[9] = {0, 0, -1, 1, -1, -1, 1, 1, 0};
const int dy[9] = {-1, 1, 0, 0, -1, 1, -1, 1, 0};

const int N = 810;

int n, m;
string g[N];
int ti[3][N][N];

int tt;
pii gs[3], boy, girl;

int get(pii p1, pii p2) {
    return abs(p1.first - p2.first) + abs(p1.second - p2.second);
}

bool check(pii p, int layer) {
    auto [x, y] = p;
    int d1 = get({x, y}, gs[1]), d2 = get({x, y}, gs[2]);
    return g[x][y] != 'X' && d1 > 2 * layer && d2 > 2 * layer;
}

void work(pii sp, int step, int col) {
    queue<pii> que;
    que.push(sp);
    auto [sx, sy] = sp;
    ti[col][sx][sy] = 0;
    int layer = 0;
    while (!que.empty()) {
        layer++;

        for (int i = 0; i < step; i++) {
            int sz = que.size();
            while (sz--) {
                auto [x, y] = que.front(); que.pop();
                if (!check({x, y}, layer)) continue;

                for (int k = 0; k < 4; k++) {
                    int nx = x + dx[k], ny = y + dy[k];

                    if (nx >= 1 && nx <= n && ny >= 1 && ny <= m) {
                        if (check({nx, ny}, layer) && ti[col][nx][ny] == -1) {
                            ti[col][nx][ny] = layer;
                            que.push({nx, ny});
                        }
                    }
                }
            }
        }
    }
}

void solve() {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            ti[1][i][j] = ti[2][i][j] = -1;
        }
    }

    tt = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (g[i][j] == 'Z') gs[++tt] = {i, j};
            if (g[i][j] == 'M') boy = {i, j};
            if (g[i][j] == 'G') girl = {i, j};
        }
    }

    work(boy, 3, 1);
    work(girl, 1, 2);

    int ans = 1e9;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (ti[1][i][j] != -1 && ti[2][i][j] != -1) {
                ans = min(ans, max(ti[1][i][j], ti[2][i][j]));
            }
        }
    }

    cout << (ans == 1e9 ? -1 : ans) << "\n";
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
            cin >> g[i];
            g[i] = ' ' + g[i];
        }
        solve();
    }

    return 0;
}