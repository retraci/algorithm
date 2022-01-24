#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>

using namespace std;

const int N = 110;

int n, m;
int g[N][N];
int f[N][N];
int pos[N][N];
vector<int> path;
int ans;

// i->j之间的路, 输出i到j之间不包括i和j的道路
void dfs(int i, int j) {
    int k = pos[i][j];
    if (k == 0) return;

    dfs(i, k);
    path.push_back(k);
    dfs(k, j);
}

void get_path(int i, int j, int k) {
    path = {};
    path.push_back(k);
    path.push_back(i);
    dfs(i, j);
    path.push_back(j);
}

void floyd() {
    for (int k = 1; k <= n; k++) {
        // 用前一个状态算最小环
        // 至少包含i, j, k, 最大编号是k(防止重复计算)
        for (int i = 1; i < k; i++) {
            for (int j = i + 1; j < k; j++) {
                if (ans > 1LL * f[i][j] + g[i][k] + g[j][k]) {
                    ans = f[i][j] + g[i][k] + g[j][k];
                    get_path(i, j, k);
                }
            }
        }

        // 推 floyd
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (f[i][j] > f[i][k] + f[k][j]) {
                    f[i][j] = f[i][k] + f[k][j];
                    pos[i][j] = k;
                }
            }
        }
    }
}

void add(int u, int v, int w) {
    g[u][v] = min(g[u][v], w);
}

void solve() {
    memcpy(f, g, sizeof f);
    ans = 0x3f3f3f3f;
    floyd();

    if (ans == 0x3f3f3f3f) {
        cout << "No solution." << endl;
        return;
    }
    for (int u : path) cout << u << " ";
    cout << endl;
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n >> m;
    memset(g, 0x3f, sizeof g);
    for (int i = 1; i <= n; i++) g[i][i] = 1;
    while (m--) {
        int u, v, w;
        cin >> u >> v >> w;
        add(u, v, w), add(v, u, w);
    }
    solve();

    return 0;
}